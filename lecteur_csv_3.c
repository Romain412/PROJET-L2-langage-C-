#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longueur_max_ligne = 2000;

struct vecteur{
	float *donnees;
	int taille;
	int categorie;
};typedef struct vecteur vecteur;

int nb_lignes_fichier_csv(FILE *f){ 				// calcule le nombre de lignes d'un CSV et enleve 1 (pour ne pas compter l'en-tête avec les noms de colonne
	fseek(f,0,SEEK_SET);
	char lettre = fgetc(f);
	int nb = 1;

	while( lettre != EOF) {
		lettre = fgetc(f);
		if(lettre == '\n') nb++;
	}

	fseek(f,0,SEEK_SET);								//Deplacement dans f de 0 caracteres a partir du debut (remet le fichier au debut)
	return nb - 1;
}




void remplir_tableau(FILE *doc, int taille, vecteur *tab){// rempli un tableau de fiche_client (FC) avec les données d'un fichier CSV
	int i=0;

	char line[longueur_max_ligne];					//tableau qui stockera chaque ligne en chaîne de caractère
	char *nb_temp;											//variable qui gardera les char entre chaque ";" du CSV

	while(fgetc(doc) != '\n') fgetc(doc); 			//saute la ligne d'en-têtes

	while (fgets(line, longueur_max_ligne, doc) != NULL){ 	//tant que la ligne n'est pas vide

		nb_temp = strtok(line, ";");						// stocke dans nb_temp les caractère jusqu'au prochain caractère séparateur
		tab[i].donnees[0] = atof(nb_temp);						//transforme la chaine de caractère en int et la stocke dans le tableau tab[i].donnees;

        for(int z = 1;z < taille-1; z++){     //stocke le reste de la ligne dans tab[i].donnees
          nb_temp = strtok(NULL, ";");
          tab[i].donnees[z] = atof(nb_temp);
        }

        nb_temp = strtok(NULL,";");
        tab[i].categorie =atoi(nb_temp);        //stocke la derniere valeur de la ligne dans tab[i].categorie

        i++;
	}
}




int main(){

	FILE *fichier = NULL;
	fichier = fopen("heart_failure_clinical_records_dataset.csv","r");//ouverture du fichier
    int nb_colonnes = 13;
    int nb_lignes=nb_lignes_fichier_csv(fichier);

	vecteur *tableau=malloc(sizeof(vecteur)*nb_lignes-1);//allocation du tableau de vecteurs

    for(int y=0;y<nb_lignes-1;y++){//allocation de chaque vecteur dans le tableau
        vecteur *v=malloc(sizeof(*v));
        v->donnees=malloc(sizeof(float)*nb_colonnes);
        v->taille=0;
        v->categorie=0;
        tableau[y]=*v;
    }

    remplir_tableau(fichier,nb_colonnes,tableau);//on rempli le tableau


    //affichage du tableau pour verifier
	for(int y=0;y<nb_lignes-1;y++){
        printf("\n%d\t",y);
        for(int z=0;z<nb_colonnes-1;z++){
            printf("%f |  ",tableau[y].donnees[z]);
        }
        printf("categorie:%d",tableau[y].categorie);
    }

	return 0;
}
