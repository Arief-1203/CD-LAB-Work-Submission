%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *s);

#define MAXSYM 200
#define MAXTAC 500

// -------- SYMBOL TABLE ----------
char symTable[MAXSYM][50];
int symCount = 0;

int symbolExists(char *name){
    for(int i=0;i<symCount;i++){
        if(strcmp(symTable[i], name)==0) return 1;
    }
    return 0;
}

void addSymbol(char *name){
    if(!symbolExists(name)){
        strcpy(symTable[symCount++], name);
    }
}

// -------- TAC ----------
char tac[MAXTAC][100];
int tacCount = 0;

int tempCount = 0;
char* newTemp(){
    char *t = (char*)malloc(10);
    sprintf(t, "t%d", ++tempCount);
    return t;
}

void emit(char *line){
    strcpy(tac[tacCount++], line);
}

// -------- OPTIMIZED TAC ----------
char optTac[MAXTAC][100];
int optCount = 0;

int isNumberStr(char *s){
    for(int i=0;s[i];i++){
        if(s[i]<'0' || s[i]>'9') return 0;
    }
    return strlen(s)>0;
}

void optimize(){
    optCount = 0;
    for(int i=0;i<tacCount;i++){
        char X[20], eq[5], A[20], op[5], B[20];

        int parts = sscanf(tac[i], "%s %s %s %s %s", X, eq, A, op, B);

        // Constant folding: t = 3 * 2
        if(parts==5 && strcmp(eq,"=")==0 && isNumberStr(A) && isNumberStr(B)){
            int a = atoi(A), b = atoi(B);
            int res; int ok=1;

            if(strcmp(op,"+")==0) res = a+b;
            else if(strcmp(op,"-")==0) res = a-b;
            else if(strcmp(op,"*")==0) res = a*b;
            else if(strcmp(op,"/")==0){
                if(b==0) ok=0;
                else res = a/b;
            } else ok=0;

            if(ok){
                char newline[100];
                sprintf(newline, "%s = %d", X, res);
                strcpy(optTac[optCount++], newline);
                continue;
            }
        }

        strcpy(optTac[optCount++], tac[i]);
    }
}

void generateTarget(){
    printf("\n==============================\n");
    printf("✅ PHASE 6: TARGET CODE (Assembly-like)\n");
    printf("==============================\n");

    for(int i=0;i<optCount;i++){
        char X[20], eq[5], A[20], op[5], B[20];
        int parts = sscanf(optTac[i], "%s %s %s %s %s", X, eq, A, op, B);

        if(parts==3){
            // X = A
            printf("MOV %s, %s\n", X, A);
        } else if(parts==5){
            printf("LOAD %s\n", A);
            if(strcmp(op,"+")==0) printf("ADD %s\n", B);
            else if(strcmp(op,"-")==0) printf("SUB %s\n", B);
            else if(strcmp(op,"*")==0) printf("MUL %s\n", B);
            else if(strcmp(op,"/")==0) printf("DIV %s\n", B);
            printf("STORE %s\n", X);
        }
    }
}

%}

%union{
    int num;
    char *id;
    char *place; // for TAC result
}

%token <id> ID
%token <num> NUMBER

%token ASSIGN SEMI
%token PLUS MINUS MUL DIV
%token LPAREN RPAREN

%type <place> expr term factor

%left PLUS MINUS
%left MUL DIV

%%

program:
      program statement
    | /* empty */
    ;

statement:
      ID ASSIGN expr SEMI
      {
        // PHASE 3: semantic (assignment => declare variable)
        addSymbol($1);

        // PHASE 4: TAC final assignment
        char line[100];
        sprintf(line, "%s = %s", $1, $3);
        emit(line);
      }
    ;

expr:
      expr PLUS term
      {
        char *t = newTemp();
        char line[100];
        sprintf(line, "%s = %s + %s", t, $1, $3);
        emit(line);
        $$ = t;
      }
    | expr MINUS term
      {
        char *t = newTemp();
        char line[100];
        sprintf(line, "%s = %s - %s", t, $1, $3);
        emit(line);
        $$ = t;
      }
    | term
      { $$ = $1; }
    ;

term:
      term MUL factor
      {
        char *t = newTemp();
        char line[100];
        sprintf(line, "%s = %s * %s", t, $1, $3);
        emit(line);
        $$ = t;
      }
    | term DIV factor
      {
        char *t = newTemp();
        char line[100];
        sprintf(line, "%s = %s / %s", t, $1, $3);
        emit(line);
        $$ = t;
      }
    | factor
      { $$ = $1; }
    ;

factor:
      NUMBER
      {
        char *val = (char*)malloc(20);
        sprintf(val, "%d", $1);
        $$ = val;
      }
    | ID
      {
        // PHASE 3: semantic check
        if(!symbolExists($1)){
            printf("\n❌ SEMANTIC ERROR: Variable '%s' used before assignment!\n", $1);
            exit(0);
        }
        $$ = $1;
      }
    | LPAREN expr RPAREN
      { $$ = $2; }
    ;

%%

void yyerror(const char *s){
    printf("\n❌ SYNTAX ERROR: %s\n", s);
}

int main(){
    printf("==============================\n");
    printf("✅ MINI COMPILER USING FLEX+BISON\n");
    printf("==============================\n");

    printf("\n✅ PHASE 2: SYNTAX + PHASE 3: SEMANTIC + PHASE 4: TAC\n");
    yyparse();

    // Print Symbol Table
    printf("\n==============================\n");
    printf("✅ PHASE 3: SYMBOL TABLE\n");
    printf("==============================\n");
    for(int i=0;i<symCount;i++){
        printf("%s\n", symTable[i]);
    }

    // Print TAC
    printf("\n==============================\n");
    printf("✅ PHASE 4: INTERMEDIATE CODE (TAC)\n");
    printf("==============================\n");
    for(int i=0;i<tacCount;i++){
        printf("%s\n", tac[i]);
    }

    // Optimization
    optimize();
    printf("\n==============================\n");
    printf("✅ PHASE 5: OPTIMIZED TAC\n");
    printf("==============================\n");
    for(int i=0;i<optCount;i++){
        printf("%s\n", optTac[i]);
    }

    // Target Code
    generateTarget();

    printf("\n🎉 6 PHASE COMPILER COMPLETED!\n");
    return 0;
}
