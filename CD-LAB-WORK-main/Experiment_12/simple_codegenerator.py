icode = []

print("Enter the set of intermediate code (terminated by exit):")

while True:
    line = input()
    if line == "exit":
        break
    icode.append(line)

print("\nTarget Code Generation")
print("*******")

for i, code in enumerate(icode):

    op = code[1]

    if op == '+':
        opr = "ADD"
    elif op == '-':
        opr = "SUB"
    elif op == '*':
        opr = "MUL"
    elif op == '/':
        opr = "DIV"
    else:
        continue

    arg1 = code[0]
    arg2 = code[2]

    print(f"\tMOV {arg1}, R{i}")
    print(f"\t{opr} {arg2}, R{i}")
    print(f"\tMOV R{i}, RESULT")
