#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longueur_max_ligne = 2000;

typedef struct fiche_client{
	float *donnees;
	int taille;
	int categorie;
}FC;

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

FC *remplir_tableau(FILE *doc, int taille){ 					// rempli un tableau de fiche_client (FC) avec les données d'un fichier CSV
	int i = 0, lignes = nb_lignes_fichier_csv(doc);

	FC *tab = malloc(sizeof(FC)*lignes);

	FC temp;
  temp.taille = taille;
  temp.donnees = malloc(sizeof(float)*(taille-1));
	char line[longueur_max_ligne];					//tableau qui stockera chaque ligne en chaîne de caractère
	char *nb_temp;											//variable qui gardera les char entre chaque ";" du CSV

	while(fgetc(doc) != '\n') fgetc(doc); 			//saute la ligne d'en-têtes

	while (fgets(line, longueur_max_ligne, doc) != NULL){ 	//tant que la ligne n'est pas vide

		nb_temp = strtok(line, ";");						// stocke dans nb_temp les caractère jusqu'au prochain caractère séparateur
		temp.donnees[0] = atof(nb_temp);						//transforme la chaine de caractère en int et la stocke dans le tableau temp.donnees;

    for(int z = 1; z < taille - 1; z++){     //stocke le reste de la ligne dans temp.donnees
      nb_temp = strtok(NULL, ";");
      temp.donnees[z] = atof(nb_temp);
    }

    nb_temp = strtok(NULL,";");
    temp.categorie =atoi(nb_temp);        //stocke la derniere valeur de la ligne dans temp.categorie


    for(int j = 0; j < taille-1; j++){
		  printf("%f | ",temp.donnees[j]);
		}
    printf("\n");
    tab[i] = temp; //stocke la variable temp dans le tableau tab
		i++;
	}

	return tab;    //renvoie tab avec tout les temp étant les lignes du CSV
}


int ajouter_valeur_tableau(FC *tab,int taille, FC val){ //ajoute une valeur au tableau (augmente sa taille juste avant) et renvoie sa nouvelle taille
	tab = realloc(tab, sizeof(FC)*(taille + 1));
	tab[taille] = val;
	return taille++;
}

int main(){

	FILE *fichier = NULL;
  int nb_colonnes = 13;
	fichier = fopen("heart_failure_clinical_records_dataset.csv","r");

	FC*tab = remplir_tableau(fichier, nb_colonnes);

	printf("\n\nnikzebi\n\n");

	for(int i = 0; i < nb_lignes_fichier_csv(fichier); i++){

		for(int j = 0; j < nb_colonnes-1; j++){
		  printf("%f | ",tab[i].donnees[j]);
		}
    printf("categorie : %d",tab[i].categorie);
    printf("\n");

	}

	return 0;
}
