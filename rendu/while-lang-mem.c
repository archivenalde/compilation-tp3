// Theo DELACOUX et Adlane LADJAL


#include <string.h>
#include <stdio.h>

#include "while-lang-table.h"
#include "while-lang-mem.h"

#define NB_VARIABLES 100*1000


int _LOC_TABLE_[NB_VARIABLES];

int mem_get_val(int loc)
{
    return _LOC_TABLE_[loc];
}

void mem_set_val(int loc, int val)
{
    _LOC_TABLE_[loc] = val;
}
