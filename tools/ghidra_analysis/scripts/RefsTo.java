// RefsTo.java - lists code/data references to given addresses (v240 triage helper).

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

public class RefsTo extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        File out = new File(args[0]);
        PrintWriter w = new PrintWriter(new OutputStreamWriter(new FileOutputStream(out), StandardCharsets.UTF_8));
        w.println("program=" + currentProgram.getName());
        w.println("sha256=" + currentProgram.getExecutableSHA256());
        for (int i = 1; i < args.length; i++) {
            Address a = currentProgram.getAddressFactory().getAddress(args[i]);
            w.println();
            w.println("[REFS_TO " + args[i] + "]");
            ReferenceIterator it = currentProgram.getReferenceManager().getReferencesTo(a);
            while (it.hasNext()) {
                Reference r = it.next();
                Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                w.println(r.getFromAddress() + "\t" + r.getReferenceType()
                        + "\tfromFunction=" + (f != null ? f.getEntryPoint() + " " + f.getName(true) : "none"));
            }
        }
        w.close();
        println("wrote " + out.getAbsolutePath());
    }
}
