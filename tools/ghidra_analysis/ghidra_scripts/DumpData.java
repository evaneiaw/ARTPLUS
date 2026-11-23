// DumpData.java - dump raw bytes / scalar values at given addresses of the current program.
// Usage: -process <prog> -noanalysis -scriptPath <dir> -postScript DumpData.java 0x180305518 [more]
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.mem.Memory;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;

public class DumpData extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length == 0) {
            println("ERROR: no addresses given");
            return;
        }
        String progName = currentProgram.getName();
        File outDir = new File("H:/Desktop/ArtPlus/rag/ghidra/exports/" + progName);
        outDir.mkdirs();
        File out = new File(outDir, "data_dump.txt");
        Memory mem = currentProgram.getMemory();
        try (PrintWriter pw = new PrintWriter(new FileWriter(out, true))) {
            pw.println("# DumpData run: " + progName);
            for (String a : args) {
                String hex = a.startsWith("0x") || a.startsWith("0X") ? a.substring(2) : a;
                Address addr = currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(hex);
                byte[] buf = new byte[16];
                int n;
                try {
                    n = mem.getBytes(addr, buf, 0, 16);
                } catch (Exception e) {
                    n = 0;
                }
                StringBuilder hx = new StringBuilder();
                StringBuilder asc = new StringBuilder();
                for (int i = 0; i < n; i++) {
                    hx.append(String.format("%02x ", buf[i]));
                    char c = (char) (buf[i] & 0xff);
                    asc.append(c >= 32 && c < 127 ? c : '.');
                }
                pw.println(String.format("%s  hex: %s | ascii: %s", addr, hx.toString().trim(), asc.toString()));
                if (n >= 8) {
                    long bits = 0;
                    for (int i = 7; i >= 0; i--) bits = (bits << 8) | (buf[i] & 0xffL);
                    pw.println(String.format("          int64=%d  double=%.17g", bits, Double.longBitsToDouble(bits)));
                }
                if (n >= 4) {
                    int i32 = (buf[0] & 0xff) | ((buf[1] & 0xff) << 8) | ((buf[2] & 0xff) << 16) | ((buf[3] & 0xff) << 24);
                    pw.println(String.format("          int32=%d", i32));
                }
            }
        }
        println("WROTE " + out.getAbsolutePath());
    }
}
