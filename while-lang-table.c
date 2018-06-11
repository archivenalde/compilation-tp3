#include "while-lang-mk.h"
#include "while-lang-table.h"
#include <stdio.h>
#include <stdlib.h>

#include "liste.h"

llist table = NULL;

var_t table_lookup_id(char* name)
{
    var_t var = (var_t) malloc(sizeof(struct var_rec));
    if (var == NULL)
    {
        printf("Erreur allocation memoire table_lookup_id\n");
        exit(-1);
    }

    llist emplacement = rechercherElement(table, var);

    free(var);

    return (emplacement == NULL) ? emplacement->variable) : NULL;
}

var_t table_add_id(char* name)
{
    
}
