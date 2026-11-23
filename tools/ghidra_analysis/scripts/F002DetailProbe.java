// F002DetailProbe.java - F-002 (Mark Set) detail evidence: v240 real functions + interior-address check
//
// Run (headless, project DocMarks_v240, read-only):
//   analyzeHeadless <projdir> DocMarks_v240 -process -readOnly -noanalysis
//        -scriptPath tools/ghidra_analysis/scripts -postScript F002DetailProbe.java
//
// Writes UTF-8 (no BOM):
//   rag/evidence/F-002/ghidra/raw_v240/_detail.txt
//   rag/evidence/F-002/ghidra/raw_v240/_decompile_detail.txt
//   rag/evidence/F-002/ghidra/raw_v240/_interior.txt
//
// Read-only: never modifies the program database.

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.Symbol;

import java.io.File;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

public class F002DetailProbe extends GhidraScript {

    private static final String OUT_DIR =
            "H:/Desktop/ArtPlus/rag/evidence/F-002/ghidra/raw_v240";

    // v240 function entries selected from the symbol table search (names from A4 / spec).
    private static final String[] TARGETS = {
            "0x1800147F0", // DocumentMarks::ApplyMarkSet
            "0x180014A00", // DocumentMarks::ApplyMarkSetToPage
            "0x1800426F0", // DocumentMarks::CopyMarksToPage
            "0x180045C70", // DocumentMarks::MakeFormsFromMarks
            "0x1802436A0", // DocumentMarks::TaskMarkSets::TaskMarkSets
            "0x180243EC0", // TaskMarkSets::ApplyMarksFromSet
            "0x180243F40", // TaskMarkSets::ApplyRelevantMarkSets
            "0x180244A50", // TaskMarkSets::ApplyRelevantMarkSetsWithReuse
            "0x180245380", // TaskMarkSets::CopyMarksToPageWithLog
            "0x180246C70", // TaskMarkSets::PrepareMarksCache (Document overload)
            "0x180248720", // TaskMarkSets::PrepareMarksCachePage
            "0x180248D30", // TaskMarkSets::ReadMarkSetFile
            "0x180249210"  // TaskMarkSets::RecreateLoadedMarks
    };

    // The 10 IDs inherited from the F-002 manifest: 0x10-spaced run.
    private static final String[] IDS_10 = {
            "0x18001A2C0", "0x18001A2D0", "0x18001A2E0", "0x18001A2F0", "0x18001A300",
            "0x18001A310", "0x18001A320", "0x18001A330", "0x18001A340", "0x18001A350"
    };

    // Containing function of the run (found by probe #1); dumped to explain the offsets.
    private static final String RUN_CONTAINER = "0x18001A240";

    @Override
    protected void run() throws Exception {
        new File(OUT_DIR).mkdirs();
        PrintWriter det = open(OUT_DIR + "/_detail.txt");
        PrintWriter dec = open(OUT_DIR + "/_decompile_detail.txt");
        PrintWriter itr = open(OUT_DIR + "/_interior.txt");

        try {
            String header = "program=" + currentProgram.getName()
                    + " exec=" + currentProgram.getExecutablePath()
                    + "\nmd5=" + currentProgram.getExecutableMD5()
                    + " imageBase=" + currentProgram.getImageBase()
                    + " ghidra=" + getGhidraVersion() + "\n";
            det.print(header);
            dec.print(header);
            itr.print(header);

            DecompInterface ifc = new DecompInterface();
            ifc.openProgram(currentProgram);

            det.println("\n===== TARGETS (v240 function entries) =====");
            dec.println("\n===== DECOMPILED (v240) =====");
            for (String s : TARGETS) {
                Address a = toAddr(s);
                Function f = (a == null) ? null : getFunctionAt(a);
                det.println("\n---- " + s + " ----");
                if (f == null) {
                    det.println("verdict=NOT_A_FUNCTION_ENTRY");
                    continue;
                }
                dumpFunction(det, f);
                dec.println("\n#### " + f.getEntryPoint() + " " + f.getName() + " ####");
                try {
                    DecompileResults res = ifc.decompileFunction(f, 180, monitor);
                    if (res != null && res.decompileCompleted()) {
                        dec.println(res.getDecompiledFunction().getC());
                    } else {
                        dec.println("/* decompile failed: "
                                + (res != null ? res.getErrorMessage() : "null") + " */");
                    }
                } catch (Exception e) {
                    dec.println("/* decompile exception: " + e + " */");
                }
            }
            ifc.dispose();

            itr.println("\n===== RUN OF 10 IDS =====");
            Address mid = toAddr("0x18001A2D0");
            MemoryBlock blk = currentProgram.getMemory().getBlock(mid);
            itr.println("section=" + (blk != null ? blk.getName() : "?")
                    + " start=" + (blk != null ? blk.getStart() : "?")
                    + " end=" + (blk != null ? blk.getEnd() : "?")
                    + " exec=" + (blk != null && blk.isExecute()));
            for (String s : IDS_10) {
                Address a = toAddr(s);
                Function f = getFunctionAt(a);
                itr.println("\n---- " + s + " ----");
                itr.println("isFunctionEntry=" + (f != null && f.getEntryPoint().equals(a)));
                Function cont = getFunctionContaining(a);
                itr.println("containingFunction=" + (cont == null ? "NONE"
                        : cont.getEntryPoint() + " " + cont.getName(true)));
                List<Symbol> syms = new ArrayList<>();
                for (Symbol sym : currentProgram.getSymbolTable().getSymbols(a)) {
                    syms.add(sym);
                }
                itr.println("symbolsAtAddress=" + (syms.isEmpty() ? "NONE" : syms.size()));
                Instruction insn = currentProgram.getListing().getInstructionContaining(a);
                if (insn == null) {
                    itr.println("instructionContaining=NONE");
                } else {
                    itr.println("instructionContaining=" + insn.getAddress() + " "
                            + insn.toString() + " (len=" + insn.getLength() + ")");
                    itr.println("isInstructionStart=" + insn.getAddress().equals(a)
                            + " deltaIntoInstruction="
                            + a.subtract(insn.getAddress()));
                }
            }

            Address ra = toAddr(RUN_CONTAINER);
            Function rf = (ra == null) ? null : getFunctionAt(ra);
            itr.println("\n===== CONTAINER FUNCTION =====");
            if (rf != null) {
                dumpFunction(itr, rf);
            } else {
                itr.println("container NOT a function entry");
            }

        } finally {
            det.close();
            dec.close();
            itr.close();
        }
        println("F002DetailProbe done -> " + OUT_DIR);
    }

    private PrintWriter open(String path) throws Exception {
        return new PrintWriter(new OutputStreamWriter(
                new java.io.FileOutputStream(path), StandardCharsets.UTF_8));
    }

    private void dumpFunction(PrintWriter out, Function f) {
        out.println("functionEntry=" + f.getEntryPoint());
        out.println("name=" + f.getName());
        out.println("fullName=" + f.getName(true));
        out.println("namespace=" + f.getParentNamespace().getName(true));
        out.println("prototype=" + f.getPrototypeString(true, true));
        out.println("body=" + f.getBody().getMinAddress() + ".." + f.getBody().getMaxAddress());
        out.println("bodySize=" + f.getBody().getNumAddresses());
        out.println("thunk=" + f.isThunk() + " external=" + f.isExternal());
        out.println("callingConvention=" + f.getCallingConventionName());
        out.println("paramCount=" + f.getParameterCount());
        Set<String> callers = new LinkedHashSet<>();
        for (Function c : f.getCallingFunctions(monitor)) {
            callers.add(c.getEntryPoint() + " " + c.getName());
        }
        out.println("callerCount=" + callers.size());
        for (String c : callers) {
            out.println("caller=" + c);
        }
        List<String> callees = new ArrayList<>();
        for (Function c : f.getCalledFunctions(monitor)) {
            callees.add(c.getEntryPoint() + " " + c.getName());
        }
        out.println("calleeCount=" + callees.size());
        for (String c : callees) {
            out.println("callee=" + c);
        }
        out.println("stringsInBody=" + String.join(" | ", stringsInBody(f)));
        ReferenceIterator ri = currentProgram.getReferenceManager()
                .getReferencesTo(f.getEntryPoint());
        int n = 0;
        while (ri.hasNext()) {
            Reference r = ri.next();
            out.println("refTo=" + r.getFromAddress() + " " + r.getReferenceType());
            n++;
        }
        out.println("refsToCount=" + n);
    }

    private List<String> stringsInBody(Function f) {
        List<String> out = new ArrayList<>();
        Listing listing = currentProgram.getListing();
        DataIterator it = listing.getDefinedData(f.getBody(), true);
        while (it.hasNext() && !monitor.isCancelled()) {
            Data d = it.next();
            String tn = d.getDataType().getName().toLowerCase();
            if (tn.contains("string") || tn.contains("unicode")) {
                Object v = d.getValue();
                if (v != null) {
                    String s = v.toString().replace('\n', ' ').replace('\r', ' ');
                    if (s.length() > 100) {
                        s = s.substring(0, 100) + "...";
                    }
                    out.add(d.getAddress() + " \"" + s + "\"");
                }
                if (out.size() >= 40) {
                    out.add("...(truncated)");
                    break;
                }
            }
        }
        return out;
    }
}
