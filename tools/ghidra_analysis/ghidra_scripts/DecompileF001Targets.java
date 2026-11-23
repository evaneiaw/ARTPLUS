// DecompileF001Targets.java - decompile F-001 specific addresses for DocumentMarks.dll
// Usage: -process DocumentMarks.dll -noanalysis -scriptPath <dir> -postScript DecompileF001Targets.java <outDir> <addr1> <addr2> ...
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.ReferenceManager;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.listing.Data;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.*;

public class DecompileF001Targets extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) {
            println("Usage: DecompileF001Targets.java <outDir> <addr1> <addr2> ...");
            return;
        }
        File outDir = new File(args[0]);
        outDir.mkdirs();
        String progName = currentProgram.getName().replace(".dll", "");
        
        DecompInterface decomp = new DecompInterface();
        if (!decomp.openProgram(currentProgram)) {
            println("ERROR: could not open program in decompiler");
            return;
        }
        
        ReferenceManager refManager = currentProgram.getReferenceManager();
        
        for (int i = 1; i < args.length; i++) {
            String addrHex = args[i];
            try {
                long addrVal = Long.parseLong(addrHex.startsWith("0x") || addrHex.startsWith("0X") ? addrHex.substring(2) : addrHex, 16);
                Address addr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(addrVal);
                Function fn = currentProgram.getFunctionManager().getFunctionAt(addr);
                if (fn == null) {
                    fn = currentProgram.getFunctionManager().getFunctionContaining(addr);
                }
                if (fn == null) {
                    println("No function at 0x" + addrHex);
                    continue;
                }
                
                String safeName = fn.getName().replaceAll("[^A-Za-z0-9_]", "_");
                File md = new File(outDir, progName + "__" + addrHex.toUpperCase() + ".md");
                
                // Get xrefs (callers)
                List<String> xrefs = new ArrayList<>();
                ReferenceIterator ri = refManager.getReferencesTo(fn.getEntryPoint());
                while (ri.hasNext()) {
                    Reference r = ri.next();
                    Function caller = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                    String cname = (caller != null) ? caller.getName() + " @ " + caller.getEntryPoint() : "unknown";
                    xrefs.add(r.getFromAddress() + " -> " + cname + " (" + r.getReferenceType() + ")");
                }
                
                // Get callees
                List<String> callees = new ArrayList<>();
                try {
                    Set<Function> called = fn.getCalledFunctions(monitor);
                    for (Function c : called) {
                        callees.add(c.getEntryPoint() + " " + c.getName());
                    }
                } catch (Exception e) {
                    callees.add("ERROR: " + e.getMessage());
                }
                
                // Get referenced strings in function body
                List<String> strs = new ArrayList<>();
                Set<String> seen = new HashSet<>();
                var listing = currentProgram.getListing();
                var instIter = listing.getInstructions(fn.getBody(), true);
                while (instIter.hasNext()) {
                    var ins = instIter.next();
                    Reference[] refs = refManager.getReferencesFrom(ins.getAddress());
                    for (Reference r : refs) {
                        Address to = r.getToAddress();
                        Data data = listing.getDataAt(to);
                        if (data != null) {
                            Object val = data.getValue();
                            if (val != null) {
                                String s = val.toString();
                                if (s.length() >= 3 && !seen.contains(s)) {
                                    seen.add(s);
                                    strs.add(to + " : " + s);
                                }
                            }
                        }
                    }
                }
                
                // Decompile
                DecompileResults res = decomp.decompileFunction(fn, 120, monitor);
                String code = "";
                if (res != null && res.decompileCompleted() && res.getDecompiledFunction() != null) {
                    code = res.getDecompiledFunction().getC();
                } else {
                    code = "// DECOMPILE FAILED: " + (res != null ? res.getErrorMessage() : "null");
                }
                
                // Write markdown
                try (PrintWriter pw = new PrintWriter(new FileWriter(md))) {
                    pw.println("```yaml");
                    pw.println("modulo: " + progName + ".dll");
                    pw.println("versao: 24.03.10017");
                    pw.println("funcao: " + fn.getEntryPoint().toString().toUpperCase());
                    pw.println("nome: " + fn.getName(true));
                    pw.println("confianca: media");
                    pw.println("xrefs: " + (xrefs.isEmpty() ? "[]" : xrefs.toString().replace("\n", "")));
                    pw.println("strings: " + (strs.isEmpty() ? "[]" : strs.toString().replace("\n", "")));
                    pw.println("```");
                    pw.println();
                    pw.println("## Assinatura");
                    pw.println("```c");
                    pw.println(fn.getPrototypeString(false, false));
                    pw.println("```");
                    pw.println();
                    pw.println("## Xrefs de entrada (callers)");
                    if (xrefs.isEmpty()) pw.println("(nenhum)");
                    for (String x : xrefs) pw.println("- " + x);
                    pw.println();
                    pw.println("## Xrefs de saida (callees)");
                    if (callees.isEmpty()) pw.println("(nenhum)");
                    for (String c : callees) pw.println("- " + c);
                    pw.println();
                    pw.println("## Strings referenciadas no corpo");
                    if (strs.isEmpty()) pw.println("(nenhuma)");
                    for (String s : strs) pw.println("- " + s);
                    pw.println();
                    pw.println("## Pseudocodigo (Ghidra Decompiler)");
                    pw.println("```c");
                    pw.println(code);
                    pw.println("```");
                    pw.println();
                    pw.println("---");
                    pw.println("_Fonte: Ghidra 12.2 headless, " + currentProgram.getName() + ", " + fn.getEntryPoint().toString().toUpperCase() + "_");
                }
                println("WROTE " + md.getAbsolutePath());
            } catch (Exception e) {
                println("Error processing 0x" + addrHex + ": " + e.getMessage());
            }
        }
        
        decomp.dispose();
    }
}