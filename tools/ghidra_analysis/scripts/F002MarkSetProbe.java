// F002MarkSetProbe.java - F-002 (Mark Set) static evidence probe against DocumentMarks.dll v24.03.10017
//
// Run (headless, project DocMarks_v240, read-only):
//   analyzeHeadless <projdir> DocMarks_v240 -process -noanalysis
//        -scriptPath tools/ghidra_analysis/scripts -postScript F002MarkSetProbe.java
//
// Writes ASCII/UTF-8 (no BOM) files:
//   rag/evidence/F-002/ghidra/raw_v240/_probe.txt      - per-address verdict (isFunctionEntry etc.)
//   rag/evidence/F-002/ghidra/raw_v240/_names.txt      - symbol search for Mark Set related names
//   rag/evidence/F-002/ghidra/raw_v240/_decompile.txt  - decompiled C of every function entry found
//
// This script only reads the program. It does not modify the project database.

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.symbol.SymbolTable;

import java.io.File;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

public class F002MarkSetProbe extends GhidraScript {

    private static final String OUT_DIR =
            "H:/Desktop/ArtPlus/rag/evidence/F-002/ghidra/raw_v240";

    // IDs currently declared for F-002 (historical / v250 layout) + section-8 probe list.
    private static final String[] ADDRESSES = {
            "0x18001A2C0", "0x18001A2D0", "0x18001A2E0", "0x18001A2F0", "0x18001A300",
            "0x18001A310", "0x18001A320", "0x18001A330", "0x18001A340", "0x18001A350",
            "0x18024D3E0", "0x18024D460", "0x18024E9B0", "0x180251790"
    };

    // A4 coverage list, taken from old export names; may belong to another version.
    private static final String[] NAME_NEEDLES = {
            "ApplyMarkSet", "ApplyMarkSetToPage", "CopyMarksToPage", "ApplyMarksFromSet",
            "ApplyRelevantMarkSets", "ApplyRelevantMarkSetsWithReuse", "CopyMarksToPageWithLog",
            "PrepareMarksCachePage", "PrepareMarksCache", "RecreateLoadedMarks",
            "ReadMarkSetFile", "MakeFormsFromMarks", "MarkSets"
    };

    @Override
    protected void run() throws Exception {
        new File(OUT_DIR).mkdirs();

        PrintWriter probe = open(OUT_DIR + "/_probe.txt");
        PrintWriter names = open(OUT_DIR + "/_names.txt");
        PrintWriter dec   = open(OUT_DIR + "/_decompile.txt");

        try {
            String header = "program=" + currentProgram.getName()
                    + " exec=" + currentProgram.getExecutablePath()
                    + "\nmd5=" + currentProgram.getExecutableMD5()
                    + " imageBase=" + currentProgram.getImageBase()
                    + " language=" + currentProgram.getLanguageID()
                    + " ghidra=" + getGhidraVersion()
                    + "\n";
            probe.print(header);
            names.print(header);
            dec.print(header);

            decompileTargets(probe, dec);

            // Probe every address from the ID list
            probe.println("\n===== ADDRESS PROBE =====");
            for (String s : ADDRESSES) {
                probeAddress(probe, s);
            }

            // Symbol name search
            names.println("\n===== SYMBOL SEARCH =====");
            searchNames(names);

        } finally {
            probe.close();
            names.close();
            dec.close();
        }
        println("F002MarkSetProbe done -> " + OUT_DIR);
    }

    private PrintWriter open(String path) throws Exception {
        return new PrintWriter(new java.io.OutputStreamWriter(
                new java.io.FileOutputStream(path), StandardCharsets.UTF_8));
    }

    private void probeAddress(PrintWriter out, String s) {
        out.println("---- " + s + " ----");
        Address a;
        try {
            a = toAddr(s);
        } catch (Exception e) {
            out.println("verdict=UNPARSEABLE");
            return;
        }
        if (a == null) {
            out.println("verdict=ADDRESS_OUTSIDE_MEMORY");
            return;
        }
        Function f = getFunctionAt(a);
        boolean entry = (f != null) && f.getEntryPoint().equals(a);
        out.println("isFunctionEntry=" + entry);
        if (!entry) {
            Function cont = getFunctionContaining(a);
            if (cont == null) {
                out.println("containingFunction=NONE");
            } else {
                out.println("containingFunction=" + cont.getEntryPoint() + " " + cont.getName());
                long off = a.subtract(cont.getEntryPoint());
                out.println("offsetIntoContaining=0x" + Long.toHexString(off));
            }
            List<Symbol> syms = new ArrayList<>();
            for (Symbol sym : currentProgram.getSymbolTable().getSymbols(a)) {
                syms.add(sym);
            }
            if (syms.isEmpty()) {
                out.println("symbolsAtAddress=NONE");
            } else {
                for (Symbol sym : syms) {
                    out.println("symbolAtAddress=" + sym.getSymbolType() + " " + sym.getName()
                            + " parent=" + (sym.getParentSymbol() != null
                            ? sym.getParentSymbol().getName() : "-"));
                }
            }
            ReferenceIterator ri = currentProgram.getReferenceManager().getReferencesTo(a);
            int n = 0;
            while (ri.hasNext()) {
                Reference r = ri.next();
                out.println("refTo=" + r.getFromAddress() + " " + r.getReferenceType());
                n++;
            }
            out.println("refsToCount=" + n);
            return;
        }
        dumpFunctionSummary(out, f);
    }

    private void dumpFunctionSummary(PrintWriter out, Function f) {
        out.println("functionEntry=" + f.getEntryPoint());
        out.println("name=" + f.getName());
        out.println("namespace=" + f.getParentNamespace().getName(true));
        out.println("prototype=" + f.getPrototypeString(true, true));
        out.println("body=" + f.getBody().getMinAddress() + ".." + f.getBody().getMaxAddress());
        out.println("thunk=" + f.isThunk() + " external=" + f.isExternal());
        out.println("callingConvention=" + f.getCallingConventionName());
        out.println("paramCount=" + f.getParameterCount());
        out.println("stackFrameSize=" + (f.getStackFrame() != null
                ? f.getStackFrame().getFrameSize() : -1));
        Set<String> callers = new LinkedHashSet<>();
        for (Function c : f.getCallingFunctions(monitor)) {
            callers.add(c.getEntryPoint() + " " + c.getName());
        }
        if (callers.isEmpty()) {
            out.println("callers=NONE");
        } else {
            for (String c : callers) {
                out.println("caller=" + c);
            }
        }
        Set<String> callees = new LinkedHashSet<>();
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
                    if (s.length() > 120) {
                        s = s.substring(0, 120) + "...";
                    }
                    out.add(d.getAddress() + " [" + d.getDataType().getName() + "] \"" + s + "\"");
                }
                if (out.size() >= 40) {
                    out.add("...(truncated)");
                    break;
                }
            }
        }
        return out;
    }

    private void decompileTargets(PrintWriter probe, PrintWriter dec) {
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        dec.println("\n===== DECOMPILED =====");
        for (String s : ADDRESSES) {
            Address a = toAddr(s);
            if (a == null) {
                continue;
            }
            Function f = getFunctionAt(a);
            if (f == null || !f.getEntryPoint().equals(a)) {
                continue;
            }
            dec.println("\n#### " + f.getEntryPoint() + " " + f.getName() + " ####");
            try {
                DecompileResults res = ifc.decompileFunction(f, 120, monitor);
                if (res != null && res.decompileCompleted()) {
                    String c = res.getDecompiledFunction().getC();
                    dec.println(c);
                    probe.println("decompiled=" + f.getEntryPoint() + " lines="
                            + (c.split("\n").length));
                } else {
                    dec.println("/* decompile failed: "
                            + (res != null ? res.getErrorMessage() : "null") + " */");
                }
            } catch (Exception e) {
                dec.println("/* decompile exception: " + e + " */");
            }
        }
        ifc.dispose();
    }

    private void searchNames(PrintWriter out) {
        SymbolTable st = currentProgram.getSymbolTable();
        SymbolIterator it = st.getAllSymbols(true);
        List<String> hits = new ArrayList<>();
        while (it.hasNext() && !monitor.isCancelled()) {
            Symbol sym = it.next();
            String name = sym.getName();
            for (String needle : NAME_NEEDLES) {
                if (name.toLowerCase().contains(needle.toLowerCase())) {
                    hits.add(sym.getAddress() + "\t" + sym.getSymbolType() + "\t"
                            + sym.getName(true));
                    break;
                }
            }
        }
        out.println("hits=" + hits.size());
        for (String h : hits) {
            out.println(h);
        }
    }
}
