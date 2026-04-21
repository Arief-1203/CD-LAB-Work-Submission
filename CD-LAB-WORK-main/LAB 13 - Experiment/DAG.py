class DAGNode:
    def __init__(self, label, data, left=None, right=None):
        self.label = label
        self.data = data
        self.left = left
        self.right = right


label_node = {}
statements = []

# Read statements from file
with open("input.txt", "r") as f:
    for line in f:
        line = line.strip()
        if line:
            statements.append(line)


# Build DAG
for st in statements:

    label = st[0]
    left = st[2]
    op = st[3]
    right = st[4]

    if left not in label_node:
        left_ptr = DAGNode('_', left)
    else:
        left_ptr = label_node[left]

    if right not in label_node:
        right_ptr = DAGNode('_', right)
    else:
        right_ptr = label_node[right]

    node = DAGNode(label, op, left_ptr, right_ptr)

    label_node[label] = node


# Display DAG
print("Label\tData\tLeft\tRight")

for st in statements:

    node = label_node[st[0]]

    if node.left.label == '_':
        left_val = node.left.data
    else:
        left_val = node.left.label

    if node.right.label == '_':
        right_val = node.right.data
    else:
        right_val = node.right.label

    print(node.label, "\t", node.data, "\t", left_val, "\t", right_val)
