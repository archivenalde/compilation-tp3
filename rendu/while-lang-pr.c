#include "while-lang-pr.h"

#include "while-lang-types.h"

#include <stdio.h>
#include <stdlib.h>

void pr_aexpr(aexpr_t ae)
{
  if (ae->tag == 0)
    printf("%d", ae->data.num);
  else if (ae->tag == 1)
  {
      printf("%s",ae->data.var->name);
  }
  else if (20 < ae->tag && ae->tag < 30)
  {
    switch (ae->tag) {
      case 21:
        printf("+");
        break;
      case 22:
        printf("-");
        break;
    }
    pr_aexpr(ae->data.expr);
  }
  else {
    pr_aexpr(ae->data.binop.lexpr);
    switch (ae->tag) {
    case 31:
      printf("+");
      break;
    case 32:
      printf("-");
      break;
    case 33:
      printf("*");
      break;
    case 34:
      printf("/");
      break;
    }
    pr_aexpr(ae->data.binop.rexpr);
  }
}


void pr_bexpr(bexpr_t be)
{
  if (be->tag == 0)
    printf("%s", be->data.bval ? "true" : "false");
  else if (be->tag == 1)
  {
    printf("!");
    pr_bexpr(be->data.expr);
  }
  else if (30 < be->tag && be->tag < 40)
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
      case 41:
        printf(" > ");
        break;
      case 42:
        printf(" < ");
        break;
      case 43:
        printf(" = ");
        break;
      case 44:
        printf(" >= ");
        break;
      case 45:
        printf(" <= ");
        break;
    }
    pr_aexpr(be->data.comp.rexpr);
  }
}


void pr_cmd(cmd_t c)
{
    switch(c->tag)
    {
        case 0:
            printf(" skip ");
            break;
        case 1:
            printf("%s", c->data.cmd_ass.var->name);
            printf(" := ");
            pr_aexpr(c->data.cmd_ass.expr);
            break;
        case 2:
            pr_cmd(c->data.cmd_seq.cmd1);
            printf(" ; ");
            pr_cmd(c->data.cmd_seq.cmd2);
            break;
        case 3:
            printf(" if ");
            pr_bexpr(c->data.cmd_ite.test);
            printf(" then ");
            pr_cmd(c->data.cmd_ite.cmd_then);
            printf(" else ");
            pr_cmd(c->data.cmd_ite.cmd_else);
            break;
        case 4:
            printf(" while ");
            pr_bexpr(c->data.cmd_while.test);
            printf(" do ");
            pr_cmd(c->data.cmd_while.cmd_body);
            break;
    }
}