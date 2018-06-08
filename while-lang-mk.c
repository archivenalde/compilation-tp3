#include "while-lang-mk.h"
#include "while-lang-types.h"
#include <stdio.h>
#include <stdlib.h>


aexpr_t mk_aexpr_num(int n)
{
  aexpr_t res = NULL;
  res = (aexpr_t)malloc(sizeof(struct aexpr));
  if(res == NULL)
  {
    printf("Erreur allocation memoire 4\n");
    exit(-1);
  }

  res->tag = 0;
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
  res->tag = 1;
  //res->data.var = n;

  return res;
}

aexpr_t mk_aexpr_unop(int op, aexpr_t expr)
{
  aexpr_t res = NULL;
  res = (aexpr_t)malloc(sizeof(struct aexpr));
  if(res == NULL)
  {
    printf("Erreur allocation memoire 2\n");
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

aexpr_t mk_aexpr_binop(int op, aexpr_t lexpr, aexpr_t rexpr)
{

  aexpr_t res = NULL;
  res = (aexpr_t)malloc(sizeof(struct aexpr));
  if(res == NULL)
  {
    printf("Erreur allocation memoire 1\n");
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

void pr_aexpr(aexpr_t ae)
{
  if (ae->tag == 0)
    printf("%d", ae->data.num);
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
