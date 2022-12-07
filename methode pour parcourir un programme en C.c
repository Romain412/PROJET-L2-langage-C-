#include <stdio.h>

int taille_fichier(FILE *f){
	char lettre = fgetc(f);
	int nb=1;
	while( lettre != EOF) {
		lettre = fgetc(f);
		if(lettre=='\n') nb++;
	}
	fseek(f,0,SEEK_SET);//Deplacement dans f de 0 caracteres a partir du debut (pour pouvoir parcourir le fichier plusieurs fois)
	return nb;
}

int main(){

	FILE *fichier = NULL;
	fichier=fopen("classeur1.txt","r");
	printf("%d",taille_fichier(fichier));

	return 0;
}
