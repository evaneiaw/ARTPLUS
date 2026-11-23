// F004Extract.java - extract decompiled code, xrefs, string references and pointer hits
// for the selection/resize/transform functions of PDFObjectActions.dll (F-004).
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import ghidra.program.model.mem.*;
import java.io.*;
import java.util.*;

public class F004Extract extends GhidraScript {

    private static final String[] TARGETS = {
        "GOVSelectHitElement::Select",
        "GOVSelectHitElement::SetRect",
        "GOVSelectHitElement::SetHitType",
        "GOVSelectOverlapping::Select",
        "GOVSelectOverlappingObjects::Select",
        "GOVSelectOverlappingObjects::Expand",
        "GOVChangeScaleSelection::Change",
        "GOVChangeRotateSelection::Change",
        "GOVChangeFlipSelection::Change",
        "GOVGetSelectedObjects::GetObjects",
        "GOVGetSelectedObjects::Inform",
        "GOVCloneSelection::ConfigChangeMatrix",
        "GOVSelectObjects::Select"
    };

    private PrintWriter index;
    private DecompInterface dec;

    @Override
    protected void run() throws Exception {
        String outDir = "H:/Desktop/ArtPlus/rag/evidence/F-004/ghidra/_raw";
        new File(outDir).mkdirs();
        index = new PrintWriter(new FileWriter(new File(outDir, "index.tsv")));
        index.println("address\tname\tparams\tbytes\tcallers\tcallees\tstrings");

        List<Function> selected = new ArrayList<>();
        FunctionIterator fit = currentProgram.getFunctionManager().getFunctions(true);
        while (fit.hasNext() && !monitor.isCancelled()) {
            Function f = fit.next();
            String n = f.getName(true);
            for (String t : TARGETS) {
                if (n.equals(t)) {
                    selected.add(f);
                    break;
                }
            }
        }

        // one pass over non-executable memory: which addresses hold a pointer to a target function
        Map<Long, List<String>> ptrHits = new HashMap<>();
        Set<Long> wanted = new HashSet<>();
        for (Function f : selected) wanted.add(f.getEntryPoint().getOffset());

        Memory mem = currentProgram.getMemory();
        for (MemoryBlock b : mem.getBlocks()) {
            if (!b.isInitialized() || b.isExecute()) continue;
            Address a = b.getStart();
            long end = b.getEnd().getOffset();
            while (a.getOffset() < end && !monitor.isCancelled()) {
                if (a.getOffset() % 8 == 0) {
                    try {
                        long v = mem.getLong(a);
                        if (wanted.contains(v)) {
                            ptrHits.computeIfAbsent(v, k -> new ArrayList<>()).add(b.getName() + ":" + a);
                        }
                    } catch (Exception e) {
                        // unreadable, skip
                    }
                }
                a = a.add(1);
            }
        }

        dec = new DecompInterface();
        dec.openProgram(currentProgram);

        for (Function f : selected) {
            dump(outDir, f, ptrHits.getOrDefault(f.getEntryPoint().getOffset(), new ArrayList<>()));
        }
        index.flush();
        index.close();
        dec.dispose();
        println("F004Extract: " + selected.size() + " functions");
    }

    private void dump(String outDir, Function f, List<String> ptrs) throws Exception {
        Address entry = f.getEntryPoint();
        Set<Function> callers = f.getCallingFunctions(monitor);
        Set<Function> callees = f.getCalledFunctions(monitor);

        LinkedHashMap<String, String> strings = new LinkedHashMap<>();
        InstructionIterator iit = currentProgram.getListing().getInstructions(f.getBody(), true);
        while (iit.hasNext()) {
            Instruction ins = iit.next();
            for (Reference r : ins.getReferencesFrom()) {
                Address to = r.getToAddress();
                Data d = getDataAt(to);
                if (d != null && d.getValue() != null) {
                    String dt = d.getDataType().getName();
                    if (dt.contains("string") || dt.contains("String") || dt.contains("unicode")) {
                        strings.put(to.toString(), d.getValue().toString().replace("\n", " ").replace("\r", " "));
                    }
                }
            }
        }

        String fname = "PDFObjectActions__" + entry.toString() + ".txt";
        PrintWriter pw = new PrintWriter(new FileWriter(new File(outDir, fname)));
        pw.println("address: " + entry);
        pw.println("name: " + f.getName(true));
        pw.println("signature: " + f.getPrototypeString(true, true));
        pw.println("body_bytes: " + f.getBody().getNumAddresses());
        pw.println("param_count: " + f.getParameterCount());
        pw.println();
        pw.println("[callers]");
        for (Function c : callers) pw.println("  " + c.getEntryPoint() + " " + c.getName(true));
        pw.println("[callees]");
        for (Function c : callees) pw.println("  " + c.getEntryPoint() + " " + c.getName(true));
        pw.println("[string_refs]");
        for (Map.Entry<String, String> e : strings.entrySet()) {
            pw.println("  " + e.getKey() + " " + e.getValue());
        }
        pw.println("[pointer_hits_non_exec]");
        for (String s : ptrs) pw.println("  " + s);
        pw.println();
        pw.println("[decompiled]");
        DecompileResults res = dec.decompileFunction(f, 120, monitor);
        if (res != null && res.decompileCompleted()) {
            pw.println(res.getDecompiledFunction().getC());
        } else {
            pw.println("(decompile failed)");
        }
        pw.flush();
        pw.close();

        index.println(entry + "\t" + f.getName(true) + "\t" + f.getParameterCount() + "\t"
                + f.getBody().getNumAddresses() + "\t" + callers.size() + "\t" + callees.size()
                + "\t" + strings.size());
    }
}
