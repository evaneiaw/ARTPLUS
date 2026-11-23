// DumpF005Vtable.java
// Dumps virtual function tables (pointer-slot -> function) for F-005 evidence.
// Usage: -postScript DumpF005Vtable.java <outFile> vt:0xADDR[:count]

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.symbol.Symbol;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.Locale;

public class DumpF005Vtable extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        File out = new File(args.length > 0 ? args[0]
                : "H:/Desktop/ArtPlus/tools/ghidra_analysis/f005_vtables.txt");
        out.getParentFile().mkdirs();

        try (PrintWriter w = new PrintWriter(new OutputStreamWriter(
                new FileOutputStream(out), StandardCharsets.UTF_8))) {
            w.println("# program=" + currentProgram.getName()
                    + " sha256=" + currentProgram.getExecutableSHA256());
            for (int i = 1; i < args.length; i++) {
                String raw = args[i].trim();
                if (!raw.toLowerCase(Locale.ROOT).startsWith("vt:")) {
                    continue;
                }
                String spec = raw.substring(3);
                int count = 32;
                String addrPart = spec;
                int c = spec.indexOf(':');
                if (c > 0) {
                    addrPart = spec.substring(0, c);
                    try {
                        count = Integer.parseInt(spec.substring(c + 1).trim());
                    } catch (Exception e) {
                        count = 32;
                    }
                }
                Address base;
                try {
                    base = currentProgram.getAddressFactory().getDefaultAddressSpace()
                            .getAddress(addrPart.trim());
                } catch (Exception e) {
                    w.println("## VT invalid " + addrPart);
                    continue;
                }
                w.println();
                w.println("## VT " + base + " count=" + count);
                Memory mem = currentProgram.getMemory();
                for (int k = 0; k < count; k++) {
                    Address slot = base.add((long) k * 8L);
                    long val;
                    try {
                        val = mem.getLong(slot);
                    } catch (Exception e) {
                        break;
                    }
                    Address target = currentProgram.getAddressFactory()
                            .getDefaultAddressSpace().getAddress(Long.toHexString(val));
                    Function f = currentProgram.getFunctionManager().getFunctionAt(target);
                    Function cont = currentProgram.getFunctionManager().getFunctionContaining(target);
                    Symbol s = currentProgram.getSymbolTable().getPrimarySymbol(target);
                    w.println("   [" + k + "] slot=" + slot + " -> 0x" + Long.toHexString(val)
                            + " fn=" + (f != null ? f.getEntryPoint() + " " + f.getName(true) : "-")
                            + " containing=" + (cont != null ? cont.getEntryPoint() + " " + cont.getName(true) : "-")
                            + " sym=" + (s != null ? s.getName(true) : "-"));
                }
            }
        }
        println("DumpF005Vtable wrote " + out.getAbsolutePath());
    }
}
