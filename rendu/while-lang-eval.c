#include <stdlib.h>
#include <stdio.h>

#include "while-lang-table.h"
#include "while-lang-mem.h"
#include "while-lang-eval.h"


int eval_aexpr(aexpr_t ae)
{
    int verif0;
    if (ae->tag == 0)
        return ae->data.num;
  else if (ae->tag == 1)
  {
      return mem_get_val(table_lookup_id(ae->data.var->name)->loc);
  }
  else if (20 < ae->tag && ae->tag < 30)
  {
    switch (ae->tag) {
      case 21:
        return eval_aexpr(ae->data.expr);
        break;
      case 22:
        return -eval_aexpr(ae->data.expr);
        break;
    }
  }
  else {
    switch (ae->tag) {
    case 31:
      return eval_aexpr(ae->data.binop.lexpr) + eval_aexpr(ae->data.binop.rexpr);
      break;
    case 32:
      return eval_aexpr(ae->data.binop.lexpr) - eval_aexpr(ae->data.binop.rexpr);
      break;
    case 33:
      return eval_aexpr(ae->data.binop.lexpr) * eval_aexpr(ae->data.binop.rexpr);
      break;
    case 34:
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


boolean eval_bexpr(bexpr_t be)
{
  if (be->tag == 0)
    return be->data.bval;
  else if (be->tag == 1)
  {
    return !eval_bexpr(be->data.expr);
  }
  else if (30 < be->tag && be->tag < 40)
  {
    switch (be->tag)
    {
      case 31:
        return eval_bexpr(be->data.binop.lexpr) && eval_bexpr(be->data.binop.rexpr);
        break;
      case 32:
        eval_bexpr(be->data.binop.lexpr) || eval_bexpr(be->data.binop.rexpr);
        break;
    }
  }
  else
  {
    switch (be->tag)
    {
      case 41:
        return eval_aexpr(be->data.comp.lexpr) > eval_aexpr(be->data.comp.rexpr);
        break;
      case 42:
        return eval_aexpr(be->data.comp.lexpr) < eval_aexpr(be->data.comp.rexpr);
        break;
      case 43:
        return eval_aexpr(be->data.comp.lexpr) == eval_aexpr(be->data.comp.rexpr);
        break;
      case 44:
        return eval_aexpr(be->data.comp.lexpr) >= eval_aexpr(be->data.comp.rexpr);
        break;
      case 45:
        return eval_aexpr(be->data.comp.lexpr) <= eval_aexpr(be->data.comp.rexpr);
        break;
    }
  }
}

void eval_cmd(cmd_t cmd)
{
    switch (cmd->tag) {
        case 0: //skip
            return;
            break;
        case 1:
            mem_set_val(cmd->data.cmd_ass.var->loc, eval_aexpr(cmd->data.cmd_ass.expr));
            break;
        case 2:
            eval_cmd(cmd->data.cmd_seq.cmd1);
            eval_cmd(cmd->data.cmd_seq.cmd2);
            break;
        case 3:
            if (eval_bexpr(cmd->data.cmd_ite.test))
                eval_cmd(cmd->data.cmd_ite.cmd_then);
            else
                eval_cmd(cmd->data.cmd_ite.cmd_else);
            break;
        case 4:
            while (eval_bexpr(cmd->data.cmd_while.test))
                eval_cmd(cmd->data.cmd_while.cmd_body);
            break;
    }
}
