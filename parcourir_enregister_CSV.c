#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fiche_client{
	int age; // ya vrmnt besoin de commenter là ?
	int revenu; // revenu mensuel
	int sante; // etat de santé E ]0-100]
	int pret; // 1=oui / 0 = non

}FC;

int nb_lignes_fichier_csv(FILE *f){
	fseek(f,0,SEEK_SET);
	char lettre = fgetc(f);
	int nb = 1;
	while( lettre != EOF) {
		lettre = fgetc(f);
		if(lettre == '\n') nb++;
	}
	fseek(f,0,SEEK_SET);	//Deplacement dans f de 0 caracteres a partir du debut (pour pouvoir parcourir le fichier plusieurs fois)
	return nb - 1;
}

FC *remplir_tableau(FILE *doc){
  int i, taille = nb_lignes_fichier_csv(doc);
  FC *tab = malloc(sizeof(FC)*taille;
  FC temp = NULL;
  int nb_temp;

  for(i = 0; i < taille; i++){ //manque la fouille du csv et mettre la valeur dans nb_temp

    temp.age = nb_temp;

    temp.revenu = nb_temp;

    temp.sante = nb_temp;

    temp.pret = nb_temp;

    tab[i] = temp;
  }

  return tab;
}

FC *ajouter_valeur_tableau(FC *tab,int taille, FC val){
  tab = realloc(); //??
  tab[taille] = val;
  return tab;
}

int main(){



  return 0;
}
