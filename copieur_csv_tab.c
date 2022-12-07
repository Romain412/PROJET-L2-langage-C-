#include <stdio.h>
#include <stdlib.h>

typedef struct fiche_client{
	int age; // ya vrmnt besoin de commenter là ?
	int revenu; // revenu mensuel
	float sante; // etat de santé E ]0-1]
	int pret; // 1=oui / 0 = non
	
}FC;

int taille_fichier(FILE *f){
	fseek(f,0,SEEK_SET);
	char lettre = fgetc(f);
	int nb=1;
	while( lettre != EOF) {
		lettre = fgetc(f);
		if(lettre=='\n') nb++;
	}
	fseek(f,0,SEEK_SET);	//Deplacement dans f de 0 caracteres a partir du debut (pour pouvoir parcourir le fichier plusieurs fois)
	return nb;
}

FC *creation_tab(int taille){
	FC *tab = (FC*) malloc(sizeof(FC)*taille);
	return tab;
}

void CSV_INSERT(FILE *F, FC *tab, int taille){
	fseek(F,0,SEEK_SET);
	int i = 0, ligne = 0;
	FC fiche;
	
	while(ligne<taille){
		
		fiche.age = fgetc(F);
		fiche.revenu = fgetc(F);
		fiche.sante = fgetc(F);
		fiche.pret = fgetc(F);
		ligne++;
		tab[i++] = fiche;
	}
	
	
	fseek(F,0,SEEK_SET);
}

int main(){
	
	FILE *fichier = NULL;
	//fichier = fopen("","r");
	int taille = (taille_fichier(fichier));
	FC *tableau = creation_tab(taille);
	
	CSV_INSERT(fichier,tableau,taille);
	
	return 0;
}
