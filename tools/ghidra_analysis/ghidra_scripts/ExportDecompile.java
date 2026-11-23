// ExportDecompile.java - decompile the trim/cut mark functions of DocumentMarks.dll
// Run: analyzeHeadless <proj> <name> -process <prog> -noanalysis
//      -scriptPath "H:\Desktop\ArtPlus\tools\ghidra_analysis\ghidra_scripts"
//      -postScript ExportDecompile.java

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.regex.Pattern;

public class ExportDecompile extends GhidraScript {

    private static final Pattern TARGET = Pattern.compile(
        "(?i)(ApplyRelevantMarkSets|ApplyMarksFromSet|ApplyMarkSet|" +
        "CopyMarksToPage|PrepareMarksCachePage|RecreateLoadedMarks)");

    // Factories/parsers found by caller analysis of the CutMark constructors.
    private static final long[] EXTRA = new long[] {
        0x180111410L, // factory: "AIDynamicMarks-CutMark" -> CutMark
        0x180172550L, // factory: constructs PDFPlusCutMark
        0x18017c5d0L  // parser/validator: "Cut Mark has invalid Orientation/Repetition value"
    };

    @Override
    protected void run() throws Exception {
        String progName = currentProgram.getName();
        File outDir = new File("H:/Desktop/ArtPlus/rag/ghidra/exports/" + progName);
        File decDir = new File(outDir, "decompiled");
        decDir.mkdirs();

        DecompInterface ifc = new DecompInterface();
        ifc.setOptions(new ghidra.app.decompiler.DecompileOptions());
        if (!ifc.openProgram(currentProgram)) {
            println("ERROR: could not open program in decompiler");
            return;
        }

        PrintWriter combined = new PrintWriter(new FileWriter(new File(outDir, "marks_decompiled.c")));
        combined.println("// DocumentMarks.dll - decompiled trim/cut mark functions");
        combined.println("// program: " + progName + " base: " + currentProgram.getImageBase());
        combined.println();

        FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
        int ok = 0;
        int fail = 0;
        while (it.hasNext() && !monitor.isCancelled()) {
            Function fn = it.next();
            if (fn.isThunk() || fn.isExternal()) {
                continue;
            }
            String name = fn.getName();
            String full = fn.getName(true);
            boolean isCut = full != null && (full.contains("CutMark") || full.contains("TrimSymbol"));
            boolean isExtra = false;
            long off = fn.getEntryPoint().getOffset();
            for (long e : EXTRA) {
                if (e == off) {
                    isExtra = true;
                    break;
                }
            }
            if (!isCut && !isExtra && (name == null || !TARGET.matcher(name).find())) {
                continue;
            }
            DecompileResults res = ifc.decompileFunction(fn, 120, monitor);
            if (res == null || !res.decompileCompleted() || res.getDecompiledFunction() == null) {
                fail++;
                combined.println("// DECOMPILE FAILED " + fn.getEntryPoint() + " " + name
                    + (res != null ? " : " + res.getErrorMessage() : ""));
                combined.println();
                continue;
            }
            ok++;
            String c = res.getDecompiledFunction().getC();
            combined.println("// ---------------------------------------------------------------");
            combined.println("// FUNC " + fn.getEntryPoint() + " " + name);
            combined.println("// signature: " + fn.getSignature().getPrototypeString());
            combined.println("// ---------------------------------------------------------------");
            combined.println(c);
            combined.println();

            String safe = name.replaceAll("[^A-Za-z0-9_.]", "_");
            if (safe.length() > 120) {
                safe = safe.substring(0, 120);
            }
            File one = new File(decDir, fn.getEntryPoint().toString().replace(":", "_") + "__" + safe + ".c");
            try (PrintWriter pw = new PrintWriter(new FileWriter(one))) {
                pw.println("// " + fn.getEntryPoint() + " " + name);
                pw.println(c);
            }
        }
        combined.close();
        ifc.dispose();
        println("Decompiled ok=" + ok + " fail=" + fail + " -> " + outDir.getAbsolutePath());
    }
}
