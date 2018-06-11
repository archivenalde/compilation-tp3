#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "liste.h"


llist ajoutEnTete(llist liste, var_t variable)
{
	/* On crée un nouvel élément */

	llist newElement = malloc(sizeof(element));


	/* On assigne la valeur qu'on veut */
	newElement->val = variable;


	/* On assigne l'adresse de l'élément suivant */
	newElement->nxt = liste;

	/* On retourne le nouvel élément */
	return newElement;
}



llist ajoutEnFin(llist liste, var_t variable)
{
	/*On crée le nouvel élément*/
	element* newElement = malloc(sizeof(element));

	/*On affecte la variable*/
	newElement->val = variable;

	/*On affecte l'adresse NULL car c'est le dernier élément*/
	newElement->nxt = NULL;

	/*S'il n'y a pas d'élément dans la liste alors on retourne juste l'élément qu'on vient de créer.
	La liste contient donc maintenant un élément */
	if (liste == NULL)
	{
		return newElement;
	}
	else /*Sinon*/
	{
		llist temp = liste; /*On créé un élément temporaire */
		while (temp->nxt != NULL) /*On parcourt la liste jusqu'à trouver l'élément NULL */
		{
			temp = temp->nxt; /* On avance d'un cran */
		}
		temp->nxt = newElement; /*On donne au dernier élément l'élément qu'on vient de créer */
		return liste;
	}
}


llist ajout(llist liste, var_t variable, int ieme)
{

	if (ieme == 0)
		return ajoutEnTete(liste, variable);

	int nbrElmt = comptNbrElmt(liste);

	if (ieme == nbrElmt)
		return ajoutEnFin(liste, variable);

	/*if (ieme < 0 || ieme >= nbrElmt)
		return exit(EXIT_FAILURE);*/

	element* newElement = malloc(sizeof(element));
	newElement->val = variable;

	int i = 0;

	element* tmp = liste;
	element* ptmp = liste;

	while (ieme != i)
	{
		ptmp = tmp;
		tmp = tmp->nxt;
		++i;
	}

	newElement->nxt = tmp;
	ptmp->nxt = newElement;

	return liste;
}


llist rechercherElement(llist liste, var_t variable)
{
	element* tmp = liste;
	while(tmp != NULL)
	{
		if (strcmp(tmp->val->name, variable->name) == 0)
			return tmp;

		tmp = tmp->nxt;
	}

	return NULL;
}



/*void afficherListe(llist liste)
{
	if (estVide(liste)) printf("Null\n");
	else
	{
		llist tmp = liste;
		while(tmp != NULL)
		{
			printf("%d -> ", tmp->val);

			tmp = tmp->nxt;
		}
		printf("Null\n");
	}
}


int estVide(llist liste)
{
	if (liste == NULL)
		return 1;
	return 0;
}



llist suppEnTete(llist liste)
{
	if (liste != NULL)
	{
		llist newList = liste->nxt;
		free(liste);

		return newList;
	}
	else
		return NULL;
}



llist suppEnFin(llist liste)
{
	if (liste == NULL)
		return NULL;

	if (liste->nxt == NULL)
	{
		free(liste);
		return NULL;
	}


	element* tmp = liste;
	element* ptmp = liste;
	while(tmp->nxt != NULL)
	{
		ptmp = tmp;
		tmp = tmp->nxt;
	}
	ptmp->nxt = NULL;
	free(tmp);

	return liste;
}


llist supp(llist liste, int indice)
{
	int nbr = comptNbrElmt(liste);
	int n = 0;
	if (nbr == 0) return NULL;

	if (indice == 0)
	{
		liste = suppEnTete(liste);
		return liste;
	}

	if (indice == nbr-1)
	{
		liste = suppEnFin(liste);
		return liste;
	}

	element* tmp = liste;
	element* ptmp = liste;
	while (indice != n)
	{
		ptmp = tmp;
		tmp = tmp->nxt;
		++n;
	}
	ptmp->nxt = tmp->nxt;
	free(tmp);


	return liste;

}
*/

/*


int nombreOccurence (llist liste, int valeur)
{
	int i = 0;

	if (liste == NULL)
		return 0;

	while ((liste = rechercherElement(liste, valeur)) != NULL)
	{

		liste = liste->nxt;
		++i;
	}

	return i;
}

*/

llist ieme_element (llist liste, unsigned int ieme)
{
	int i = 0;
	//element* tmp = liste;

	for (i = 0; i < ieme && liste != NULL; ++i)
		liste = liste->nxt;

	if (liste == NULL)
		return NULL;

	return liste;
}

/*

int valeur(element* elmt)
{
	if (elmt)
		return elmt->val;
	return ERREUR;
}


int comptNbrElmt(llist liste)
{
	int n = 0;
	element* tmp = liste;
	while (tmp != NULL)
	{
		tmp = tmp->nxt;
		++n;
	}

	return n;
}


llist suppall(llist liste)
{
	if (liste != NULL)
	{
		element* tmp = liste;
		liste = liste->nxt;
		free(tmp);
		return suppall(liste);
	}
	else return NULL;
}


void deplacerTete(llist* p1, llist* p2)
{
	llist aux = *p2;
	*p2 = *p1;
	*p1 = suite(*p1);
	(*p2)->nxt = aux;
}


llist suite(llist l)
{
	if (l != NULL)
		return l->nxt;
	return NULL;
}*/
