// DecompileAddr.java - decompile specific addresses of the current program.
// Usage: -process <prog> -noanalysis -scriptPath <dir> -postScript DecompileAddr.java 0x1800FAE70 [more]
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;

public class DecompileAddr extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length == 0) {
            println("ERROR: no addresses given");
            return;
        }
        String progName = currentProgram.getName();
        File outDir = new File("H:/Desktop/ArtPlus/rag/ghidra/exports/" + progName + "/decompiled_addr");
        outDir.mkdirs();
        DecompInterface ifc = new DecompInterface();
        if (!ifc.openProgram(currentProgram)) {
            println("ERROR: could not open program in decompiler");
            return;
        }
        for (String a : args) {
            String hex = a.startsWith("0x") || a.startsWith("0X") ? a.substring(2) : a;
            Address addr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(hex);
            Function fn = getFunctionAt(addr);
            if (fn == null) {
                fn = getFunctionContaining(addr);
            }
            if (fn == null) {
                println("NO FUNCTION at " + a);
                continue;
            }
            DecompileResults res = ifc.decompileFunction(fn, 120, monitor);
            if (res == null || !res.decompileCompleted() || res.getDecompiledFunction() == null) {
                println("DECOMPILE FAILED " + a + " : " + (res != null ? res.getErrorMessage() : "null"));
                continue;
            }
            String c = res.getDecompiledFunction().getC();
            File out = new File(outDir, fn.getEntryPoint().toString().replace(":", "_") + "__" + fn.getName().replaceAll("[^A-Za-z0-9_.]", "_") + ".c");
            try (PrintWriter pw = new PrintWriter(new FileWriter(out))) {
                pw.println("// " + progName + " " + fn.getEntryPoint() + " " + fn.getName(true));
                pw.println("// signature: " + fn.getSignature().getPrototypeString());
                pw.println(c);
            }
            println("WROTE " + out.getAbsolutePath());
        }
        ifc.dispose();
    }
}
