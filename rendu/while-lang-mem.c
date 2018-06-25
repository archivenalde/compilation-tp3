#include <string.h>
#include <stdio.h>

#include "while-lang-table.h"
#include "while-lang-mem.h"


int _LOC_TABLE_[10000];

int mem_get_val(int loc)
{
    return _LOC_TABLE_[loc];
}

void mem_set_val(int loc, int val)
{
    _LOC_TABLE_[loc] = val;
}
