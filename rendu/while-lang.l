%{

void yyerror(char *);

#include "while-lang-types.h"
#include "y.tab.h"


%}

%%

[0-9]+  {
          yylval.ival = atoi(yytext);
          return NUM;
        }

[+*\-/()\n] {
            return *yytext;
          }

true	{
			yylval.bval = 1;
			return BCONST;
		}

false	{
			yylval.bval = 0;
			return BCONST;
		}


[<>=!&\|] 	{	
					return *yytext;
			}



[ \t]	{
			;
		}

\. {
          return *yytext;
        }

.     yyerror("invalid character");

%%

int yywrap(void) {
  return 1;
}
