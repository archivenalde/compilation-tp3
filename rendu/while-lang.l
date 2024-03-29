%{
// Theo DELACOUX et Adlane LADJAL
void yyerror(char *);

#include <string.h>

#include "while-lang-types.h"
#include "y.tab.h"


%}

%%

skip    return SKIP;

:=      {
        return ASSIGN;
        }

if      {
            return IF;
            }
then    return THEN;

else    return ELSE;

while   return WHILE;

do      return DO;

[0-9]+  {
          yylval.ival = atoi(yytext);
          return NUM;
        }

true	{
			yylval.bval = 1;
			return BCONST;
		}

false	{
			yylval.bval = 0;
			return BCONST;
		}

[a-zA-Z_][a-zA-Z_1-9]* 	{
				yylval.id = (char*) malloc(sizeof(char) * (yyleng + 1));
				strcpy(yylval.id, yytext);
				return ID;
			}


[<>=!&\|{}+*\-/();] 	{
					return *yytext;
			}



[ \t]	{
			;
		}

\. {
          return *yytext;
        }

\n 		;

.     {
        yyerror("invalid character");
        }

%%

int yywrap(void) {
  return 1;
}
