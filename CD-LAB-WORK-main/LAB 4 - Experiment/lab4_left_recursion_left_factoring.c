#include <stdio.h>
#include <string.h>

/* -------- LEFT RECURSION -------- */
void eliminateLeftRecursion(char nt, char alpha[], char beta[]) {
    printf("\nAfter Eliminating Left Recursion:\n");
    printf("%c -> %s%c'\n", nt, beta, nt);
    printf("%c' -> %s%c' | ε\n", nt, alpha, nt);
}

/* -------- LEFT FACTORING -------- */
void leftFactoring(char nt, char p1[], char p2[]) {
    int i = 0;
    char common[20] = "";

    while (p1[i] == p2[i]) {
        common[i] = p1[i];
        i++;
    }
    common[i] = '\0';

    printf("\nAfter Left Factoring:\n");
    printf("%c -> %s%c'\n", nt, common, nt);
    printf("%c' -> %s | %s\n", nt, p1 + i, p2 + i);
}

int main() {
    char nt;
    char alpha[20], beta[20];
    char p1[20], p2[20];

    printf("LEFT RECURSION ELIMINATION\n");
    printf("-------------------------\n");
    printf("Enter Non-Terminal: ");
    scanf(" %c", &nt);

    printf("Enter alpha (recursive part): ");
    scanf("%s", alpha);

    printf("Enter beta (non-recursive part): ");
    scanf("%s", beta);

    eliminateLeftRecursion(nt, alpha, beta);

    printf("\nLEFT FACTORING\n");
    printf("-------------\n");
    printf("Enter Non-Terminal: ");
    scanf(" %c", &nt);

    printf("Enter Production 1: ");
    scanf("%s", p1);

    printf("Enter Production 2: ");
    scanf("%s", p2);

    leftFactoring(nt, p1, p2);

    return 0;
}
