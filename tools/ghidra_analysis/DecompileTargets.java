// Ghidra script - exportar pseudocódigo de funções específicas (F-006 Save Document)
// Run: analyzeHeadless <project> <program> -process <file> -scriptPath <dir> -postScript DecompileTargets.java <outDir> <addr1> <addr2> ...

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.symbol.Symbol;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.*;

public class DecompileTargets extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 3) {
            println("Usage: DecompileTargets.java <outDir> <addr1> <addr2> ...");
            return;
        }
        File outDir = new File(args[0]);
        outDir.mkdirs();
        
        String progName = currentProgram.getName().replace(".dll", "").replace(".exe", "");
        
        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        
        for (int i = 1; i < args.length; i++) {
            String addrHex = args[i];
            try {
                long addrVal = Long.parseLong(addrHex, 16);
                Address addr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(addrVal);
                Function fn = currentProgram.getFunctionManager().getFunctionAt(addr);
                if (fn == null) {
                    println("No function at 0x" + addrHex);
                    continue;
                }
                
                String safeName = fn.getName().replaceAll("[^A-Za-z0-9_]", "_");
                File md = new File(outDir, progName + "__" + addrHex + ".md");
                
                try (PrintWriter pw = new PrintWriter(new FileWriter(md))) {
                    String demangled = bestDemangled(fn);
                    pw.println("# " + progName + " " + fn.getEntryPoint().toString());
                    pw.println("```yaml");
                    pw.println("modulo: " + progName + ".dll");
                    pw.println("versao: 24.0");
                    pw.println("funcao: 0x" + addrHex);
                    pw.println("nome: " + demangled);
                    pw.println("mangled: " + fn.getName());
                    pw.println("confianca: alta");
                    pw.println("xrefs: []");
                    pw.println("strings: []");
                    pw.println("```");
                    pw.println();
                    pw.println("## Assinatura");
                    pw.println("```c");
                    pw.println(fn.getPrototypeString(false, false));
                    pw.println("```");
                    pw.println();
                    pw.println("## Pseudocódigo (decompilado)");
                    pw.println("```c");
                    DecompileResults res = decomp.decompileFunction(fn, 120, monitor);
                    if (res != null && res.decompileCompleted()) {
                        pw.println(res.getDecompiledFunction().getC());
                    } else {
                        pw.println("// decompilacao falhou: " + (res != null ? res.getErrorMessage() : "null"));
                    }
                    pw.println("```");
                    pw.println();
                    pw.println("---");
                    pw.println("_Fonte: Ghidra 12.2 headless, " + currentProgram.getName() + ", 0x" + addrHex + "_");
                }
                println("Wrote " + md.getAbsolutePath());
            } catch (Exception e) {
                println("Error processing 0x" + addrHex + ": " + e.getMessage());
            }
        }
        
        decomp.dispose();
    }

    private String bestDemangled(Function fn) {
        ghidra.program.model.symbol.Symbol primary = currentProgram.getSymbolTable().getPrimarySymbol(fn.getEntryPoint());
        String best = primary != null ? primary.getName() : fn.getName();
        for (ghidra.program.model.symbol.Symbol sym : currentProgram.getSymbolTable().getSymbols(fn.getEntryPoint())) {
            String n = sym.getName();
            if (n.contains("@") || n.contains("::")) {
                if (n.length() > best.length()) {
                    best = n;
                }
            }
        }
        return best;
    }
}
