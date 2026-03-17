# CD-LAB-WORK-Submission

## Steps to Run the Assignment

Step 1: Open Codespace
1. Open this GitHub repository.
2. Click the green **Code** button.
3. Go to the **Codespaces** tab.
4. Click **Create codespace on main**.
5. Wait until the online VS Code environment loads.

---

Step 2: Open Terminal
Inside Codespaces:
1. Click **Terminal → New Terminal**
2. You will see something like:
   ```bash
   username ➜ /workspaces/repo-name $

Step 3: Install Flex and Bison
Run the following command:
```
sudo apt update
sudo apt install flex bison -y
```
Check installation:
```
flex --version
bison --version
```
Step 4: Compile the Compiler
Run:
```
yacc -d simple.y
flex simple.l
gcc y.tab.c lex.yy.c -o compiler -lfl
```
Step 5: Run the Compiler
```
./compiler
```
You will see:
Enter program (Ctrl+D to finish):
Example Input
Paste the following:
```
int a;
int b;
int c;
c = a + b * 3;
```
Then press:
```
Ctrl + D
```
Expected Output
========== 1. LEXICAL ANALYSIS ==========
(tokens...)

========== 2. SYNTAX ANALYSIS ==========
Syntax is valid

========== 3. SEMANTIC ANALYSIS ==========
Semantic checks passed

========== 4. INTERMEDIATE CODE ==========
t0 = b * 3
t1 = a + t0
c = t1

========== 5. OPTIMIZATION ==========
Constant folding applied

========== 6. TARGET CODE ==========
MOV R1, result

