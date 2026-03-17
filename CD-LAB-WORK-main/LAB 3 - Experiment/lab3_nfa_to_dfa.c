#include <stdio.h>
#include <string.h>

int nfa[10][10][10];     // NFA[state][symbol][state]
int dfa[10][10];         // DFA transitions
int dfa_states[10][10];  // DFA state sets
int nfa_states, symbols;
int dfa_count = 0;

/* Check if DFA state already exists */
int isSameState(int a[], int b[]) {
    for (int i = 0; i < nfa_states; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

/* Check if DFA state is new */
int getStateIndex(int state[]) {
    for (int i = 0; i < dfa_count; i++) {
        if (isSameState(dfa_states[i], state))
            return i;
    }
    return -1;
}

int main() {
    printf("Enter number of NFA states: ");
    scanf("%d", &nfa_states);

    printf("Enter number of input symbols: ");
    scanf("%d", &symbols);

    printf("\nEnter NFA transitions (1 if exists, else 0)\n");

    for (int i = 0; i < nfa_states; i++) {
        for (int k = 0; k < symbols; k++) {
            printf("From q%d on symbol %d:\n", i, k);
            for (int j = 0; j < nfa_states; j++) {
                printf("  To q%d: ", j);
                scanf("%d", &nfa[i][k][j]);
            }
        }
    }

    // Initial DFA state = {q0}
    memset(dfa_states, 0, sizeof(dfa_states));
    dfa_states[0][0] = 1;
    dfa_count = 1;

    // Subset construction
    for (int i = 0; i < dfa_count; i++) {
        for (int k = 0; k < symbols; k++) {
            int new_state[10] = {0};

            for (int j = 0; j < nfa_states; j++) {
                if (dfa_states[i][j]) {
                    for (int x = 0; x < nfa_states; x++) {
                        if (nfa[j][k][x])
                            new_state[x] = 1;
                    }
                }
            }

            int index = getStateIndex(new_state);
            if (index == -1) {
                index = dfa_count;
                for (int x = 0; x < nfa_states; x++)
                    dfa_states[dfa_count][x] = new_state[x];
                dfa_count++;
            }
            dfa[i][k] = index;
        }
    }

    // Print DFA
    printf("\nDFA TRANSITION TABLE\n");
    printf("-------------------\n");
    printf("State\t");

    for (int k = 0; k < symbols; k++)
        printf("%d\t", k);
    printf("\n");

    for (int i = 0; i < dfa_count; i++) {
        printf("q%d\t", i);
        for (int k = 0; k < symbols; k++)
            printf("q%d\t", dfa[i][k]);
        printf("\t{ ");

        for (int j = 0; j < nfa_states; j++)
            if (dfa_states[i][j])
                printf("q%d ", j);
        printf("}\n");
    }

    return 0;
}
// 3 2 
// 010 001 010 001 001 001
