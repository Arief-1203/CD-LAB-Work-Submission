#include <stdio.h>
#include <stdlib.h>

int state = 1;   // start from q1, q0 reserved

struct NFA {
    int start;
    int end;
};

struct NFA stack[100];
int top = -1;

/* Stack operations */
void push(struct NFA n) {
    stack[++top] = n;
}

struct NFA pop() {
    if (top < 0) {
        printf("❌ Invalid postfix expression\n");
        exit(1);
    }
    return stack[top--];
}

/* Print transitions */
void add_transition(int from, char symbol, int to) {
    if (symbol == 'e')
        printf("q%d -- ε --> q%d\n", from, to);
    else
        printf("q%d -- %c --> q%d\n", from, symbol, to);
}

/* Validate postfix */
int is_valid_postfix(char *p) {
    int count = 0;
    for (int i = 0; p[i]; i++) {
        if (p[i] >= 'a' && p[i] <= 'z')
            count++;
        else if (p[i] == '*')
            ;
        else if (p[i] == '.' || p[i] == '/')
            count--;
        else
            return 0;

        if (count <= 0)
            return 0;
    }
    return count == 1;
}

int main() {
    char postfix[50];

    printf("Enter Regular Expression (postfix): ");
    scanf("%s", postfix);

    if (!is_valid_postfix(postfix)) {
        printf("❌ Invalid postfix expression\n");
        return 0;
    }

    printf("\nNFA Transitions:\n");

    /* Build NFA using Thompson's construction */
    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];

        if (ch >= 'a' && ch <= 'z') {
            struct NFA n;
            n.start = state++;
            n.end = state++;
            add_transition(n.start, ch, n.end);
            push(n);
        }

        else if (ch == '*') {
            struct NFA n1 = pop();
            struct NFA n;

            n.start = state++;
            n.end = state++;

            add_transition(n.start, 'e', n1.start);
            add_transition(n.start, 'e', n.end);
            add_transition(n1.end, 'e', n1.start);
            add_transition(n1.end, 'e', n.end);

            push(n);
        }

        else if (ch == '.') {
            struct NFA n2 = pop();
            struct NFA n1 = pop();

            add_transition(n1.end, 'e', n2.start);

            struct NFA n;
            n.start = n1.start;
            n.end = n2.end;

            push(n);
        }

        else if (ch == '/') {
            struct NFA n2 = pop();
            struct NFA n1 = pop();
            struct NFA n;

            n.start = state++;
            n.end = state++;

            add_transition(n.start, 'e', n1.start);
            add_transition(n.start, 'e', n2.start);
            add_transition(n1.end, 'e', n.end);
            add_transition(n2.end, 'e', n.end);

            push(n);
        }
    }

    struct NFA result = pop();

    if (top != -1) {
        printf("❌ Invalid postfix expression\n");
        return 0;
    }

    /* 🔥 GLOBAL START STATE q0 */
    add_transition(0, 'e', result.start);

    printf("\nStart State: q0\n");
    printf("Final State: q%d\n", result.end);

    return 0;
}
