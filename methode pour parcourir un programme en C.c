


#include <stdio.h>


int taille_fichier(FILE *f){ //RETOURNE LE NOMBRE DE CARACTERES DANS UN FICHIER
	char lettre = fgetc(f);
	int nb=1;
	while( lettre != EOF) {
		lettre = fgetc(f);
		nb++;
	}
	fseek(f,0,SEEK_SET);//Deplacement dans f de 0 caracteres a partir du debut (pour pouvoir parcourir le fichier plusieurs fois)
	return nb;
}


int main(int argc, char **argv)
{
    FILE *fichier=NULL;//creation du pointeur de fichier
    fichier=fopen("test2.c","r");//ouverture du fichier dans lequel on lit

    //Remplissage d'un tableau contenant tous les caracteres du fichier qu'on est en train de lire
    char texte[taille_fichier(fichier)];
    char lettre=fgetc(fichier);
    int i=0;
    while (lettre!=EOF){
        texte[i]=lettre;
        lettre=fgetc(fichier);
        printf("%c",texte[i]);
        i++;
    }
    fclose(fichier);
	return 0;



}

