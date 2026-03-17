#include <stdio.h>
#include <string.h>

char stack[50];
int top = -1;

/* Stack operations */
void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

/* Check terminal */
int isTerminal(char c) {
    return (c=='i' || c=='+' || c=='*' || c=='$');
}

/* Print stack */
void printStack() {
    for (int i = top; i >= 0; i--)
        printf("%c", stack[i]);
}

int main() {
    char input[50];
    int ip = 0;

    printf("Enter input string (end with $): ");
    scanf("%s", input);

    /* Initialize stack */
    push('$');
    push('E');

    printf("\nSTACK\t\tINPUT\t\tACTION\n");
    printf("-------------------------------------------\n");

    while (top >= 0) {
        char X = stack[top];
        char a = input[ip];

        printStack();
        printf("\t\t%s\t\t", &input[ip]);

        /* Match */
        if (X == a) {
            pop();
            ip++;
            printf("Match %c\n", a);
        }
        /* Terminal mismatch */
        else if (isTerminal(X)) {
            printf("Error\n");
            return 0;
        }
        /* Non-terminal */
        else {
            pop();

            /* Predictive Parsing Table logic */
            if (X == 'E' && a == 'i') {
                push('R');
                push('T');
                printf("E -> TR\n");
            }
            else if (X == 'R' && a == '+') {
                push('R');
                push('T');
                push('+');
                printf("R -> +TR\n");
            }
            else if (X == 'R' && a == '$') {
                printf("R -> ε\n");
            }
            else if (X == 'T' && a == 'i') {
                push('Y');
                push('F');
                printf("T -> FY\n");
            }
            else if (X == 'Y' && a == '*') {
                push('Y');
                push('F');
                push('*');
                printf("Y -> *FY\n");
            }
            else if (X == 'Y' && (a == '+' || a == '$')) {
                printf("Y -> ε\n");
            }
            else if (X == 'F' && a == 'i') {
                push('i');
                printf("F -> i\n");
            }
            else {
                printf("Error\n");
                return 0;
            }
        }
    }

    if (input[ip] == '\0')
        printf("\n✅ STRING ACCEPTED\n");
    else
        printf("\n❌ STRING REJECTED\n");

    return 0;
}
