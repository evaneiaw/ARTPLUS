// DumpF005Symbols.java
// Ghidra 12.2 headless probe for F-005 (Open Document) on the v240 Document.dll program.
// Dumps program identity, symbols/strings matching open/import/parse/page keywords,
// and resolves a candidate address list.

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

public class DumpF005Symbols extends GhidraScript {

    private static final String[] SYM_KEYWORDS = {
        "openfile", "opendoc", "open", "import", "parse", "readpdf", "loadpdf",
        "pdfdocument", "documentio", "catalog", "pagecount", "numpages", "getpages",
        "addpage", "createpage", "makePage", "insertpage", "importdocument",
        "detect", "sniff", "probeformat", "fileformat"
    };

    private static final String[] STR_KEYWORDS = {
        "document: file", "document: open", "invalid catalog", "has no pages",
        "unknown encryption", "error_file", "wrong_password", "%pdf-", "open read",
        "exception caught while opening", "document: destructor", "already open"
    };

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        File out = new File(args.length > 0 ? args[0]
                : "H:/Desktop/ArtPlus/tools/ghidra_analysis/f005_probe.txt");
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
            w.println("# symbols matching keywords (case-insensitive)");
            SymbolIterator it = currentProgram.getSymbolTable().getAllSymbols(true);
            int hits = 0;
            while (it.hasNext() && !monitor.isCancelled()) {
                Symbol s = it.next();
                String n = s.getName(true);
                String low = n.toLowerCase(Locale.ROOT);
                boolean match = false;
                for (String k : SYM_KEYWORDS) {
                    if (low.contains(k.toLowerCase(Locale.ROOT))) {
                        match = true;
                        break;
                    }
                }
                if (!match) {
                    continue;
                }
                Address a = s.getAddress();
                Function f = currentProgram.getFunctionManager().getFunctionContaining(a);
                w.println(a + "\t" + s.getSymbolType() + "\t" + n
                        + "\tfuncEntry=" + (f != null ? f.getEntryPoint().toString() : "-")
                        + "\tns=" + s.getParentNamespace().getName(true));
                hits++;
            }
            w.println("#symbol_hits=" + hits);

            w.println();
            w.println("# defined strings matching keywords (case-insensitive)");
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
                boolean match = false;
                for (String k : STR_KEYWORDS) {
                    if (low.contains(k)) {
                        match = true;
                        break;
                    }
                }
                if (!match) {
                    continue;
                }
                w.println(d.getAddress() + "\t" + d.getDataType().getName() + "\t"
                        + sv.replace("\n", "\\n").replace("\r", "\\r"));
                shits++;
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
        println("DumpF005Symbols wrote " + out.getAbsolutePath());
    }
}
