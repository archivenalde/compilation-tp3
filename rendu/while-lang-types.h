//
//  while-lang-types.h
//  2014-15-Compil-Projet
//
//  Created by Stefano Guerrini on 05/06/2015.
//  Copyright (c) 2015 Stefano Guerrini. All rights reserved.
//

#ifndef __while_lang_types__
#define __while_lang_types__

typedef enum {false, true} boolean;

typedef struct var_rec *var_t;
typedef struct aexpr *aexpr_t;
typedef struct bexpr *bexpr_t;
typedef struct cmd *cmd_t;

struct var_rec {
    char *name;                         /* variable name */
    int loc;                            /* variable location */
};

struct aexpr {
    int tag;                            /* select the value in the union */
    union {
        int num;                        /* number tag == 0 */
        var_t var;                      /* variable tag == 1x */
        struct aexpr *expr;             /* operand of a unary op tag == 2x */
        struct{
            struct aexpr *lexpr, *rexpr;    /* operands of a binary op tag == 3x */
        } binop;
    } data;
};

struct bexpr {
    int tag;                            /* select the value in the union */
    union {
        boolean bval;                   /* boolean constant  tag == 0*/
        struct bexpr *expr;             /* operand of a unary op  tag == 2x */
        struct {
            struct bexpr *lexpr, *rexpr;    /* operands of a binary op  tag == 3x */
        } binop;
        struct {
            struct aexpr *lexpr, *rexpr;    /* operands of a binary comparison tag == 4x */
        } comp;
    } data;
};

struct cmd_ass {
    var_t var;                         /* lhs variable */
    aexpr_t expr;                       /* rhs expression */
};

struct cmd_seq {
    cmd_t cmd1, cmd2;                   /* lhs and rhs commands */
};

struct cmd_ite {
    bexpr_t test;                       /* if test */
    cmd_t cmd_then, cmd_else;           /* then and else commands */
};

struct cmd_while {
    bexpr_t test;
    cmd_t cmd_body;
};

struct cmd {
    int tag;                            /* select the value in the union */
    union {
        struct cmd_ass cmd_ass;         /* assignment command */
        struct cmd_seq cmd_seq;         /* seq composition command */
        struct cmd_ite cmd_ite;         /* if-then-else command */
        struct cmd_while cmd_while;     /* while command */
    } data;
};

#endif /* defined(__while_lang_types__) */
