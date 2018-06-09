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



// aexpr_t mk_aexpr_var(char *name)
// {
//   aexpr_t res = NULL;

//   res = (aexpr_t)malloc(sizeof(struct aexpr));
//   if(res == NULL)
//   {
//     printf("Erreur allocation memoire 3\n");
//     exit(-1);
//   }
//   res->tag = 1;
//   //res->data.var = n;

//   return res;
// }

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
