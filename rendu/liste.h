#include <stdlib.h>
#include <stdio.h>
#include "while-lang-types.h"

#define ERREUR -1

typedef struct element_s element;
struct element_s
{
    var_t variable;
    struct element_s *nxt;
};
typedef element* llist;




llist ajoutEnTete		(llist liste, var_t variable);
llist ajoutEnFin		(llist liste, var_t variable);
llist ajout 			(llist liste, var_t variable, int ieme); //On commence à partir de 0

/*void deplacerTete		(llist* liste1, llist* liste2); //deplacer liste1 dans liste2

llist suppEnTete		(llist liste);
llist suppEnFin 		(llist liste);
llist supp 				(llist liste, int indice);
llist suppall			(llist liste);
//llist suppallelmt		(llist liste, int valeur);
*/
llist rechercherElement	(llist liste, var_t variable);
llist ieme_element 		(llist liste, unsigned int ieme);
/*llist suite 			(llist liste);

int estVide				(llist liste);
int nombreOccurence 	(llist liste, int valeur);*/
int comptNbrElmt		(llist liste);
/*int valeur				(element* elmt);*/


void  afficherListe		(llist liste);