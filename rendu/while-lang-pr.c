#include "while-lang-pr.h"

#include "while-lang-types.h"

#include <stdio.h>
#include <stdlib.h>


/******************************/

/* Affichage des expressions arithmetiques */

/******************************/

void pr_aexpr(aexpr_t ae)
{
    if (ae->tag == NUM_AEXPR)
        printf("%d", ae->data.num);
    else if (ae->tag == ID_AEXPR)
    {
        printf("%s",ae->data.var->name);
    }
    else if (UN_PLUS_AEXPR <= ae->tag && ae->tag <= UN_MINUS_AEXPR)
    {
        switch (ae->tag) {
            case UN_PLUS_AEXPR:
                printf("+");
                break;
            case UN_MINUS_AEXPR:
                printf("-");
                break;
        }
        pr_aexpr(ae->data.expr);
    }
    else {
        pr_aexpr(ae->data.binop.lexpr);
        switch (ae->tag) {
            case BIN_PLUS_AEXPR:
                printf("+");
                break;
            case BIN_MINUS_AEXPR:
                printf("-");
                break;
            case MULT_AEXPR:
                printf("*");
                break;
            case DIV_AEXPR:
                printf("/");
                break;
        }
        pr_aexpr(ae->data.binop.rexpr);
    }
}


/******************************/

/* Affichage des expressions booleeenes */

/******************************/


void pr_bexpr(bexpr_t be)
{
    if (be->tag == BCONST_EXPR)
        printf("%s", be->data.bval ? "true" : "false");
    else if (be->tag == NOT_EXPR)
    {
        printf("!");
        pr_bexpr(be->data.expr);
    }
    else if (AND_BEXPR <= be->tag && be->tag <= OR_BEXPR)
    {
        pr_bexpr(be->data.binop.lexpr);
        switch (be->tag)
        {
            case 31:
                printf(" && ");
                break;
            case 32:
                printf(" || ");
                break;
        }
        pr_bexpr(be->data.binop.rexpr);
    }
    else
    {
        pr_aexpr(be->data.comp.lexpr);
        switch (be->tag)
        {
            case GREATER_BEXPR:
                printf(" > ");
                break;
            case LESSER_BEXPR:
                printf(" < ");
                break;
            case EQUAL_BEXPR:
                printf(" = ");
                break;
            case GR_OR_EQ_BEXPR:
                printf(" >= ");
                break;
            case LE_OR_EQ_BEXPR:
                printf(" <= ");
                break;
        }
        pr_aexpr(be->data.comp.rexpr);
    }
}


/******************************/

/* Affichage des commandes */

/******************************/

void pr_cmd(cmd_t c)
{
    switch(c->tag)
    {
        case SKIP_CMD:
            printf(" skip ");
            break;
        case ASS_CMD:
            printf("%s", c->data.cmd_ass.var->name);
            printf(" := ");
            pr_aexpr(c->data.cmd_ass.expr);
            break;
        case SEQ_CMD:
            pr_cmd(c->data.cmd_seq.cmd1);
            printf(" ; ");
            pr_cmd(c->data.cmd_seq.cmd2);
            break;
        case ITE_CMD:
            printf(" if ");
            pr_bexpr(c->data.cmd_ite.test);
            printf(" then ");
            pr_cmd(c->data.cmd_ite.cmd_then);
            printf(" else ");
            pr_cmd(c->data.cmd_ite.cmd_else);
            break;
        case WHILE_CMD:
            printf(" while ");
            pr_bexpr(c->data.cmd_while.test);
            printf(" do ");
            pr_cmd(c->data.cmd_while.cmd_body);
            break;
    }
}
