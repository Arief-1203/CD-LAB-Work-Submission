#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n;
char prod[10][20];
char nonT[10];
char FIRST[10][20];
char FOLLOW[10][20];

/* add symbol to set */
void add(char set[], char c) {
    if (!strchr(set, c)) {
        int l = strlen(set);
        set[l] = c;
        set[l + 1] = '\0';
    }
}

/* find FIRST */
void findFIRST(char c, int idx) {
    if (!isupper(c)) {
        add(FIRST[idx], c);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            char rhs = prod[i][2];

            if (!isupper(rhs)) {
                add(FIRST[idx], rhs);
            } else {
                int k;
                for (k = 0; k < n; k++)
                    if (nonT[k] == rhs)
                        break;
                findFIRST(rhs, k);

                for (int x = 0; x < strlen(FIRST[k]); x++)
                    add(FIRST[idx], FIRST[k][x]);
            }
        }
    }
}

/* find FOLLOW */
void findFOLLOW(char c, int idx) {
    if (c == nonT[0])
        add(FOLLOW[idx], '$');

    for (int i = 0; i < n; i++) {
        for (int j = 2; j < strlen(prod[i]); j++) {
            if (prod[i][j] == c) {

                if (prod[i][j + 1] != '\0') {
                    char next = prod[i][j + 1];

                    if (!isupper(next)) {
                        add(FOLLOW[idx], next);
                    } else {
                        int k;
                        for (k = 0; k < n; k++)
                            if (nonT[k] == next)
                                break;

                        for (int x = 0; x < strlen(FIRST[k]); x++)
                            add(FOLLOW[idx], FIRST[k][x]);
                    }
                }
                else if (prod[i][0] != c) {
                    int k;
                    for (k = 0; k < n; k++)
                        if (nonT[k] == prod[i][0])
                            break;
                    findFOLLOW(prod[i][0], idx);
                }
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (E=TR):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
        nonT[i] = prod[i][0];
        FIRST[i][0] = '\0';
        FOLLOW[i][0] = '\0';
    }

    printf("\nFIRST SETS\n");
    for (int i = 0; i < n; i++) {
        findFIRST(nonT[i], i);
        printf("FIRST(%c) = { %s }\n", nonT[i], FIRST[i]);
    }

    printf("\nFOLLOW SETS\n");
    for (int i = 0; i < n; i++) {
        findFOLLOW(nonT[i], i);
        printf("FOLLOW(%c) = { %s }\n", nonT[i], FOLLOW[i]);
    }

    return 0;
}
// 5
// E=TR
// R=+TR
// T=FY
// Y=*FY
// F=i


