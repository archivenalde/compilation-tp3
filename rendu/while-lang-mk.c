// Theo DELACOUX et Adlane LADJAL


#include "while-lang-mk.h"

#include "while-lang-types.h"
#include "while-lang-table.h"

#include <stdio.h>
#include <stdlib.h>



/**********************************/

/* Construction des expressions arithmetiques */

/**********************************/

aexpr_t mk_aexpr_num(int n)
{
    aexpr_t res = NULL;

    res = (aexpr_t)malloc(sizeof(struct aexpr));
    if(res == NULL)
    {
        printf("Erreur allocation memoire mk_aexpr_num\n");
        exit(-1);
    }

    res->tag = NUM_AEXPR;
    res->data.num = n;

    return res;
}

aexpr_t mk_aexpr_var(char *name)
{
    aexpr_t res = NULL;

    res = (aexpr_t)malloc(sizeof(struct aexpr));
    if(res == NULL)
    {
        printf("Erreur allocation memoire 3\n");
        exit(-1);
    }

    res->tag = ID_AEXPR;
    res->data.var = table_lookup_id(name);

    if(res->data.var == NULL)
    {
        printf("Erreur dans mk_aexpr_var, variable non presente dans la table\n");
        exit(-1);
    }

    return res;
}

aexpr_t mk_aexpr_unop(int op, aexpr_t expr)
{
    aexpr_t res = NULL;

    res = (aexpr_t)malloc(sizeof(struct aexpr));
    if(res == NULL)
    {
        printf("Erreur allocation memoire mk_aexpr_unop\n");
        exit(-1);
    }

    switch (op)
    {
        case '+':
            res->tag = UN_PLUS_AEXPR;
            break;
        case '-':
            res->tag = UN_MINUS_AEXPR;
            break;
    }
    res->data.expr = expr;

    return res;
}


aexpr_t mk_aexpr_binop(int op, aexpr_t lexpr, aexpr_t rexpr)
{

    aexpr_t res = NULL;

    res = (aexpr_t)malloc(sizeof(struct aexpr));
    if(res == NULL)
    {
        printf("Erreur allocation memoire mk_aexpr_binop\n");
        exit(-1);
    }

    switch (op)
    {
        case '+':
            res->tag = BIN_PLUS_AEXPR;
            break;
        case '-':
            res->tag = BIN_MINUS_AEXPR;
            break;
        case '*':
            res->tag = MULT_AEXPR;
            break;
        case '/':
            res->tag = DIV_AEXPR;
            break;
    }

    res->data.binop.lexpr = lexpr;
    res->data.binop.rexpr = rexpr;

    return res;
}





/**********************************/

/* Construction des expressions booleennes */

/**********************************/



bexpr_t mk_bexpr_bconst(boolean b)
{
    bexpr_t res = NULL;

    res = (bexpr_t) malloc(sizeof(struct bexpr));
    if (res == NULL)
    {
        printf("Erreur allocation memoire mk_bepr_bconst\n");
        exit(-1);
    }

    res->tag = BCONST_EXPR;
    res->data.bval = b;

    return res;
}





bexpr_t mk_bexpr_unop(int op, bexpr_t expr)
{
    bexpr_t res = NULL;

    res = (bexpr_t) malloc(sizeof(struct bexpr));
    if (res == NULL)
    {
        printf("Erreur allocation memoire mk_bexpr_unop\n");
        exit(-1);
    }

    res->tag = NOT_EXPR;
    res->data.expr = expr;

    return res;
}


bexpr_t mk_bexpr_binop(int op, bexpr_t lexpr, bexpr_t rexpr)
{
    bexpr_t res = NULL;

    res = (bexpr_t)malloc(sizeof(struct bexpr));
    if(res == NULL)
    {
        printf("Erreur allocation memoire mk_bexpr_binop\n");
        exit(-1);
    }

    switch (op)
    {
        case '&':
            res->tag = AND_BEXPR;
            break;
        case '|':
            res->tag = OR_BEXPR;
            break;
    }
    res->data.binop.lexpr = lexpr;
    res->data.binop.rexpr = rexpr;

    return res;
}


bexpr_t mk_bexpr_comp(int op, aexpr_t lexpr, aexpr_t rexpr)
{
    bexpr_t res = NULL;

    res = (bexpr_t)malloc(sizeof(struct bexpr));
    if(res == NULL)
    {
        printf("Erreur allocation memoire mk_bexpr_comp\n");
        exit(-1);
    }

    switch (op)
    {
        case '>':
            res->tag = GREATER_BEXPR;
            break;
        case '<':
            res->tag = LESSER_BEXPR;
            break;
        case '=':
            res->tag = EQUAL_BEXPR;
            break;
        case GR_OR_EQ_BEXPR: // >=
            res->tag = GR_OR_EQ_BEXPR;
            break;
        case LE_OR_EQ_BEXPR: // <=
            res->tag = LE_OR_EQ_BEXPR;
            break;
        case NEQ_BEXPR:
            res->tag = NEQ_BEXPR;
            break;
    }
    res->data.comp.lexpr = lexpr;
    res->data.comp.rexpr = rexpr;

    return res;
}



/**********************************/

/* Construction des commandes */

/**********************************/


cmd_t mk_cmd_skip(void)
{
    cmd_t res = NULL;

    res = (cmd_t)malloc(sizeof(*res));
    if(res == NULL)
    {
        printf("Erreur allocation memoire cmd_t dans mk_cmd_skip\n");
        exit(-1);
    }

    res->tag = SKIP_CMD;

    return res;
}

cmd_t mk_cmd_ass(char *name, aexpr_t expr)
{
    cmd_t res = NULL;

    res = (cmd_t)malloc(sizeof(*res));
    if(res == NULL)
    {
        printf("Erreur allocation memoire cmd_t dans mk_cmd_skip\n");
        exit(-1);
    }

    table_add_id(name); //La fonction test d'abord si la varible n'est pas deja presente dans la table de variable
    res->tag = ASS_CMD;
    res->data.cmd_ass.var = table_lookup_id(name);
    res->data.cmd_ass.expr = expr;

    if(res->data.cmd_ass.var == NULL)
    {
        printf("Erreur fonction mk_cmd_ass, variable (%s) introuvable dans le tableau\n",name);
        exit(-1);
    }

    return res;
}

cmd_t mk_cmd_seq(cmd_t cmd1, cmd_t cmd2)
{
    cmd_t res = NULL;

    res = (cmd_t)malloc(sizeof(*res));
    if(res == NULL)
    {
        printf("Erreur allocation memoire cmd_t dans mk_cmd_skip\n");
        exit(-1);
    }

    res->tag = SEQ_CMD;
    res->data.cmd_seq.cmd1 = cmd1;
    res->data.cmd_seq.cmd2 = cmd2;

    return res;
}

cmd_t mk_cmd_ite(bexpr_t expr, cmd_t cmd_then, cmd_t cmd_else)
{
    cmd_t res = NULL;

    res = (cmd_t)malloc(sizeof(*res));
    if(res == NULL)
    {
        printf("Erreur allocation memoire cmd_t dans mk_cmd_skip\n");
        exit(-1);
    }

    res->tag = ITE_CMD;
    res->data.cmd_ite.test = expr;
    res->data.cmd_ite.cmd_then = cmd_then;
    res->data.cmd_ite.cmd_else = cmd_else;

    return res;
}

cmd_t mk_cmd_while(bexpr_t expr, cmd_t cmd_body)
{
    cmd_t res = NULL;

    res = (cmd_t)malloc(sizeof(*res));
    if(res == NULL)
    {
        printf("Erreur allocation memoire cmd_t dans mk_cmd_skip\n");
        exit(-1);
    }
    
    res->tag = WHILE_CMD;
    res->data.cmd_while.test = expr;
    res->data.cmd_while.cmd_body = cmd_body;

    return res;
}


