// DumpBearerBarSymbols.java
// Ghidra 12.2 headless probe for F-003 (Bearer Bar) on the v240 program.
// Dumps program identity, all symbols matching BearerBar/Bearer Bar, all defined
// strings matching the same keywords, and the resolved status of a candidate
// address list (so we can prove which cited addresses exist at function entry).
//
// Usage:
//   -process DocumentMarks.dll -noanalysis -scriptPath <dir> \
//     -postScript DumpBearerBarSymbols.java <outFile> [<addr> ...]

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.Locale;

public class DumpBearerBarSymbols extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        File out = new File(args.length > 0 ? args[0]
                : "H:/Desktop/ArtPlus/rag/evidence/F-003/ghidra/raw_v240/_probe.txt");
        out.getParentFile().mkdirs();

        try (PrintWriter w = new PrintWriter(new OutputStreamWriter(
                new FileOutputStream(out), StandardCharsets.UTF_8))) {

            w.println("# program identity");
            w.println("name=" + currentProgram.getName());
            w.println("executablePath=" + currentProgram.getExecutablePath());
            w.println("executableSHA256=" + currentProgram.getExecutableSHA256());
            w.println("executableMD5=" + currentProgram.getExecutableMD5());
            w.println("imageBase=" + currentProgram.getImageBase());
            w.println("language=" + currentProgram.getLanguageID());
            w.println("functionCount=" + currentProgram.getFunctionManager().getFunctionCount());
            w.println("symbolCount=" + currentProgram.getSymbolTable().getNumSymbols());

            w.println();
            w.println("# symbols matching bearerbar (case-insensitive)");
            SymbolIterator it = currentProgram.getSymbolTable().getAllSymbols(true);
            int hits = 0;
            while (it.hasNext() && !monitor.isCancelled()) {
                Symbol s = it.next();
                String n = s.getName(true);
                if (n.toLowerCase(Locale.ROOT).contains("bearerbar")) {
                    Address a = s.getAddress();
                    Function f = currentProgram.getFunctionManager().getFunctionContaining(a);
                    w.println(a + "\t" + s.getSymbolType() + "\t" + n
                            + "\tentry=" + (f != null ? f.getEntryPoint().toString() : "-")
                            + "\tns=" + s.getParentNamespace().getName(true));
                    hits++;
                }
            }
            w.println("#symbol_hits=" + hits);

            w.println();
            w.println("# defined strings matching bearer (case-insensitive)");
            DataIterator dit = currentProgram.getListing().getDefinedData(true);
            int shits = 0;
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
                String sv = v.toString();
                String low = sv.toLowerCase(Locale.ROOT);
                if (low.contains("bearer")) {
                    w.println(d.getAddress() + "\t" + d.getDataType().getName() + "\t"
                            + sv.replace("\n", "\\n").replace("\r", "\\r"));
                    shits++;
                }
            }
            w.println("#string_hits=" + shits);

            w.println();
            w.println("# candidate addresses");
            for (int i = 1; i < args.length; i++) {
                String raw = args[i].trim();
                if (raw.isEmpty()) {
                    continue;
                }
                Address a = currentProgram.getAddressFactory().getAddress(raw);
                if (a == null) {
                    w.println(raw + "\tINVALID");
                    continue;
                }
                Function at = currentProgram.getFunctionManager().getFunctionAt(a);
                Function cont = currentProgram.getFunctionManager().getFunctionContaining(a);
                w.println(raw
                        + "\tinMemory=" + currentProgram.getMemory().contains(a)
                        + "\tisFunctionEntry=" + (at != null)
                        + "\tentryName=" + (at != null ? at.getName(true) : "-")
                        + "\tcontaining=" + (cont != null ? cont.getEntryPoint() + " " + cont.getName(true) : "-")
                        + "\tcodeUnit=" + (currentProgram.getListing().getCodeUnitAt(a) != null));
            }
        }
        println("DumpBearerBarSymbols wrote " + out.getAbsolutePath());
    }
}
