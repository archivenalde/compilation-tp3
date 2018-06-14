#include <string.h>
#include <stdio.h>

#include "while-lang-table.h"
#include "while-lang-mem.h"
#include "liste.h"

static llist _VAR_TABLE_ = NULL;

int mem_get_val(int loc)
{
	return 0;
}

var_t table_lookup_id(char *name)
{
	element* variableRecherche;
	var_t variablePosition = (var_t) malloc(sizeof(*variablePosition));
	printf("%s\n", name);

	variablePosition->name = (char*) malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(variablePosition->name, name);
	printf("table_lookup_id 1\n");

	variableRecherche = rechercherElement(_VAR_TABLE_, variablePosition);
	printf("table_lookup_id 2\n");

	free(variablePosition);

	return variablePosition == NULL ? NULL : variableRecherche->variable;
}

var_t table_add_id(char* name)
{
	var_t variableAjout = (var_t) malloc(sizeof(*variableAjout));

	variableAjout->name = (char*) malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(variableAjout->name, name);

	_VAR_TABLE_ = ajoutEnFin(_VAR_TABLE_, variableAjout);


	return variableAjout;
}

int print_var_values(void)
{
	element* tmp = _VAR_TABLE_;
	var_t variableIterateur;

	while(tmp != NULL)
	{
		variableIterateur = tmp->variable;
		printf("%s = %d\n", variableIterateur->name, mem_get_val(variableIterateur->loc));
	}

	if (tmp == NULL)
		return 0;
	return 1;
}