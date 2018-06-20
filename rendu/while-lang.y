/*
 *  while-lang.y
 *  2014-15-Compil-Projet
 *
 *  Created by Stefano Guerrini on 05/06/2015.
 *  Copyright (c) 2015 Stefano Guerrini. All rights reserved.
 */

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "while-lang-types.h"
    #include "while-lang-mk.h"
    #include "while-lang-pr.h"
    #include "while-lang-table.h"
    #include "while-lang-mem.h"
    #include "while-lang-eval.h"

    int yylex(void);
    void yyerror(char const*);
%}

%union{
    char *id;
    int ival;
    boolean bval;
    cmd_t cmd;
    aexpr_t aexpr;
    bexpr_t bexpr;
}

%token<ival> NUM
%token<id> ID
%token<bval> BCONST
%token SKIP ASSIGN IF THEN ELSE WHILE DO

%type<cmd> cmd cmd1
%type<aexpr> aexpr aexpr1
%type<bexpr> bexpr

/* start symbol for arithmetic expressions */
/* %start maina */

/* start symbol for boolean expressions */
/* %start mainb */

/* start symbol for commands */
%start main

%%

main:   cmd '.'         {
                            /* print command tree */
                            pr_cmd($1);
                            putchar('\n');
                            /* eval command tree and
                             * print values of variables in symbol table
                             *
                             * uncomment for testing exercice 7.3
                             */

                            eval_cmd($1);
                            print_var_values();
                            putchar('\n');

                            return 0;
                        }
|       '.'             { return -1; }
;

maina:  aexpr '.'       {
                            /* print arithmetic expression tree */
                            pr_aexpr($1);
                            putchar('\n');
                            /* eval arithmetic expression tree
                             *
                             * uncomment for testing exercice 7.1
                             */
                            /*
                            printf("  =>  %d\n", eval_aexpr($1));
                             */
                            return 1;
                        }
|       '.'             { return -1; }
;


mainb:  bexpr '.'       {
                            /* print boolean expression tree */
                            pr_bexpr($1);
                            putchar('\n');
                            /* eval boolean expression tree
                             *
                             * uncomment for testing exercice 7.2
                             */
                            /*
                            printf(" =>  %s\n", eval_bexpr($1) ? "true" : "false");
                             */
                            return 1;
                        }
|       maina
|       '.'             { return -1; }
;

aexpr:
  aexpr '+' aexpr               { $$ = mk_aexpr_binop('+', $1, $3);}
  | aexpr '-' aexpr             { $$ = mk_aexpr_binop('-', $1, $3);}
  | '+' aexpr                   { $$ = mk_aexpr_unop('+', $2);}
  | '-' aexpr                   { $$ = mk_aexpr_unop('-', $2);}
  | aexpr1
  | ID                          {
                                  if (table_lookup_id($1) == NULL)
                                    printf("Erreur une variable n'est pas contenue dans la table");
                                  $$ = mk_aexpr_var($1);
                                }
  ;

aexpr1:
  '(' aexpr ')'                 { $$ = $2;}
  | aexpr1 '*' aexpr1           { $$ = mk_aexpr_binop('*', $1, $3);}
  | aexpr1 '/' aexpr1           { $$ = mk_aexpr_binop('/', $1, $3);}
  | '+' aexpr1                  { $$ = mk_aexpr_unop('+', $2);}
  | '-' aexpr1                  { $$ = mk_aexpr_unop('-', $2);}
  | ID                          {
                                  if (table_lookup_id($1) == NULL)
                                    printf("Erreur une variable n'est pas contenue dans la table");
                                  $$ = mk_aexpr_var($1);
                                }
  | NUM                         { $$ = mk_aexpr_num($1); }
  ;

bexpr:
  '(' bexpr ')'                 { $$ = $2; }
  | aexpr '>' aexpr             { $$ = mk_bexpr_comp('>', $1, $3);}
  | aexpr '<' aexpr             { $$ = mk_bexpr_comp('<', $1, $3);}
  | aexpr '=' aexpr             { $$ = mk_bexpr_comp('=', $1, $3);}
  | aexpr '>''=' aexpr          { $$ = mk_bexpr_comp(44, $1, $4);}
  | aexpr '<''=' aexpr          { $$ = mk_bexpr_comp(45, $1, $4);}
  | bexpr '&''&' bexpr          { $$ = mk_bexpr_binop('&', $1, $4);}
  | bexpr '|''|' bexpr          { $$ = mk_bexpr_binop('|', $1, $4);}
  | '!' bexpr                   { $$ = mk_bexpr_unop('!', $2);}
  | BCONST                      { $$ = mk_bexpr_bconst($1);}
  ;

cmd:
    cmd1 ';' cmd                { $$ = mk_cmd_seq($1, $3);}
    | cmd1                       { $$ = $1;}
    ;

cmd1:
  SKIP                          { $$ = mk_cmd_skip();}
  | ID ASSIGN aexpr             { $$ = mk_cmd_ass($1, $3);}
  | IF bexpr THEN cmd1 ELSE cmd1  { $$ = mk_cmd_ite($2, $4, $6);}
  | WHILE bexpr DO cmd1          { $$ = mk_cmd_while($2, $4);}
  | '{' cmd '}'                 { $$ = $2;}
  ;


%%

void yyerror(char const *msg) {
    fprintf (stderr, "%s\n", msg);
}

int main(void) {
   /* add variables to symbol table
     *
     * uncomment for testing exercie 2 and following
     */

    /*table_add_id("x");
    table_add_id("y");
    table_add_id("z");*/


    /* initialise variables */
    /* uncomment for testing exercie 6 and following
     */

    /*mem_set_val(table_lookup_id("x")->loc, 3);
    mem_set_val(table_lookup_id("y")->loc, 1);
    mem_set_val(table_lookup_id("z")->loc, -1);*/

    //print_var_values();

    printf("> ");
    while (yyparse() != -1) {
        printf("> ");
    }
    printf("Bye...\n");

    /*mem_set_val(table_lookup_id("x")->loc, 3);
    mem_set_val(table_lookup_id("y")->loc, 1);
    mem_set_val(table_lookup_id("z")->loc, -1);
    print_var_values();*/


    return 0;
}
