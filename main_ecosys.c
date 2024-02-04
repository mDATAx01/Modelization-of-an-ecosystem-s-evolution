#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include <unistd.h>
#include "ecosys.h"



#define NB_PROIES 50
#define NB_PREDATEURS 50
#define T_WAIT 40000
#define NB_ITERATIONS 250

#define ENERGIE_PROIES 50
#define ENERGIE_PREDATEURS 50


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
/*(Initialisés dans ecosys.c)
float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;
float p_manger = 1;
*/


int main() {
  /* A completer. Part 2:*/
  /* exercice 4, questions 2 et 4 */
  /*
  int energie =10;
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  ajouter_animal(20, 0, energie, &liste_proie);
  ajouter_animal(7, 20, energie, &liste_predateur);
  bouger_animaux(liste_proie);
  bouger_animaux(liste_predateur);
  afficher_ecosys(liste_predateur, liste_proie);
  reproduce(&liste_proie,1.0);
  reproduce(&liste_predateur, 1.0);
  */

  


  /* exercice 6, question 2*/
  // Creation et initialisation du monde
  int monde[SIZE_X][SIZE_Y];
	for(int i = 0; i < SIZE_X; i++){
		for(int j = 0; j < SIZE_Y; j++){
			monde[i][j] = 0;
		}
  }

  //Creation et initialisation liste proies
  Animal *liste_proie = NULL;
    for (int i = 0; i < NB_PROIES; i++) {
        ajouter_animal( rand()%SIZE_X, rand()%SIZE_Y, ENERGIE_PROIES, &liste_proie);
    }

  //Creation et initialisation liste predateurs
  Animal *liste_predateur = NULL;
    for (int i = 0; i < NB_PREDATEURS; i++) {
        ajouter_animal( rand()%SIZE_X, rand()%SIZE_Y, ENERGIE_PREDATEURS, &liste_predateur);
    }

  //Evolution finale de l ecosys
  FILE *fD = fopen("Evol_PopDATA.txt", "w"); //Ecriture de Evol_PopDATA.txt
  FILE *fG= fopen("Evol_PopPLOT.txt", "w"); //Ecriture de Evol_PopDATA.txt
  afficher_ecosys(liste_predateur, liste_proie);

  for (int i = 0; i < NB_ITERATIONS; i++) {
      if ( compte_animal_rec(liste_proie) <= 0  ) {
        printf("Plus de proies !\n");
        break;
      };
      if ( compte_animal_rec(liste_predateur) <= 0  ) {
        printf("Plus de predateurs !\n");
        break;
      };
     
      //usleep(T_WAIT);         
      printf("Iteration  %d :\n", i+1);
      fprintf(fD, "Iteration: %d | Nb Proies: %d | Nb Predateurs: %d\n", i, compte_animal_rec(liste_proie), compte_animal_rec(liste_predateur)); 
      fprintf(fG,"%d  %d  %d\n",i, compte_animal_rec(liste_proie), compte_animal_rec(liste_predateur));
      afficher_ecosys(liste_proie, liste_predateur);
      // rafraichissement  
      rafraichir_monde( monde );
      rafraichir_proies( &liste_proie, monde );
      rafraichir_predateurs( &liste_predateur, &liste_proie );
    }
    fclose(fD);
    fclose(fG);

// liberation de la memoire
  liberer_liste_animaux(liste_predateur);
  liberer_liste_animaux(liste_proie);

  return 0;
}

