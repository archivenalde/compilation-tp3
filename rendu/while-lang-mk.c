#include "while-lang-mk.h"
#include "while-lang-types.h"
#include "while-lang-table.h"
#include <stdio.h>
#include <stdlib.h>


aexpr_t mk_aexpr_num(int n)
{
  aexpr_t res = NULL;
  res = (aexpr_t)malloc(sizeof(struct aexpr));
  if(res == NULL)
  {
    printf("Erreur allocation memoire mk_aexpr_num\n");
    exit(-1);
  }

  res->tag = 0;
  res->data.num = n;

  return res;
}

bexpr_t mk_bexpr_bconst(boolean b)
{
  bexpr_t res = NULL;
  res = (bexpr_t) malloc(sizeof(struct bexpr));
  if (res == NULL)
  {
    printf("Erreur allocation memoire mk_bepr_bconst\n");
    exit(-1);
  }

  res->tag = 0;
  res->data.bval = b;

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
  res->tag = 1;
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
      res->tag = 21;
      break;
    case '-':
      res->tag = 22;
      break;
  }
  res->data.expr = expr;

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

  res->tag = 1;
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
      res->tag = 31;
      break;
    case '-':
      res->tag = 32;
      break;
    case '*':
      res->tag = 33;
      break;
    case '/':
      res->tag = 34;
      break;
  }

  res->data.binop.lexpr = lexpr;
  res->data.binop.rexpr = rexpr;

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
      res->tag = 31;
      break;
    case '|':
      res->tag = 32;
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
      res->tag = 41;
      break;
    case '<':
      res->tag = 42;
      break;
    case '=':
      res->tag = 43;
      break;
    case 44: // >=
      res->tag = 44;
      break;
    case 45: // <=
      res->tag = 45;
      break;
  }

  res->data.comp.lexpr = lexpr;
  res->data.comp.rexpr = rexpr;

  return res;
}



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

cmd_t mk_cmd_skip(void)
{
    cmd_t res = NULL;
    res = (cmd_t)malloc(sizeof(*res));
    if(res == NULL)
    {
        printf("Erreur allocation memoire cmd_t dans mk_cmd_skip\n");
        exit(-1);
    }
    res->tag = 0;
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
    res->tag = 1;
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
    res->tag = 2;
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
    res->tag = 3;
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
    res->tag = 4;
    res->data.cmd_while.test = expr;
    res->data.cmd_while.cmd_body = cmd_body;

    return res;
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
            putchar('\n');
            printf(" then ");
            pr_cmd(c->data.cmd_ite.cmd_then);
            printf(" else ");
            pr_cmd(c->data.cmd_ite.cmd_else);
            break;
        case 4:
            printf(" while ");
            pr_bexpr(c->data.cmd_while.test);
            putchar('\n');
            printf(" do\n");
            pr_cmd(c->data.cmd_while.cmd_body);
            break;
    }
}
