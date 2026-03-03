CD-LAB-WORK-Submission
Steps to Run the Assignment

✅ Step 1: Open Codespace

Open this GitHub repository.

Click the green Code button.

Go to the Codespaces tab.

Click Create codespace on main.

Wait until the online VS Code environment opens.

✅ Step 2: Open Terminal

Inside Codespace:

Click Terminal → New Terminal

You will see something like:

username ➜ /workspaces/repo-name $

✅ Step 3: Install Flex and Bison

Run:

sudo apt update sudo apt install flex bison -y

Check installation:

flex --version bison --version

✅ Step 4: Compile the Compiler

Now run:

yacc -d simple.y flex simple.l gcc y.tab.c lex.yy.c -o compiler -lfl

✅ Step 5: Run the Compiler ./compiler

You will see:

Enter program (Ctrl+D to finish):

🧪 Example Correct Input

Paste this:

int a; int b; int c; c = a + b * 3;

Then press:

Ctrl + D

✅ Expected Output

You will see all six phases:

========== 1. LEXICAL ANALYSIS ========== (tokens...)

========== 2. SYNTAX ANALYSIS ========== Syntax is valid

========== 3. SEMANTIC ANALYSIS ========== Semantic checks passed

========== 4. INTERMEDIATE CODE ========== t0 = b * 3 t1 = a + t0 c = t1

========== 5. OPTIMIZATION ========== Constant folding applied

========== 6. TARGET CODE ========== MOV R1, result
