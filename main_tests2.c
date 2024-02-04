#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


int main(){
    /*Creation des listes */
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;
    int energie=10;

    /*Création ecosysteme */
    for(int i=0;i<20;i++){
        ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_proie);
        ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_predateur);
    }

    /*Affichage de l'ecosysteme */
    printf("le nombre de proie est de %d\n",compte_animal_rec(liste_proie));
    printf("le nombre de predateur est de %d\n",compte_animal_rec(liste_predateur));
    afficher_ecosys(liste_predateur,liste_proie);

    /*Verification du nombre */
    assert((compte_animal_rec(liste_proie)==20)&&(compte_animal_rec(liste_predateur))==20);

    /*Test enlever animal */
    enlever_animal(&liste_proie,liste_proie->suivant);
    enlever_animal(&liste_predateur,liste_predateur->suivant);
    printf("le nombre de proie est de %d\n",compte_animal_rec(liste_proie));
    printf("le nombre de predateur est de %d\n",compte_animal_rec(liste_predateur));
    



/*PART 2 */

//Test Ecriture / Lecture fichier
afficher_ecosys(liste_proie,liste_predateur);
printf("le nombre de proies ECRITES est de %d\n",compte_animal_rec(liste_proie));
printf("le nombre de predateurs ECRITS est de %d\n",compte_animal_rec(liste_predateur));
ecrire_ecosys("test.txt",liste_predateur,liste_proie);


Animal *l_proie = NULL;
Animal *l_predateur = NULL;
lire_ecosys("test.txt",&l_predateur,&l_proie);
afficher_ecosys(l_proie,l_predateur);
printf("le nombre de proies LUES est de %d\n",compte_animal_rec(liste_proie));
printf("le nombre de predateurs LUS est de %d\n",compte_animal_rec(liste_predateur));
liberer_liste_animaux(l_proie);
liberer_liste_animaux(l_predateur);


/*A LA FIN */
/*Liberation de la memoire*/
liberer_liste_animaux(liste_proie);
liberer_liste_animaux(liste_predateur);

return 0;
}