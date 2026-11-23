// ExportDecompiled.java - Ghidra Script to export decompiled pseudocode for selected functions
// with xrefs (callers/callees) and referenced strings.
// Run with: analyzeHeadless <project> <name> -process LayoutEngine.dll -postScript ExportDecompiled.java -scriptPath <path>

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressFactory;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.listing.Data;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.ReferenceManager;
import ghidra.util.task.TaskMonitor;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.*;

public class ExportDecompiled extends GhidraScript {

    // Target function entry points (LayoutEngine.dll v240)
    private static final String[] TARGETS = new String[] {
        "0x180013d00", // GlobalEngine::GenerateLayout
        "0x18002d570", // NestingSheetGenerator::Nest
        "0x18001d5a0", // GuillotineSheetGenerator::GenerateClassicSolution
        "0x180028490", // NestingSheetGenerator::GenerateClassicSolution
        "0x180022600", // ManualLayoutEngine::GenerateBleedLayout
        "0x18000c1f0", // LayoutEngine::MakeGridLayout
        "0x180025820", // NestingSheetGenerator::ClassicFillSheet
        "0x1800261f0", // NestingSheetGenerator::ClassicMinimalLayouts
        "0x18002d610", // NestingSheetGenerator::SetUpNest
        "0x180009fc0"  // LayoutEngine::ApplyBleedOnGridLayout
    };

    @Override
    protected void run() throws Exception {
        String projectName = currentProgram.getName();
        File outputDir = new File("H:/Desktop/ArtPlus/rag/ghidra/exports/" + projectName + "/decompiled");
        outputDir.mkdirs();

        DecompInterface decomp = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        decomp.setOptions(opts);
        decomp.openProgram(currentProgram);

        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager refManager = currentProgram.getReferenceManager();
        AddressFactory af = currentProgram.getAddressFactory();

        for (String t : TARGETS) {
            Address addr = af.getAddress(t);
            Function func = fm.getFunctionAt(addr);
            if (func == null) {
                println("Function not found at " + t);
                continue;
            }

            // Decompile
            DecompileResults res = decomp.decompileFunction(func, 120, monitor);
            String code = "";
            if (res != null && res.decompileCompleted()) {
                code = res.getDecompiledFunction().getC();
            } else {
                code = "// DECOMPILE FAILED: " + (res != null ? res.getErrorMessage() : "null");
            }

            // Callers (xrefs to entry point)
            List<String> callers = new ArrayList<>();
            ReferenceIterator ri = refManager.getReferencesTo(addr);
            while (ri.hasNext()) {
                Reference r = ri.next();
                Function caller = fm.getFunctionContaining(r.getFromAddress());
                String cname = (caller != null) ? caller.getName() + " @ " + caller.getEntryPoint() : "unknown";
                callers.add(r.getFromAddress() + " -> " + cname + " (" + r.getReferenceType() + ")");
            }

            // Callees
            List<String> callees = new ArrayList<>();
            try {
                Set<Function> called = func.getCalledFunctions(monitor);
                for (Function c : called) {
                    callees.add(c.getEntryPoint() + " " + c.getName());
                }
            } catch (Exception e) {
                callees.add("ERROR: " + e.getMessage());
            }

            // Referenced strings: scan instructions in function body
            List<String> strs = new ArrayList<>();
            Set<String> seen = new HashSet<>();
            InstructionIterator ii = currentProgram.getListing().getInstructions(func.getBody(), true);
            while (ii.hasNext()) {
                Instruction ins = ii.next();
                Reference[] refs = refManager.getReferencesFrom(ins.getAddress());
                for (Reference r : refs) {
                    Address to = r.getToAddress();
                    Data data = currentProgram.getListing().getDataAt(to);
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

            // Write file
            String safeName = func.getName().replaceAll("[^A-Za-z0-9_]", "_");
            File outFile = new File(outputDir, String.format("%s__%s.md", safeName, addr.toString()));
            try (PrintWriter pw = new PrintWriter(new FileWriter(outFile))) {
                pw.println("modulo: LayoutEngine.dll");
                pw.println("versao: 24.0");
                pw.println("funcao: " + addr);
                pw.println("nome: " + func.getName());
                pw.println("assinatura: " + func.getSignature().getPrototypeString());
                pw.println("parametros: " + func.getParameterCount());
                pw.println("retorno: " + func.getReturnType().getName());
                pw.println();
                pw.println("## Callers (xrefs de entrada)");
                if (callers.isEmpty()) pw.println("(nenhum)");
                for (String c : callers) pw.println("- " + c);
                pw.println();
                pw.println("## Callees (xrefs de saida)");
                if (callees.isEmpty()) pw.println("(nenhum)");
                for (String c : callees) pw.println("- " + c);
                pw.println();
                pw.println("## Strings referenciadas");
                if (strs.isEmpty()) pw.println("(nenhuma)");
                for (String s : strs) pw.println("- " + s);
                pw.println();
                pw.println("## Pseudocodigo (Ghidra Decompiler)");
                pw.println("```c");
                pw.println(code);
                pw.println("```");
            }
            println("Exported " + func.getName() + " @ " + addr + " -> " + outFile.getAbsolutePath());
        }

        decomp.dispose();
        println("Decompile export complete.");
    }
}
