import json
import sys
from ghidra.program.model.listing import Function
from ghidra.program.model.address import Address

def main():
    program = currentProgram
    listing = program.getListing()
    
    functions = []
    func_iter = listing.getFunctions(True)
    
    while func_iter.hasNext():
        func = func_iter.next()
        functions.append({
            'name': func.getName(),
            'entry': str(func.getEntryPoint())
        })
    
    with open(sys.argv[1], 'w') as f:
        json.dump(functions, f, indent=2)
    
    print(f"Exported {{len(functions)}} functions to {{sys.argv[1]}}")

if __name__ == "__main__":
    main()
