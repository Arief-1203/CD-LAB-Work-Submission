def read_input():
    with open("input.txt", "r") as f:
        lines = [line.strip() for line in f if line.strip()]
    
    n = int(lines[0])
    blocks = lines[1:n+1]
    edges = [tuple(line.split()) for line in lines[n+1:]]
    
    return blocks, edges


blocks, edges = read_input()

# Initialize GEN and KILL sets (example)
GEN = {b: {b+"_def"} for b in blocks}
KILL = {b: set() for b in blocks}

IN = {b: set() for b in blocks}
OUT = {b: set() for b in blocks}

# Find predecessors
pred = {b: [] for b in blocks}
for u,v in edges:
    pred[v].append(u)

changed = True

while changed:
    changed = False
    
    for b in blocks:
        new_in = set()
        for p in pred[b]:
            new_in |= OUT[p]
        
        new_out = GEN[b] | (new_in - KILL[b])
        
        if new_in != IN[b] or new_out != OUT[b]:
            IN[b] = new_in
            OUT[b] = new_out
            changed = True

print("Block\tIN\t\tOUT")

for b in blocks:
    print(b, "\t", IN[b], "\t", OUT[b])d
