stack = []

def is_operator(c):
    return c in ['^', '*', '/', '+', '-']

def precedence(op):
    if op == '^':
        return 3
    elif op in ['*', '/']:
        return 2
    elif op in ['+', '-']:
        return 1
    else:
        return 0

def infix_to_postfix(expression):
    postfix = ""
    stack.append('(')
    expression = expression + ')'
    
    i = 0
    while i < len(expression):
        item = expression[i]

        if item == '(':
            stack.append(item)

        elif item.isalnum():
            postfix += item

        elif is_operator(item):
            x = stack.pop()
            while is_operator(x) and precedence(x) >= precedence(item):
                postfix += x
                x = stack.pop()
            stack.append(x)
            stack.append(item)

        elif item == ')':
            x = stack.pop()
            while x != '(':
                postfix += x
                x = stack.pop()

        else:
            print("Invalid Expression")
            return ""

        i += 1

    return postfix


# Read input from file
with open("input.txt", "r") as f:
    infix = f.read().strip()

print("Infix Expression:", infix)

postfix = infix_to_postfix(infix)

print("Postfix Expression:", postfix)
