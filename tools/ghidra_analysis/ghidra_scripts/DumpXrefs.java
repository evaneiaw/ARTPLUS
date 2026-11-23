// DumpXrefs.java - dump references to/from given addresses of the current program.
// Usage: -process <prog> -noanalysis -scriptPath <dir> -postScript DumpXrefs.java 0x180305370 [more]
// Writes H:/Desktop/ArtPlus/rag/ghidra/exports/<prog>/xrefs_focus.txt (append-safe per run).
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.LinkedHashSet;
import java.util.Set;

public class DumpXrefs extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length == 0) {
            println("ERROR: no addresses given");
            return;
        }
        String progName = currentProgram.getName();
        File outDir = new File("H:/Desktop/ArtPlus/rag/ghidra/exports/" + progName);
        outDir.mkdirs();
        File out = new File(outDir, "xrefs_focus.txt");
        try (PrintWriter pw = new PrintWriter(new FileWriter(out, true))) {
            pw.println("# DumpXrefs run: " + progName);
            for (String a : args) {
                String hex = a.startsWith("0x") || a.startsWith("0X") ? a.substring(2) : a;
                Address addr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(hex);
                pw.println("");
                pw.println("=== ADDR " + addr);
                Function fnAt = getFunctionAt(addr);
                if (fnAt == null) fnAt = getFunctionContaining(addr);
                pw.println("  function: " + (fnAt == null ? "(none)" : fnAt.getEntryPoint() + " " + fnAt.getName(true)));
                Set<String> callers = new LinkedHashSet<>();
                ReferenceIterator it = currentProgram.getReferenceManager().getReferencesTo(addr);
                pw.println("  references to (" + addr + "):");
                int n = 0;
                while (it.hasNext()) {
                    Reference r = it.next();
                    Address from = r.getFromAddress();
                    Function f = getFunctionContaining(from);
                    String fn = f == null ? "(data)" : (f.getEntryPoint() + " " + f.getName(true));
                    pw.println("    <- " + from + " [" + r.getReferenceType() + "] in " + fn);
                    callers.add(fn);
                    n++;
                }
                if (n == 0) pw.println("    (none recorded)");
                pw.println("  callers (functions):");
                if (callers.isEmpty()) pw.println("    (none)");
                for (String c : callers) pw.println("    * " + c);
                if (fnAt != null) {
                    pw.println("  callees of " + fnAt.getEntryPoint() + ":");
                    Set<Function> callees = fnAt.getCalledFunctions(monitor);
                    if (callees.isEmpty()) pw.println("    (none)");
                    for (Function c : callees) {
                        pw.println("    -> " + c.getEntryPoint() + " " + c.getName(true));
                    }
                }
            }
        }
        println("WROTE " + out.getAbsolutePath());
    }
}
