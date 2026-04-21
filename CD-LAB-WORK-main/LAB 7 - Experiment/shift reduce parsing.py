stack = []

def check():
    global stack

    # Reduce id → E
    for j in range(len(stack)-1):
        if stack[j] == 'i' and stack[j+1] == 'd':
            print("Reduce: E -> id")
            stack[j:j+2] = ['E']
            return True

    # Reduce E+E → E
    for j in range(len(stack)-2):
        if stack[j] == 'E' and stack[j+1] == '+' and stack[j+2] == 'E':
            print("Reduce: E -> E+E")
            stack[j:j+3] = ['E']
            return True

    # Reduce E*E → E
    for j in range(len(stack)-2):
        if stack[j] == 'E' and stack[j+1] == '*' and stack[j+2] == 'E':
            print("Reduce: E -> E*E")
            stack[j:j+3] = ['E']
            return True

    # Reduce (E) → E
    for j in range(len(stack)-2):
        if stack[j] == '(' and stack[j+1] == 'E' and stack[j+2] == ')':
            print("Reduce: E -> (E)")
            stack[j:j+3] = ['E']
            return True

    return False


# Read input from file
with open("input.txt", "r") as f:
    input_string = f.read().strip()

i = 0

print("\nSTACK\tINPUT\tACTION")

while i < len(input_string):
    stack.append(input_string[i])   # Shift
    print("".join(stack), "\t", input_string[i+1:], "\tShift")
    i += 1

    while check():
        print("".join(stack), "\t", input_string[i:], "\tReduce")

while check():
    print("".join(stack), "\t", "\tReduce")

if stack == ['E']:
    print("\nString Accepted ✅")
else:
    print("\nString Rejected ❌")
