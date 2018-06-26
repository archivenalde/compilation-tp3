//
//  while-lang-types.h
//  2014-15-Compil-Projet
//
//  Created by Stefano Guerrini on 05/06/2015.
//  Copyright (c) 2015 Stefano Guerrini. All rights reserved.
//

// Theo DELACOUX et Adlane LADJAL

#ifndef __while_lang_types__
#define __while_lang_types__

typedef enum {false, true} boolean;

typedef struct var_rec *var_t;
typedef struct aexpr *aexpr_t;
typedef struct bexpr *bexpr_t;
typedef struct cmd *cmd_t;

#define NUM_AEXPR 0
#define ID_AEXPR 1

#define UN_PLUS_AEXPR 21
#define UN_MINUS_AEXPR 22

#define BIN_PLUS_AEXPR 31
#define BIN_MINUS_AEXPR 32
#define MULT_AEXPR 33
#define DIV_AEXPR 34



#define BCONST_EXPR 0
#define NOT_EXPR 1

#define AND_BEXPR 31
#define OR_BEXPR 32

#define GREATER_BEXPR 41
#define LESSER_BEXPR 42
#define EQUAL_BEXPR 43
#define GR_OR_EQ_BEXPR 44
#define LE_OR_EQ_BEXPR 45
#define NEQ_BEXPR 46



#define SKIP_CMD 0
#define ASS_CMD 1
#define SEQ_CMD 2
#define ITE_CMD 3
#define WHILE_CMD 4

/* Structure de variable */

struct var_rec {
    char *name;                         /* variable name */
    int loc;                            /* variable location */
};


/* Structure des expressions arithmetiques */

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


/* Structure des expressions booleennes */

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


/* Structures des commandes */

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
