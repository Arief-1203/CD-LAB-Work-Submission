stack = []

def is_operator(c):
    return c in ['+', '-', '*', '/', '^']

def postfix_to_prefix(postfix):
    for ch in postfix:
        
        if ch.isalnum():      # operand
            stack.append(ch)

        elif is_operator(ch):   # operator
            op1 = stack.pop()
            op2 = stack.pop()

            temp = ch + op2 + op1
            stack.append(temp)

    return stack[-1]


# Read postfix expression from file
with open("input.txt", "r") as f:
    postfix = f.read().strip()

print("Postfix Expression:", postfix)

prefix = postfix_to_prefix(postfix)

print("Prefix Expression:", prefix)
