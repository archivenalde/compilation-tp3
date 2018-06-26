// Theo DELACOUX et Adlane LADJAL


#include <string.h>
#include <stdio.h>

#include "while-lang-table.h"
#include "while-lang-mem.h"
#include "liste.h"

static llist _VAR_TABLE_ = NULL;


var_t table_lookup_id(char *name)
{
	element* variableRecherche;

	var_t variablePosition = (var_t) malloc(sizeof(*variablePosition));
	if(variablePosition == NULL)
    {
        printf("Erreur allocation memoire mk_aexpr_num\n");
        exit(-1);
    }

	variablePosition->name = (char*) malloc(sizeof(char) * (strlen(name) + 1));
	if(variablePosition->name == NULL)
    {
        printf("Erreur allocation memoire mk_aexpr_num\n");
        exit(-1);
    }

	strcpy(variablePosition->name, name);

	variableRecherche = rechercherElement(_VAR_TABLE_, variablePosition);

	free(variablePosition->name);
	free(variablePosition);

	return variableRecherche == NULL ? NULL : variableRecherche->variable;
}

var_t table_add_id(char* name)
{
	static int location = 0;

	/* Si la variable est deja presente, on ne faait que retourner ladite variable */
	if (table_lookup_id(name) != NULL)
		return table_lookup_id(name);

	var_t variableAjout = (var_t) malloc(sizeof(*variableAjout));
	if(variableAjout == NULL)
    {
        printf("Erreur allocation memoire mk_aexpr_num\n");
        exit(-1);
    }

	variableAjout->name = (char*) malloc(sizeof(char) * (strlen(name) + 1));
	if(variableAjout->name == NULL)
    {
        printf("Erreur allocation memoire mk_aexpr_num\n");
        exit(-1);
    }

	variableAjout->loc = location;
	strcpy(variableAjout->name, name);

	_VAR_TABLE_ = ajoutEnFin(_VAR_TABLE_, variableAjout);
	location++;

	return variableAjout;
}

int print_var_values(void)
{
	element* tmp = _VAR_TABLE_;
	var_t variableIterateur;
	int nbVariables = 0; //Compte le nombre de variables presentent dans la table

	while(tmp != NULL)
	{
		nbVariables++;
		variableIterateur = tmp->variable;
		printf("%s = %d\n", variableIterateur->name, mem_get_val(variableIterateur->loc));
		tmp = tmp->nxt;
	}

	return nbVariables;
}
