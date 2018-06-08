%{

void yyerror(char *);

#include "while-lang-types.h"
#include "y.tab.h"


%}

%%

[0-9]+          {
                    yylval.ival = atoi(yytext);
                    return NUM;
                }

true            {
                    yylval.bval = 1;
                    return BCONST;
                }

false           {
                    yylval.bval = 0;
                    return BCONST;
                }

[+*\-/()\n]     {
                    return *yytext;
                }

(and|or|imp)    {
                    return *yytext;
                }

"<="            {
                    return *yytext;
                }

">="              {
                    printf("Bonjour");
                    return *yytext;
                }

[!<>=]          {
                    return *yytext;
                }


[ \.\t] {;}

. yyerror("invalid character");

%%

int yywrap(void) {
  return 1;
}
