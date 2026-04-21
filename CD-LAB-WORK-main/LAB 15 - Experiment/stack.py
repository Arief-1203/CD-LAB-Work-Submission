stack = []

# Read operations from file
with open("input.txt", "r") as f:
    operations = [line.strip() for line in f if line.strip()]

print("Stack Storage Allocation\n")

for op in operations:

    parts = op.split()

    if parts[0] == "push":
        var = parts[1]
        stack.append(var)
        print(f"PUSH {var} -> Stack:", stack)

    elif parts[0] == "pop":
        if stack:
            removed = stack.pop()
            print(f"POP {removed} -> Stack:", stack)
        else:
            print("Stack Underflow")
