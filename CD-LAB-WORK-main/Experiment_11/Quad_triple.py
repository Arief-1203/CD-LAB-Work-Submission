temp_count = 1

quadruple = []
triple = []
indirect = []

def generate_tac(expr):
    global temp_count
    operators = ['*', '/', '+', '-']

    tac = []

    while True:
        pos = -1
        op = ''

        for o in operators:
            if o in expr:
                pos = expr.index(o)
                op = o
                break

        if pos == -1:
            break

        left = expr[pos-1]
        right = expr[pos+1]

        temp = "t" + str(temp_count)
        tac.append(f"{temp} = {left} {op} {right}")

        quadruple.append([op, left, right, temp])
        triple.append([op, left, right])
        indirect.append(len(triple)-1)

        expr = expr[:pos-1] + temp + expr[pos+2:]
        temp_count += 1

    return tac


expr = input("Enter the expression: ")

tac = generate_tac(expr)

print("\nThree Address Code:")
for line in tac:
    print(line)

print("\nQuadruple Representation:")
print("Op\tArg1\tArg2\tResult")
for q in quadruple:
    print(q[0], "\t", q[1], "\t", q[2], "\t", q[3])

print("\nTriple Representation:")
print("Index\tOp\tArg1\tArg2")
for i,t in enumerate(triple):
    print(i, "\t", t[0], "\t", t[1], "\t", t[2])

print("\nIndirect Triple Representation:")
print("Pointer -> Triple Index")
for i,v in enumerate(indirect):
    print(i,"->",v)
