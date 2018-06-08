//
//  while-lang-main.c
//  2014-15-Compil-Projet
//
//  Created by Stefano Guerrini on 11/06/2015.
//  Copyright (c) 2015 Stefano Guerrini. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "while-lang-table.h"
#include "while-lang-mem.h"
#include "y.tab.h"

int yyparse();

int main(int argc, const char * argv[]) {
    /* add variables to symbol table
     *
     * uncomment for testing exercie 2 and following
     */
    /*
    table_add_id("x");
    table_add_id("y");
    table_add_id("z");
     */
    
    /* initialise variables
     *
    /* uncomment for testing exercie 6 and following
     */
    /*
    mem_set_val(table_lookup_id("x")->loc, 3);
    mem_set_val(table_lookup_id("y")->loc, 1);
    mem_set_val(table_lookup_id("z")->loc, -1);
     */

    printf("> ");
    while (yyparse() != -1) {
        printf("> ");
    }
    printf("\nBye...\n");
}