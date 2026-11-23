// F004Probe.java - identity + selection/resize symbol and string probe
// (F-004 static evidence, PDFObjectActions.dll v24.03.10017)
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import java.io.*;
import java.util.*;

public class F004Probe extends GhidraScript {

    private PrintWriter pw;

    @Override
    protected void run() throws Exception {
        String outDir = "H:/Desktop/ArtPlus/rag/evidence/F-004/ghidra/_probe";
        new File(outDir).mkdirs();
        pw = new PrintWriter(new FileWriter(new File(outDir, "probe.txt")));

        pw.println("program=" + currentProgram.getName());
        pw.println("imageBase=" + currentProgram.getImageBase());
        pw.println("language=" + currentProgram.getLanguageID());
        pw.println("compiler=" + currentProgram.getCompilerSpec().getCompilerSpecID());
        pw.println("executableMD5=" + currentProgram.getExecutableMD5());
        pw.println("executableSHA256=" + currentProgram.getExecutableSHA256());
        pw.println("executablePath=" + currentProgram.getExecutablePath());
        pw.println("creationDate=" + currentProgram.getCreationDate());
        int fcount = currentProgram.getFunctionManager().getFunctionCount();
        pw.println("functionCount=" + fcount);

        pw.println();
        pw.println("[FUNCTIONS matching selection/resize/hit/transform/gov/select]");
        FunctionIterator fit = currentProgram.getFunctionManager().getFunctions(true);
        while (fit.hasNext() && !monitor.isCancelled()) {
            Function f = fit.next();
            String n = f.getName(true);
            String l = n.toLowerCase();
            if (l.contains("select") || l.contains("resize") || l.contains("hit")
                || l.contains("transform") || l.contains("handle") || l.contains("rubber")) {
                pw.println(f.getEntryPoint() + "\t" + n + "\tparams=" + f.getParameterCount()
                        + "\tsize=" + f.getBody().getNumAddresses());
            }
        }

        pw.println();
        pw.println("[SYMBOLS matching selection/resize/hit/transform/gov/select]");
        SymbolIterator sit = currentProgram.getSymbolTable().getAllSymbols(true);
        while (sit.hasNext() && !monitor.isCancelled()) {
            Symbol s = sit.next();
            String n = s.getName(true);
            String l = n.toLowerCase();
            if (l.contains("select") || l.contains("resize") || l.contains("hit")
                || l.contains("transform") || l.contains("gov")) {
                pw.println(s.getAddress() + "\t" + s.getSymbolType() + "\t" + n
                        + "\tns=" + (s.getParentNamespace() == null ? "" : s.getParentNamespace().getName(true)));
            }
        }

        pw.println();
        pw.println("[STRINGS matching selection/resize/hit/transform/cropbox/mark]");
        DataIterator dit = currentProgram.getListing().getDefinedData(true);
        while (dit.hasNext() && !monitor.isCancelled()) {
            Data d = dit.next();
            String dt = d.getDataType().getName();
            if (!dt.contains("string") && !dt.contains("String") && !dt.contains("unicode")) {
                continue;
            }
            Object v = d.getValue();
            if (v == null) continue;
            String s = v.toString();
            String l = s.toLowerCase();
            if (l.contains("select") || l.contains("resize") || l.contains("hit")
                || l.contains("transform") || l.contains("cropbox") || l.contains("selectionmark")) {
                pw.println(d.getAddress() + "\t" + s.replace("\n", " ").replace("\r", " "));
            }
        }

        pw.println();
        pw.println("[EXPORTED SYMBOLS (from symbol table, type FUNCTION with external=false and namespace global)]");
        SymbolTable st = currentProgram.getSymbolTable();
        for (Symbol s : st.getDefinedSymbols()) {
            if (s.isExternal() == false && s.getSymbolType() == SymbolType.FUNCTION) {
                // nothing; keep output small
            }
        }

        pw.flush();
        pw.close();
        println("F004Probe done");
    }
}
