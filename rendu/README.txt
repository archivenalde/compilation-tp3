Ce devoir a été réalisé par Théo DELACOUX et Adlane LADJAL.
Il modélise un compilateur du langage WHILE vu en cours de SLP.



------Instructions d'exécutions et de compilation------

Pour lancer le programme, tapez la commande make dans le dossier rendu.
Pour exécuter : ./exe < <fichier de test>



------Les tests------

Nous avons fourni plusieurs fichiers de test dans le dossier TESTS.
L'exécution du code s'arrête à la première erreur rencontrée, et donne une desc\
ription de cette erreur.
Sinon le programme termine et ">Bye..." s'affiche.

test-1.txt : calcul du factoriel.
test-2.txt : calcul du pgcd.
test-3.txt : erreur avec une division par 0.
test-4.txt : erreur avec une variable appele sans etre initialisee.

Les resultats du terminal sont contenus dans les fichiers "res-*".



------Substilités de la syntaxe de notre langage------

La dernière commande d'un programme doit terminer par un '.' au lieu du ';'.
Pour indiquer la fin d'un fichier il faut mettre un '.'.
Toutes commandes et tout bloc doivent etre séparés par des ';'.
Sauf la dernière commande d'un bloc, qui ne contient pas de ';' à la fin de la commande.



------La table des locations------

Pour stocker les valeurs des varibales à leurs locations respectives, nous avons choisi un tableau statique. Cela nous limite alors forcément le nombre de varibles, bien que nous pouvons choisir un nombre aussi grand que l'on veut.
Ce nombre est défini dans while-lang-mem.c, et par défaut il est initialisé à 100 000.
Vous pouvez modifiez ce nombre si vous souhaitez mettre plus de 100 000 variables dans un programme, bien que nous doutions de l'utilité de la chose. 




Bonne correction,

Théo DELACOUX et Adlane LADJAL

