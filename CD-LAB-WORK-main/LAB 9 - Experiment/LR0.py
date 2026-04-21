from collections import defaultdict

grammar = defaultdict(list)
productions = []

# Read grammar from file
with open("grammar.txt", "r") as f:
    for line in f:
        line = line.strip()
        if line == "0":
            break
        productions.append(line)

# Build grammar dictionary
for p in productions:
    lhs, rhs = p.split("->")
    grammar[lhs].append(rhs)

start_symbol = productions[0].split("->")[0]
augmented = start_symbol + "'"

grammar[augmented].append(start_symbol)

print("Augmented Grammar:")
for lhs in grammar:
    for rhs in grammar[lhs]:
        print(lhs + "->" + rhs)

# Closure function
def closure(items):
    closure_set = set(items)

    while True:
        new_items = set(closure_set)

        for item in closure_set:
            lhs, rhs = item.split("->")
            dot = rhs.find('.')

            if dot != -1 and dot + 1 < len(rhs):
                symbol = rhs[dot+1]

                if symbol in grammar:
                    for prod in grammar[symbol]:
                        new_items.add(symbol + "->." + prod)

        if new_items == closure_set:
            break

        closure_set = new_items

    return closure_set


# GOTO function
def goto(items, symbol):
    moved = set()

    for item in items:
        lhs, rhs = item.split("->")
        dot = rhs.find('.')

        if dot != -1 and dot + 1 < len(rhs) and rhs[dot+1] == symbol:
            new_rhs = rhs[:dot] + symbol + '.' + rhs[dot+2:]
            moved.add(lhs + "->" + new_rhs)

    return closure(moved)


# Build LR(0) item sets
C = []
start_item = closure({augmented + "->." + start_symbol})
C.append(start_item)

symbols = set()

for lhs in grammar:
    symbols.add(lhs)
    for rhs in grammar[lhs]:
        for c in rhs:
            symbols.add(c)

changed = True

while changed:
    changed = False
    for I in list(C):
        for X in symbols:
            g = goto(I, X)
            if g and g not in C:
                C.append(g)
                changed = True

# Print LR(0) Items
print("\nTHE SET OF LR(0) ITEMS:\n")

for i, itemset in enumerate(C):
    print("I", i)
    for item in itemset:
        print(item)
    print()
