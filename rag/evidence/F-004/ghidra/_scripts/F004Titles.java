// F004Titles.java - dump GetTitle/GetDescription/LogConfiguration of the selection operators
// so the UI/action-list strings of PDFObjectActions.dll (v24.03.10017) are traceable.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import java.io.*;
import java.util.*;

public class F004Titles extends GhidraScript {

    private static final String[] CLASSES = {
        "GOVChangeScaleSelection",
        "GOVChangeRotateSelection",
        "GOVChangeFlipSelection",
        "GOVSelectOverlappingObjects",
        "GOVSelectOverlapping",
        "GOVSelectObjects",
        "GOVSelectHitElement",
        "GOVCloneSelection",
        "GOVGetSelectedObjects",
        "GOVChangeRasterizeSelection",
        "GOVChangeSelectionToForm"
    };

    private static final String[] METHODS = {
        "GetTitle", "GetDescription", "LogConfiguration", "GetReportCategory"
    };

    @Override
    protected void run() throws Exception {
        String outDir = "H:/Desktop/ArtPlus/rag/evidence/F-004/ghidra/_raw";
        new File(outDir).mkdirs();
        PrintWriter index = new PrintWriter(new FileWriter(new File(outDir, "index_titles.tsv")));
        index.println("address\tname\tbytes\tstring_refs");
        DecompInterface dec = new DecompInterface();
        dec.openProgram(currentProgram);

        int n = 0;
        FunctionIterator fit = currentProgram.getFunctionManager().getFunctions(true);
        while (fit.hasNext() && !monitor.isCancelled()) {
            Function f = fit.next();
            String nm = f.getName(true);
            int c = nm.indexOf("::");
            if (c < 0) continue;
            String cls = nm.substring(0, c);
            String meth = nm.substring(c + 2);
            boolean hit = false;
            for (String k : CLASSES) if (cls.equals(k)) { hit = true; break; }
            if (!hit) continue;
            hit = false;
            for (String m : METHODS) if (meth.equals(m)) { hit = true; break; }
            if (!hit) continue;

            LinkedHashMap<String, String> strings = new LinkedHashMap<>();
            InstructionIterator iit = currentProgram.getListing().getInstructions(f.getBody(), true);
            while (iit.hasNext()) {
                Instruction ins = iit.next();
                for (Reference r : ins.getReferencesFrom()) {
                    Data d = getDataAt(r.getToAddress());
                    if (d != null && d.getValue() != null) {
                        String dt = d.getDataType().getName();
                        if (dt.contains("string") || dt.contains("String") || dt.contains("unicode")) {
                            strings.put(r.getToAddress().toString(),
                                    d.getValue().toString().replace("\n", " ").replace("\r", " "));
                        }
                    }
                }
            }

            PrintWriter pw = new PrintWriter(new FileWriter(new File(outDir,
                    "PDFObjectActions__" + f.getEntryPoint() + ".titles.txt")));
            pw.println("address: " + f.getEntryPoint());
            pw.println("name: " + nm);
            pw.println("signature: " + f.getPrototypeString(true, true));
            pw.println("body_bytes: " + f.getBody().getNumAddresses());
            pw.println("[string_refs]");
            for (Map.Entry<String, String> e : strings.entrySet()) {
                pw.println("  " + e.getKey() + " " + e.getValue());
            }
            pw.println("[decompiled]");
            DecompileResults res = dec.decompileFunction(f, 120, monitor);
            pw.println(res != null && res.decompileCompleted()
                    ? res.getDecompiledFunction().getC() : "(decompile failed)");
            pw.flush();
            pw.close();
            index.println(f.getEntryPoint() + "\t" + nm + "\t" + f.getBody().getNumAddresses()
                    + "\t" + strings.size());
            n++;
        }
        index.flush();
        index.close();
        dec.dispose();
        println("F004Titles: " + n + " functions");
    }
}
