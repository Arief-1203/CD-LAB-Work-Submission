%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%%
[ \t\r\n]+                  ;   // ignore spaces

";"                         { return SEMI; }
"="                         { return ASSIGN; }
"("                         { return LPAREN; }
")"                         { return RPAREN; }

"+"                         { return PLUS; }
"-"                         { return MINUS; }
"*"                         { return MUL; }
"/"                         { return DIV; }

[0-9]+                      { yylval.num = atoi(yytext); return NUMBER; }

[a-zA-Z_][a-zA-Z0-9_]*       { yylval.id = strdup(yytext); return ID; }

.                           { printf("❌ Unknown char: %s\n", yytext); }

%%

int yywrap() { return 1; }
