#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecosys.h"


float p_ch_dir=0.01; //probabilite de changer de direction de deplacement 0.01
float p_reproduce_proie=0.9; //0.4
float p_reproduce_predateur=0.1;//.05
int temps_repousse_herbe=-1;
float p_manger = 0.5;

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!(animal->suivant));
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  assert(0<=x && x<=SIZE_X && 0<=y && y<=SIZE_Y );
  Animal *nouv = creer_animal(x,y,energie);
  
  *liste_animal = ajouter_en_tete_animal(*liste_animal,nouv);;

  }

  

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  if (animal = *liste ) {
    *liste = (*liste)->suivant ;
    free(animal);
    return;
  }
  while((*liste)->suivant){
    Animal *tmp = (*liste)->suivant ;
    if (animal = tmp){
        *liste = tmp->suivant;
        free(tmp);
        return ;
    } 
  }
  return ;
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
  Animal *tmp;
  while(liste){
    tmp = liste->suivant;
    free(liste);
    liste = tmp;
  }
  return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    assert(0<=pa->x && pa->x<=SIZE_X && 0<=pa->y && pa->y<=SIZE_Y );  /*CORRECTION*/
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      assert(0<=pa->x && pa->x<=SIZE_X && 0<=pa->y && pa->y<=SIZE_Y );  /*CORRECTION*/
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/
void ecrire_ecosys(const char *nom_fichier, Animal * liste_predateur,Animal * liste_proie){
  FILE *f;
  f = fopen(nom_fichier,"w");
  assert(f);
  fprintf(f,"<proie>\n");
  while(liste_proie){
    fprintf(f,"x=%d,y=%d,dir=[%d,%d],e=%.6f\n",liste_proie->x,liste_proie->y,liste_proie->dir[0],liste_proie->dir[1],liste_proie->energie);
    liste_proie=liste_proie->suivant;
  }
  fprintf(f,"</proie>\n");
  fprintf(f,"<predateur>\n");
  while(liste_predateur){
    fprintf(f,"x=%d,y=%d,dir=[%d,%d],e=%.6f\n",liste_predateur->x,liste_predateur->y,liste_predateur->dir[0],liste_predateur->dir[1],liste_predateur->energie);
    liste_predateur=liste_predateur->suivant;
  }
  fprintf(f,"</predateur>\n");
  fclose(f);
}

void lire_ecosys(const char *nom_fichier,Animal **liste_predateur,Animal **liste_proie){
  FILE *f;
  f = fopen(nom_fichier,"r");
  assert(f);
  char buffer[130];

  if(fgets(buffer,130,f)==NULL||(strcmp(buffer,"<proie>\n")!= 0))printf("erreur Proies \n");

  while(fgets(buffer,130,f)!= NULL&& strcmp(buffer,"</proie>\n")!=0){
    int x,y,dir[2];
    float energie;
    int n = sscanf(buffer,"x=%d,y=%d,dir=[%d,%d],e=%f",&x,&y,&dir[0],&dir[1],&energie);
    Animal * a = creer_animal(x,y,energie);
    a->dir[0]=dir[0];
    a->dir[1]=dir[1];
    *liste_proie = ajouter_en_tete_animal(*liste_proie,a);
  }

  if(fgets(buffer,130,f)==NULL||(strcmp(buffer,"<predateur>\n")!= 0)) printf("erreur Predateurs \n");

  while(fgets(buffer,130,f)!= NULL&& strcmp(buffer,"</predateur>\n")!=0){
    int x,y,dir[2];
    float energie;
    int n = sscanf(buffer,"x=%d,y=%d,dir=[%d,%d],e=%f",&x,&y,&dir[0],&dir[1],&energie);
    Animal * a = creer_animal(x,y,energie);
    a->dir[0]=dir[0];
    a->dir[1]=dir[1];
    *liste_predateur= ajouter_en_tete_animal(*liste_predateur,a);
  }

  fclose(f);
}


/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
  while(la){    //On parcourt la liste la//
    if(la->energie >0){
      if ((float)rand() / RAND_MAX < p_ch_dir){ //Si il ne change pas de direction//
        la->dir[0] = rand()%3 -1;
        la->dir[1] = rand()%3 -1;
      }                             
                                                //Si il change de direction//
      la->x = (la->x + la->dir[0])%SIZE_X;
      la->y = (la->y + la->dir[1])%SIZE_Y;

                                                //Toricité du monde//
      if (la->x < 0){
        la->x += SIZE_X;
      }
      if (la->y < 0){
        la->y += SIZE_Y;
      }

    }

    la = la->suivant;
  }
}


/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  if(liste_animal){

    Animal *ani = *liste_animal; //Variable pour parcourir//

    while(ani){
      if (((float)rand()) / RAND_MAX < p_reproduce){
          ajouter_animal(ani->x,ani->y,ani->energie/2,liste_animal); //Ajout en tete//
          ani->energie /=2;
      }

      ani = ani->suivant;
    }    
  }
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  Animal *ani = *liste_proie;
  bouger_animaux(ani); 

  while(ani){    //Boucle de parcours

    ani->energie --;

    if(monde[ani->x][ani->y] >= 0){
      ani->energie += monde[ani->x][ani->y];
      monde[ani->x][ani->y] = temps_repousse_herbe;
    }

    if(ani->energie < 1){
      Animal *tmp = ani;
      ani = ani->suivant;        
      enlever_animal(liste_proie, tmp);
    }else{
    ani = ani->suivant;
    }
  } 
  reproduce(liste_proie,p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
  while (l) {
    if (l->x == x && l->y == y){
      return l;
    }
    l = l->suivant;
  } 
  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  Animal *pred = *liste_predateur;
  bouger_animaux(pred);
  while(pred){      //Boucle de parcours
      
    pred->energie--;
      
    if(liste_proie){
      Animal *proie =animal_en_XY(*liste_proie, pred->x, pred->y);
      if( (proie) && ((float)rand()/RAND_MAX < p_manger) ){ //Si une proie se troue au meme endroit ET proba suffisante
        pred->energie += proie->energie;
        enlever_animal(liste_proie, proie);
      }  
    }

    if(pred->energie < 1){
      Animal *tmp = pred;
      pred = pred->suivant;
      enlever_animal(liste_predateur, tmp);
    }else{
    pred = pred->suivant;
    } 
  }
  reproduce(liste_predateur,p_reproduce_predateur);

}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
  for (int i = 0; i < SIZE_X; i++) {
    for (int j = 0; j < SIZE_Y; j++) {
      monde[i][j] += 1;
    }
  }
}

