// DumpF005Refs.java
// Ghidra 12.2 headless evidence extraction for F-005 (Open Document), v240 Document.dll.
// Usage:
//   -process Document.dll -noanalysis -readOnly -scriptPath <dir>
//     -postScript DumpF005Refs.java <outFile> str:0xADDR ... fn:0xADDR ...
// For str: prints all references to the data address with containing functions.
// For fn: prints signature, entry, thunks, incoming refs, outgoing calls, and C decompilation.

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.Locale;
import java.util.Set;
import java.util.TreeSet;

public class DumpF005Refs extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        File out = new File(args.length > 0 ? args[0]
                : "H:/Desktop/ArtPlus/tools/ghidra_analysis/f005_refs.txt");
        out.getParentFile().mkdirs();

        DecompInterface dec = new DecompInterface();
        dec.openProgram(currentProgram);

        try (PrintWriter w = new PrintWriter(new OutputStreamWriter(
                new FileOutputStream(out), StandardCharsets.UTF_8))) {

            w.println("# program=" + currentProgram.getName()
                    + " sha256=" + currentProgram.getExecutableSHA256());

            for (int i = 1; i < args.length; i++) {
                String raw = args[i].trim();
                if (raw.isEmpty()) {
                    continue;
                }
                if (raw.toLowerCase(Locale.ROOT).startsWith("str:")) {
                    dumpStringRefs(w, raw.substring(4));
                } else if (raw.toLowerCase(Locale.ROOT).startsWith("fn:")) {
                    dumpFunction(w, dec, raw.substring(3));
                }
            }
        } finally {
            dec.dispose();
        }
        println("DumpF005Refs wrote " + out.getAbsolutePath());
    }

    private Address addr(String s) {
        try {
            return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(s.trim());
        } catch (Exception e) {
            return null;
        }
    }

    private void dumpStringRefs(PrintWriter w, String raw) {
        w.println();
        Address a = addr(raw);
        w.println("## DATA " + a + " value=" + safeValue(a));
        ReferenceIterator it = currentProgram.getReferenceManager().getReferencesTo(a);
        int n = 0;
        while (it.hasNext() && !monitor.isCancelled()) {
            Reference r = it.next();
            Address from = r.getFromAddress();
            Function f = currentProgram.getFunctionManager().getFunctionContaining(from);
            w.println("   refFrom=" + from + " type=" + r.getReferenceType()
                    + " fn=" + (f != null ? f.getEntryPoint() + " " + f.getName(true) : "-")
                    + " offset=" + (f != null ? from.subtract(f.getEntryPoint()) : "-"));
            n++;
        }
        w.println("   refCount=" + n);
    }

    private String safeValue(Address a) {
        try {
            ghidra.program.model.listing.Data d = currentProgram.getListing().getDataAt(a);
            if (d != null && d.getValue() != null) {
                return d.getValue().toString().replace("\n", "\\n");
            }
        } catch (Exception e) {
            return "?";
        }
        return "?";
    }

    private void dumpFunction(PrintWriter w, DecompInterface dec, String raw) {
        Address a = addr(raw);
        Function f = currentProgram.getFunctionManager().getFunctionAt(a);
        w.println();
        w.println("## FN " + a);
        if (f == null) {
            Function cont = currentProgram.getFunctionManager().getFunctionContaining(a);
            w.println("   NOT_A_FUNCTION_ENTRY containing="
                    + (cont != null ? cont.getEntryPoint() + " " + cont.getName(true) : "-"));
            return;
        }
        w.println("   name=" + f.getName(true));
        w.println("   signature=" + f.getSignature());
        w.println("   entry=" + f.getEntryPoint() + " thunk=" + f.isThunk()
                + " external=" + f.isExternal() + " body=" + f.getBody().getNumAddresses());
        if (f.isThunk() && f.getThunkedFunction(true) != null) {
            w.println("   thunkedTo=" + f.getThunkedFunction(true).getEntryPoint() + " "
                    + f.getThunkedFunction(true).getName(true));
        }

        w.println("   -- callers --");
        Set<String> callers = new TreeSet<>();
        ReferenceIterator rit = currentProgram.getReferenceManager().getReferencesTo(f.getEntryPoint());
        while (rit.hasNext() && !monitor.isCancelled()) {
            Reference r = rit.next();
            Function cf = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
            callers.add(r.getFromAddress() + " " + r.getReferenceType() + " "
                    + (cf != null ? cf.getEntryPoint() + " " + cf.getName(true) : "-"));
        }
        for (String s : callers) {
            w.println("      " + s);
        }
        w.println("   -- callees --");
        Set<String> callees = new TreeSet<>();
        for (Function c : f.getCalledFunctions(monitor)) {
            callees.add(c.getEntryPoint() + " " + c.getName(true));
        }
        for (String s : callees) {
            w.println("      " + s);
        }

        w.println("   -- strings referenced --");
        Set<String> strs = new TreeSet<>();
        ghidra.program.model.listing.InstructionIterator iit =
                currentProgram.getListing().getInstructions(f.getBody(), true);
        while (iit.hasNext() && !monitor.isCancelled()) {
            ghidra.program.model.listing.Instruction ins = iit.next();
            for (Reference r : currentProgram.getReferenceManager().getReferencesFrom(ins.getAddress())) {
                Address to = r.getToAddress();
                try {
                    ghidra.program.model.listing.Data d = currentProgram.getListing().getDataAt(to);
                    if (d != null && d.getValue() != null) {
                        String dt = d.getDataType().getName().toLowerCase(Locale.ROOT);
                        if (dt.contains("string") || dt.contains("unicode")) {
                            strs.add(ins.getAddress() + " -> " + to + " \""
                                    + d.getValue().toString().replace("\n", "\\n") + "\"");
                        }
                    }
                } catch (Exception e) {
                    // ignore
                }
            }
        }
        for (String s : strs) {
            w.println("      " + s);
        }

        w.println("   -- decompiled --");
        try {
            DecompileResults res = dec.decompileFunction(f, 90, monitor);
            if (res != null && res.decompileCompleted() && res.getDecompiledFunction() != null) {
                w.println(res.getDecompiledFunction().getC());
            } else {
                w.println("   DECOMPILE_FAILED " + (res != null ? res.getErrorMessage() : "null"));
            }
        } catch (Exception e) {
            w.println("   DECOMPILE_EXCEPTION " + e);
        }
    }
}
