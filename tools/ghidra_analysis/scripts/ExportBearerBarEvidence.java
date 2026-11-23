// ExportBearerBarEvidence.java
// Ghidra 12.2 headless post-script.
// Dumps identity + per-address function evidence (decompile, callers, callees,
// referenced strings, xrefs, vtable-ish data context) for the F-003 Bearer Bar set.
//
// Usage:
//   analyzeHeadless <proj> ArtProPlus -process DocumentMarks.dll -noanalysis \
//     -scriptPath <dir> -postScript ExportBearerBarEvidence.java <outDir> <addr> [<addr> ...]

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.data.DataType;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ExportBearerBarEvidence extends GhidraScript {

    private static final String[] KEYWORDS = {
        "Bearer", "BearerBar", "AIDynamicMarks-BearerBar",
        "DM-BearerBarParams", "DynamicObject_PDFPlusBearerBar",
        "DocumentMarks_BearerBar_ReferenceID",
        "PDFPlusBearerBar_OriginalReferenceName",
        "Vertical offset in bearer bar not supported",
        "Position", "Reference", "ReferenceID", "Offset", "Extends",
        "SourceAnchor", "ReferenceAnchor", "ObjectID", "IsVertical", "Location",
        "PageBox", "ProcessingStepLayer",
        "LeftMostGridLayout", "RightMostGridLayout", "LeftMostGridLayoutColumn",
        "RightMostGridLayoutColumn", "TopMostGridLayout", "BottomMostGridLayout",
        "TopMostGridLayoutRow", "BottomMostGridLayoutRow",
        "TrimBox", "Trim Box", "MediaBox", "Media Box", "CropBox", "Crop Box",
        "BleedBox", "Bleed Box", "ArtBox", "Art Box",
        "update at", "Bearer Bar update"
    };

    private PrintWriter log;

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        File outDir = new File(args.length > 0 ? args[0]
                : "H:/Desktop/ArtPlus/rag/evidence/F-003/ghidra/raw_v240");
        outDir.mkdirs();

        log = open(new File(outDir, "_identity.txt"));
        log.println("program=" + currentProgram.getName());
        log.println("executablePath=" + currentProgram.getExecutablePath());
        log.println("executableSHA256=" + currentProgram.getExecutableSHA256());
        log.println("executableMD5=" + currentProgram.getExecutableMD5());
        log.println("imageBase=" + currentProgram.getImageBase());
        log.println("language=" + currentProgram.getLanguageID());
        log.println("compiler=" + currentProgram.getCompilerSpec().getCompilerSpecID());
        log.println("functionCount=" + currentProgram.getFunctionManager().getFunctionCount());
        log.println("targetAddressArgs=" + String.join(",", java.util.Arrays.copyOfRange(args, 1, args.length)));
        log.flush();
        log.close();

        dumpStringKeywords(outDir);

        DecompInterface dec = new DecompInterface();
        dec.openProgram(currentProgram);

        for (int i = 1; i < args.length; i++) {
            String a = args[i].trim();
            if (a.isEmpty()) {
                continue;
            }
            Address addr = currentProgram.getAddressFactory().getAddress(a);
            if (addr == null) {
                println("INVALID ADDRESS " + a);
                continue;
            }
            dumpOne(dec, outDir, addr, a);
        }
        dec.dispose();
        println("ExportBearerBarEvidence done -> " + outDir.getAbsolutePath());
    }

    private void dumpOne(DecompInterface dec, File outDir, Address addr, String raw) throws Exception {
        String hex = String.format("%x", addr.getUnsignedOffset());
        PrintWriter w = open(new File(outDir, "addr_" + hex + ".txt"));
        w.println("requested=" + raw);
        w.println("resolvedAddress=" + addr);
        w.println("minAddress=" + currentProgram.getMinAddress());
        w.println("inMemory=" + currentProgram.getMemory().contains(addr));

        Function containing = currentProgram.getFunctionManager().getFunctionContaining(addr);
        Function func = currentProgram.getFunctionManager().getFunctionAt(addr);
        w.println("isFunctionEntry=" + (func != null));
        if (func == null && containing != null) {
            w.println("containingFunction=" + containing.getEntryPoint() + " " + containing.getName());
        } else if (containing != null) {
            w.println("containingFunction=" + containing.getEntryPoint() + " " + containing.getName());
        } else {
            w.println("containingFunction=");
        }

        if (func == null) {
            w.println("status=NO_FUNCTION_AT_ENTRY");
            // still dump bytes around address for forensics
            w.println("bytes=" + bytesAt(addr, 32));
            w.close();
            println("NO FUNCTION at " + raw);
            return;
        }

        w.println("status=OK");
        w.println("entry=" + func.getEntryPoint());
        w.println("name=" + func.getName());
        w.println("qualifiedName=" + func.getName(true));
        w.println("namespace=" + (func.getParentNamespace() != null ? func.getParentNamespace().getName(true) : ""));
        w.println("signature=" + func.getPrototypeString(false, false));
        w.println("returnType=" + func.getReturnType().getName());
        w.println("parameterCount=" + func.getParameterCount());
        w.println("bodyMin=" + func.getBody().getMinAddress());
        w.println("bodyMax=" + func.getBody().getMaxAddress());
        w.println("bodySize=" + func.getBody().getNumAddresses());
        w.println("isThunk=" + func.isThunk());
        w.println("isExternal=" + func.isExternal());
        w.println("callingConvention=" + func.getCallingConventionName());

        // xrefs to entry
        w.println();
        w.println("[XREFS_TO]");
        ReferenceIterator rit = currentProgram.getReferenceManager().getReferencesTo(func.getEntryPoint());
        while (rit.hasNext()) {
            Reference r = rit.next();
            Function fromF = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
            w.println(r.getFromAddress() + " refType=" + r.getReferenceType()
                    + " fromFunction=" + (fromF != null ? fromF.getEntryPoint() + " " + fromF.getName() : ""));
        }

        // callers
        w.println();
        w.println("[CALLERS]");
        for (Function c : func.getCallingFunctions(monitor)) {
            w.println(c.getEntryPoint() + " " + c.getName(true));
        }

        // callees
        w.println();
        w.println("[CALLEES]");
        for (Function c : func.getCalledFunctions(monitor)) {
            w.println(c.getEntryPoint() + " " + c.getName(true));
        }

        // instruction-level direct call/jump targets (includes unresolved ones)
        w.println();
        w.println("[DIRECT_CALL_TARGETS]");
        Set<String> seen = new LinkedHashSet<>();
        InstructionIterator iit = currentProgram.getListing().getInstructions(func.getBody(), true);
        while (iit.hasNext()) {
            Instruction ins = iit.next();
            if (ins.getFlowType().isCall() || ins.getFlowType().isJump()) {
                Reference[] refs = ins.getReferencesFrom();
                for (Reference r : refs) {
                    if (!r.getReferenceType().isCall() && !r.getReferenceType().isJump()) {
                        continue;
                    }
                    Address t = r.getToAddress();
                    Function tf = currentProgram.getFunctionManager().getFunctionContaining(t);
                    String key = ins.getAddress() + " -> " + t + " "
                            + (tf != null ? tf.getName(true) : symbolAt(t));
                    if (seen.add(key)) {
                        w.println(key);
                    }
                }
            }
        }

        // referenced strings inside body
        w.println();
        w.println("[STRINGS_REFERENCED]");
        TreeSet<String> strs = new TreeSet<>();
        iit = currentProgram.getListing().getInstructions(func.getBody(), true);
        while (iit.hasNext()) {
            Instruction ins = iit.next();
            for (Reference r : ins.getReferencesFrom()) {
                Address t = r.getToAddress();
                Data d = currentProgram.getListing().getDataAt(t);
                if (d != null && d.getValue() != null) {
                    String dt = d.getDataType().getName().toLowerCase();
                    if (dt.contains("string") || dt.contains("unicode")) {
                        strs.add(t + " \"" + d.getValue().toString().replace("\n", "\\n").replace("\r", "").replace("\"", "'") + "\"");
                    }
                }
                if (seen.add("S:" + t)) {
                    // also record string symbols hit through composite data
                    Data dc = currentProgram.getListing().getDataContaining(t);
                    if (dc != null) {
                        Object v = dc.getValue();
                        if (v != null && dc.getDataType().getName().toLowerCase().contains("string")) {
                            strs.add(dc.getAddress() + " \"" + v.toString().replace("\n", "\\n").replace("\r", "").replace("\"", "'") + "\"");
                        }
                    }
                }
            }
        }
        for (String s : strs) {
            w.println(s);
        }

        // data references out of the body (vtables / globals)
        w.println();
        w.println("[DATA_XREFS_FROM_BODY]");
        iit = currentProgram.getListing().getInstructions(func.getBody(), true);
        Set<String> dx = new LinkedHashSet<>();
        while (iit.hasNext()) {
            Instruction ins = iit.next();
            for (Reference r : ins.getReferencesFrom()) {
                if (r.getReferenceType().isData() || r.getReferenceType().isRead()
                        || r.getReferenceType().isWrite()) {
                    Address t = r.getToAddress();
                    MemoryBlock b = currentProgram.getMemory().getBlock(t);
                    dx.add(ins.getAddress() + " -> " + t + " block=" + (b != null ? b.getName() : "?")
                            + " sym=" + symbolAt(t));
                }
            }
        }
        for (String s : dx) {
            w.println(s);
        }

        // decompile
        w.println();
        w.println("[DECOMPILE]");
        try {
            DecompileResults dr = dec.decompileFunction(func, 600, monitor);
            if (dr != null && dr.decompileCompleted()) {
                w.println(dr.getDecompiledFunction().getC());
            } else {
                w.println("DECOMPILE_FAILED=" + (dr != null ? dr.getErrorMessage() : "null"));
            }
        } catch (Exception e) {
            w.println("DECOMPILE_EXCEPTION=" + e);
        }
        w.flush();
        w.close();
        println("wrote addr_" + hex + ".txt (" + func.getName() + ")");
    }

    private void dumpStringKeywords(File outDir) throws Exception {
        PrintWriter w = open(new File(outDir, "_strings_keywords.txt"));
        Pattern p = Pattern.compile(String.join("|", KEYWORDS), Pattern.CASE_INSENSITIVE);
        DataIterator dit = currentProgram.getListing().getDefinedData(true);
        int hits = 0;
        while (dit.hasNext() && !monitor.isCancelled()) {
            Data d = dit.next();
            Object v = d.getValue();
            if (v == null) {
                continue;
            }
            String dt = d.getDataType().getName().toLowerCase();
            if (!dt.contains("string") && !dt.contains("unicode")) {
                continue;
            }
            String s = v.toString();
            Matcher m = p.matcher(s);
            if (m.find()) {
                w.println(d.getAddress() + "\t" + d.getDataType().getName() + "\t"
                        + s.replace("\n", "\\n").replace("\r", "\\r"));
                hits++;
            }
        }
        w.println("#hits=" + hits);
        w.close();
        println("string keyword hits=" + hits);
    }

    private String symbolAt(Address a) {
        if (a == null) {
            return "";
        }
        Symbol s = currentProgram.getSymbolTable().getPrimarySymbol(a);
        if (s == null) {
            try {
                Symbol[] syms = currentProgram.getSymbolTable().getSymbols(a);
                if (syms.length > 0) {
                    s = syms[0];
                }
            } catch (Exception ignored) {
                // no symbol
            }
        }
        return s != null ? s.getName(true) : "";
    }

    private String bytesAt(Address a, int n) {
        StringBuilder sb = new StringBuilder();
        try {
            byte[] buf = new byte[n];
            currentProgram.getMemory().getBytes(a, buf);
            for (byte b : buf) {
                sb.append(String.format("%02x", b));
            }
        } catch (Exception e) {
            sb.append("unreadable:").append(e.getMessage());
        }
        return sb.toString();
    }

    private PrintWriter open(File f) throws Exception {
        return new PrintWriter(new OutputStreamWriter(new FileOutputStream(f), StandardCharsets.UTF_8));
    }
}

