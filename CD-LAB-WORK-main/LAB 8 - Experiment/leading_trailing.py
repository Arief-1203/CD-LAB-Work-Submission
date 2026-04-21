def is_non_terminal(c):
    return c.isupper()

n = int(input("Enter number of productions: "))

productions = []

for i in range(n):
    p = input("Enter production: ")
    productions.append(p)

flag = True

for prod in productions:
    rhs = prod.split("->")[1]

    # Check for epsilon
    if rhs == "ε":
        flag = False

    # Check for adjacent non-terminals
    for i in range(len(rhs)-1):
        if is_non_terminal(rhs[i]) and is_non_terminal(rhs[i+1]):
            flag = False

if flag:
    print("The grammar is an Operator Grammar")
else:
    print("The grammar is NOT an Operator Grammar")
