//
//  while-lang-mk.h
//  2014-15-Compil-Projet
//
//  Created by Stefano Guerrini on 16/06/2015.
//  Copyright (c) 2015 Stefano Guerrini. All rights reserved.
//

// Theo DELACOUX et Adlane LADJAL


#ifndef __while_lang_mk__
#define __while_lang_mk__

#include "while-lang-types.h"

aexpr_t mk_aexpr_num(int n);
aexpr_t mk_aexpr_var(char *name);
aexpr_t mk_aexpr_unop(int op, aexpr_t expr);
aexpr_t mk_aexpr_binop(int op, aexpr_t lexpr, aexpr_t rexpr);

bexpr_t mk_bexpr_bconst(boolean b);
bexpr_t mk_bexpr_unop(int op, bexpr_t expr);
bexpr_t mk_bexpr_binop(int op, bexpr_t lexpr, bexpr_t rexpr);
bexpr_t mk_bexpr_comp(int op, aexpr_t lexpr, aexpr_t rexpr);

cmd_t mk_cmd_skip(void);
cmd_t mk_cmd_ass(char *name, aexpr_t expr);
cmd_t mk_cmd_seq(cmd_t cmd1, cmd_t cmd2);
cmd_t mk_cmd_ite(bexpr_t expr, cmd_t cmd_then, cmd_t cmd_else);
cmd_t mk_cmd_while(bexpr_t expr, cmd_t cmd_body);

#endif /* defined(__while_lang_mk__) */
