#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longueur_max_ligne = 50;

typedef struct fiche_client{
	int age; // age de la personne
	int revenu; // revenu mensuel
	int sante; // etat de santé dans l'intervalle ]0-100]
	int pret; // 1=oui / 0 = non
	int categorie;
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
	int i=0, taille = nb_lignes_fichier_csv(doc);

	FC *tab = malloc(sizeof(FC)*taille);

	FC temp;
	char line[longueur_max_ligne];	//tableau qui stockera chaque ligne en chaîne de caractère
	char *nb_temp;	//variable qui gardera les char entre chaque ";" du CSV
	
	while(fgetc(doc) != '\n') fgetc(doc); 	//saute la ligne d'en-têtes

	while (fgets(line, longueur_max_ligne, doc) != NULL){ 	//manque la fouille du csv et mettre la valeur dans nb_temp

		nb_temp = strtok(line, ";"); // stock dans nb_temp les caractère jusqu'au prochain caractère séparateur
		temp.age = atoi(nb_temp);		//transforme la chaine de caractère en int et la stocke dans la variable temp;
		
		nb_temp = strtok(NULL, ";");
		temp.revenu = atoi(nb_temp);
		
		nb_temp = strtok(NULL, ";");
		temp.sante = atoi(nb_temp);
		
		nb_temp = strtok(NULL, ";");
		temp.pret = atoi(nb_temp);
		
		nb_temp = strtok(NULL, ";");
		temp.categorie = atoi(nb_temp);

		tab[i] = temp;
		i++;
	}

	return tab;
}


int ajouter_valeur_tableau(FC *tab,int taille, FC val){
	tab = realloc(tab, sizeof(FC)*(taille + 1));
	tab[taille] = val;
	return taille++;
}

	int main(){

	FILE *fichier = NULL;
	fichier = fopen("testCSV.csv","r");

	FC*tab = remplir_tableau(fichier);

	for(int i=0; i<(nb_lignes_fichier_csv(fichier));i++){

		printf("%d ; %d ; %d ; %d ; %d \n",tab[i].age,tab[i].revenu,tab[i].sante,tab[i].pret,tab[i].categorie);

	}

return 0;
}
