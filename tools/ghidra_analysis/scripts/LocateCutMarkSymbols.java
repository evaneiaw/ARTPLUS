// LocateCutMarkSymbols.java
// Lists v240 functions/symbols relevant to Cut Mark so spec IDs (captured on
// v25) can be mapped to their real v240 entries. Read-only.

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;

public class LocateCutMarkSymbols extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        File out = new File(args.length > 0 ? args[0]
                : "H:/Desktop/ArtPlus/rag/evidence/F-001/ghidra/raw_v240/_cutmark_symbols.txt");
        out.getParentFile().mkdirs();
        PrintWriter w = new PrintWriter(new OutputStreamWriter(new FileOutputStream(out), StandardCharsets.UTF_8));
        w.println("program=" + currentProgram.getName());
        w.println("executablePath=" + currentProgram.getExecutablePath());
        w.println("executableSHA256=" + currentProgram.getExecutableSHA256());
        w.println();
        w.println("[FUNCTIONS_MATCHING_CUTMARK]");
        FunctionIterator fit = currentProgram.getFunctionManager().getFunctions(true);
        int n = 0;
        while (fit.hasNext() && !monitor.isCancelled()) {
            Function f = fit.next();
            String q = f.getName(true);
            String simple = f.getName();
            String ql = q.toLowerCase();
            String sl = simple.toLowerCase();
            if (ql.contains("cutmark") || sl.contains("cutmark")
                    || ql.contains("marksfromset") || ql.contains("applyrelevantmark")
                    || ql.contains("marks/page") || ql.contains("copymarkstopage")
                    || ql.contains("getpagebox") || ql.contains("getreferencebox")) {
                w.println(f.getEntryPoint() + "\t" + q + "\t" + f.getPrototypeString(false, false));
                n++;
            }
        }
        w.println("#count=" + n);
        w.println();
        w.println("[ADDRESS_LOOKUP]");
        for (int i = 1; i < args.length; i++) {
            Address a = currentProgram.getAddressFactory().getAddress(args[i]);
            Function f = currentProgram.getFunctionManager().getFunctionContaining(a);
            Function fe = currentProgram.getFunctionManager().getFunctionAt(a);
            w.println(args[i] + "\tcontains=" + (f != null ? f.getEntryPoint() + " " + f.getName(true) : "none")
                    + "\tentry=" + (fe != null ? fe.getName(true) : "none"));
        }
        w.close();
        println("wrote " + out.getAbsolutePath());
    }
}
