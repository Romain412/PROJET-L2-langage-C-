#include <stdio.h>

int taille_fichier(FILE f){
	char l = fgetc(fichier);
	int nb=1;
	
	while( l != EOF) {
		l = fgetc(fichier);
		nb++;
	}
	return nb;
}

int main(int argc, char **argv)
{
    FILE *fichier=NULL;//creation du pointeur de fichier
    fichier=fopen("test2.c","r");//ouverture du fichier dans lequel on lit

    //on affiche les 40 premiers caracteres du fichier
    for(int i=0;i<40;i++){
    char lettre=fgetc(fichier);
    printf("%c",lettre);
    }
    fclose(fichier);//fermeture du fichier
	return 0;
}

