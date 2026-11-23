// DumpBearerBarRefs.java
// Ghidra 12.2 headless probe for F-003: resolve v240 equivalents of v25 addresses.
// For each argument (0xADDR or str:<exact text>) prints:
//   - symbol(s) at the address, function at/containing it
//   - every reference TO the address, with the containing function and symbol
//   - if the address is a function entry: its callers and callees
//
// Usage: -postScript DumpBearerBarRefs.java <outFile> <0xADDR|str:TEXT> ...

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.Symbol;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.Locale;

public class DumpBearerBarRefs extends GhidraScript {

    private PrintWriter w;

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        File out = new File(args[0]);
        out.getParentFile().mkdirs();
        try (PrintWriter pw = new PrintWriter(new OutputStreamWriter(
                new FileOutputStream(out), StandardCharsets.UTF_8))) {
            w = pw;
            w.println("# DumpBearerBarRefs on " + currentProgram.getName());
            w.println("executableSHA256=" + currentProgram.getExecutableSHA256());
            for (int i = 1; i < args.length; i++) {
                String a = args[i].trim();
                if (a.isEmpty()) {
                    continue;
                }
                if (a.toLowerCase(Locale.ROOT).startsWith("str:")) {
                    String text = a.substring(4);
                    resolveString(text);
                } else {
                    Address addr = currentProgram.getAddressFactory().getAddress(a);
                    if (addr == null) {
                        w.println("\n=== INVALID " + a);
                        continue;
                    }
                    dump(addr, a);
                }
            }
        }
        println("DumpBearerBarRefs wrote " + out.getAbsolutePath());
    }

    private void resolveString(String text) {
        DataIterator dit = currentProgram.getListing().getDefinedData(true);
        int found = 0;
        while (dit.hasNext() && !monitor.isCancelled()) {
            Data d = dit.next();
            Object v = d.getValue();
            if (v == null) {
                continue;
            }
            String dt = d.getDataType().getName().toLowerCase(Locale.ROOT);
            if (!dt.contains("string") && !dt.contains("unicode")) {
                continue;
            }
            if (v.toString().equals(text)) {
                w.println("\n=== STRING \"" + text + "\"");
                dump(d.getAddress(), d.getAddress().toString());
                found++;
            }
        }
        if (found == 0) {
            w.println("\n=== STRING \"" + text + "\" NOT FOUND AS DEFINED STRING");
        }
    }

    private void dump(Address addr, String raw) {
        w.println("\n=== ADDR " + raw + " -> " + addr);
        w.println("inMemory=" + currentProgram.getMemory().contains(addr));
        Symbol[] syms = currentProgram.getSymbolTable().getSymbols(addr);
        for (Symbol s : syms) {
            w.println("  symbol: " + s.getSymbolType() + " " + s.getName(true));
        }
        Function at = currentProgram.getFunctionManager().getFunctionAt(addr);
        Function cont = currentProgram.getFunctionManager().getFunctionContaining(addr);
        w.println("  isFunctionEntry=" + (at != null)
                + " entryName=" + (at != null ? at.getName(true) : "-"));
        w.println("  containing=" + (cont != null
                ? cont.getEntryPoint() + " " + cont.getName(true)
                + " body=" + cont.getBody().getMinAddress() + ".." + cont.getBody().getMaxAddress()
                + " size=" + cont.getBody().getNumAddresses()
                : "-"));

        w.println("  [REFERENCES_TO]");
        ReferenceIterator rit = currentProgram.getReferenceManager().getReferencesTo(addr);
        int n = 0;
        while (rit.hasNext()) {
            Reference r = rit.next();
            Function fromF = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
            w.println("    <- " + r.getFromAddress() + " [" + r.getReferenceType() + "] in "
                    + (fromF != null ? fromF.getEntryPoint() + " " + fromF.getName(true) : "(data)"));
            n++;
        }
        if (n == 0) {
            w.println("    (none)");
        }

        if (at != null) {
            w.println("  [CALLERS]");
            int c = 0;
            for (Function f : at.getCallingFunctions(monitor)) {
                w.println("    * " + f.getEntryPoint() + " " + f.getName(true));
                c++;
            }
            if (c == 0) {
                w.println("    (none)");
            }
            w.println("  [CALLEES]");
            c = 0;
            for (Function f : at.getCalledFunctions(monitor)) {
                w.println("    -> " + f.getEntryPoint() + " " + f.getName(true));
                c++;
            }
            if (c == 0) {
                w.println("    (none)");
            }
        }
    }
}
