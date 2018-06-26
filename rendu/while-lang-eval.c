// Theo DELACOUX et Adlane LADJAL


#include "while-lang-eval.h"

#include "while-lang-table.h"
#include "while-lang-mem.h"
#include "while-lang-types.h"

#include <stdlib.h>
#include <stdio.h>


/**********************************/

/* Evaluation des expressions arithmetiques */

/**********************************/


int eval_aexpr(aexpr_t ae)
{
    int verif0;

    if (ae->tag == NUM_AEXPR)
		return ae->data.num;
    else if (ae->tag == ID_AEXPR)
    {             
		return mem_get_val(table_lookup_id(ae->data.var->name)->loc);
    }
    else if (20 < ae->tag && ae->tag < 30)
    {
		switch (ae->tag) {
		    case UN_PLUS_AEXPR:
				return eval_aexpr(ae->data.expr);
				break;
		    case UN_MINUS_AEXPR:
				return -eval_aexpr(ae->data.expr);
				break;
		}
    }
    else {
		switch (ae->tag) {
		    case BIN_PLUS_AEXPR:
				return eval_aexpr(ae->data.binop.lexpr) + eval_aexpr(ae->data.binop.rexpr);
				break;
		    case BIN_MINUS_AEXPR:
				return eval_aexpr(ae->data.binop.lexpr) - eval_aexpr(ae->data.binop.rexpr);
				break;
		    case MULT_AEXPR:
				return eval_aexpr(ae->data.binop.lexpr) * eval_aexpr(ae->data.binop.rexpr);
				break;
		    case DIV_AEXPR:
				verif0 = eval_aexpr(ae->data.binop.rexpr);
				if(verif0 == 0)
				{
				    printf("Erreur division par 0 dans eval_aexpr\n");
				    exit(-1);
				}
				return eval_aexpr(ae->data.binop.lexpr) / verif0;
				break;
		}
    }
}

/**********************************/

/* Evaluation des expressions booleennes */

/**********************************/


boolean eval_bexpr(bexpr_t be)
{
    if (be->tag == BCONST_EXPR)
		return be->data.bval;
    else if (be->tag == NOT_EXPR)
    {
		return !eval_bexpr(be->data.expr);
    }
    else if (AND_BEXPR <= be->tag && be->tag <= OR_BEXPR)
    {
		switch (be->tag)
		{
		    case AND_BEXPR:
				return eval_bexpr(be->data.binop.lexpr) && eval_bexpr(be->data.binop.rexpr);
				break;
		    case OR_BEXPR:
				eval_bexpr(be->data.binop.lexpr) || eval_bexpr(be->data.binop.rexpr);
				break;
		}
    }
    else
    {
		switch (be->tag)
		{
		    case GREATER_BEXPR:
				return eval_aexpr(be->data.comp.lexpr) > eval_aexpr(be->data.comp.rexpr);
				break;
		    case LESSER_BEXPR:
				return eval_aexpr(be->data.comp.lexpr) < eval_aexpr(be->data.comp.rexpr);
				break;
		    case EQUAL_BEXPR:
				return eval_aexpr(be->data.comp.lexpr) == eval_aexpr(be->data.comp.rexpr);
				break;
		    case GR_OR_EQ_BEXPR:
				return eval_aexpr(be->data.comp.lexpr) >= eval_aexpr(be->data.comp.rexpr);
				break;
		    case LE_OR_EQ_BEXPR:
				return eval_aexpr(be->data.comp.lexpr) <= eval_aexpr(be->data.comp.rexpr);
				break;
			case NEQ_BEXPR:
				return eval_aexpr(be->data.comp.lexpr) != eval_aexpr(be->data.comp.rexpr);
				break;
		}
    }
}


/**********************************/

/* Evaluation des commandes */

/**********************************/


void eval_cmd(cmd_t cmd)
{
    switch (cmd->tag) {
	case SKIP_CMD: //skip
	    return;
	    break;
	case ASS_CMD:
	    mem_set_val(cmd->data.cmd_ass.var->loc, eval_aexpr(cmd->data.cmd_ass.expr));
	    break;
	case SEQ_CMD:
	    eval_cmd(cmd->data.cmd_seq.cmd1);
	    eval_cmd(cmd->data.cmd_seq.cmd2);
	    break;
	case ITE_CMD:
	    if (eval_bexpr(cmd->data.cmd_ite.test))
		eval_cmd(cmd->data.cmd_ite.cmd_then);
	    else
		eval_cmd(cmd->data.cmd_ite.cmd_else);
	    break;
	case WHILE_CMD:
	    while (eval_bexpr(cmd->data.cmd_while.test))
		eval_cmd(cmd->data.cmd_while.cmd_body);
	    break;
    }
}
