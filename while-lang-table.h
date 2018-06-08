//
//  while-lang-table.h
//  2014-15-Compil-Projet
//
//  Created by Stefano Guerrini on 16/06/2015.
//  Copyright (c) 2015 Stefano Guerrini. All rights reserved.
//

#ifndef __while_lang_table__
#define __while_lang_table__

#include "while-lang-types.h"
#include "while-lang-mem.h"

var_t table_lookup_id(char *name);

var_t table_add_id(char *name);

int print_var_values(void);

#endif /* defined(__while_lang_table__) */
