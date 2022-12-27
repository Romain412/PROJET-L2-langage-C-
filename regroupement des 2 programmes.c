#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longueur_max_ligne = 2000;

struct vecteur{
	float *donnees;
	int taille;
	int categorie;
};typedef struct vecteur vecteur;

int nb_lignes_fichier_csv(FILE *f){ 				// calcule le nombre de lignes d'un CSV et enleve 1 (pour ne pas compter l'en-t�te avec les noms de colonne
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




void remplir_tableau(FILE *doc, int taille, vecteur *tab){// rempli un tableau de fiche_client (FC) avec les donn�es d'un fichier CSV
	int i=0;

	char line[longueur_max_ligne];					//tableau qui stockera chaque ligne en cha�ne de caract�re
	char *nb_temp;											//variable qui gardera les char entre chaque ";" du CSV

	while(fgetc(doc) != '\n') fgetc(doc); 			//saute la ligne d'en-t�tes

	while (fgets(line, longueur_max_ligne, doc) != NULL){ 	//tant que la ligne n'est pas vide

		nb_temp = strtok(line, ";");						// stocke dans nb_temp les caract�re jusqu'au prochain caract�re s�parateur
		tab[i].donnees[0] = atof(nb_temp);						//transforme la chaine de caract�re en int et la stocke dans le tableau tab[i].donnees;

        for(int z = 1;z < taille-1; z++){     //stocke le reste de la ligne dans tab[i].donnees
          nb_temp = strtok(NULL, ";");
          tab[i].donnees[z] = atof(nb_temp);
        }

        nb_temp = strtok(NULL,";");
        tab[i].categorie =atoi(nb_temp);        //stocke la derniere valeur de la ligne dans tab[i].categorie

        i++;
	}
}

vecteur *creation_vecteur(int taille_vec){//LA FONCTION MARCHE
    vecteur *v=malloc(sizeof(*v));
    v->donnees=malloc(sizeof(float)*taille_vec);
    v->taille=taille_vec;
    v->categorie=0;
    return v;
}

void *creation_tab_vec(vecteur *tab_vec,int nb_lignes,int taille_vec){//LA FONCTION MARCHE
    for(int i=0;i<nb_lignes;i++){
        tab_vec[i]=*creation_vecteur(taille_vec);
    }
}


float distance(vecteur vec1,vecteur vec2){//LA FONCTION MARCHE
    float dist=0;
    for (int i=0;i<vec1.taille;i++){
        dist+=pow((vec1.donnees[i]-vec2.donnees[i]),2);
    }
    dist=sqrt(dist);
    return dist;
}



int dans_cercle(vecteur vec,vecteur Point,int K){//LA FONCTION MARCHE
	if (distance(Point,vec)<=K) return 1;
	return 0;
}


void voisins(vecteur *tab_vois, vecteur *tab_vec, int taille_tab_vec, vecteur Point, int K,int *p_nv_taille){//LA FONCTION MARCHE
    int j=0;
    for (int i=0;i<taille_tab_vec;i++){
        if(dans_cercle(tab_vec[i],Point,K)==1){
            tab_vois[j]=tab_vec[i];
            j++;
        }
    }
    *p_nv_taille=j;
}






void compteur_cate(vecteur *tab_vois, int *tab_categ, int taille){//NORMALEMENT LA FONCTION MARCHE
	vecteur vec;
	for (int i=0;i<taille;i++){
		vec=tab_vois[i];
		tab_categ[vec.categorie]++;//+1 pour la categorie du vecteur selectionne a ce tour
	}						  // ex: si vec.cate=1 -> tab_categ[1]++,    si vec.cate=0 -> tab_categ[0]++
}




int maxi(int tab_categ[], int taille){//LA FONCTION MARCHE
    int cate_max=0;
    for(int i=0;i<taille;i++){
        if (tab_categ[i]>tab_categ[cate_max]){
            cate_max=i;
        }
    }
    return cate_max;
}





int main(){

    int K=120000;

	FILE *fichier = NULL;
	fichier = fopen("heart_failure_clinical_records_dataset.csv","r");//ouverture du fichier
    int nb_colonnes = 13;
    int nb_lignes=nb_lignes_fichier_csv(fichier);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vecteur *tableau=malloc(sizeof(vecteur)*nb_lignes-1);//allocation du tableau de vecteurs

    creation_tab_vec(tableau,nb_lignes,nb_colonnes);
    remplir_tableau(fichier,nb_colonnes,tableau);

    //affichage du tableau pour verifier
	for(int y=0;y<nb_lignes-1;y++){
        printf("\n%d\t",y);
        for(int z=0;z<nb_colonnes-1;z++){
            printf("%f |  ",tableau[y].donnees[z]);
        }
        printf("categorie:%d",tableau[y].categorie);
    }
    printf("\n\n\n\n\n\n");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int donnees_point[]={44,0,471,1,53,0,499000,1,130,0,1,245};
    vecteur Point={donnees_point,nb_colonnes,-1};//vecteur de categorie inconnue

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    vecteur *tab_vois=malloc(sizeof(vecteur)*nb_lignes);//tableau qui va contenir tous les vecteurs dans le cercle (voisins)
    int nvlle_taille_vois=nb_lignes;//nouvelle taille du tableau des vecteurs voisins
    int *p_nv_taille=&nvlle_taille_vois;

    int nb_cate=2;
    int *tab_cate=calloc(nb_cate,sizeof(*tab_cate));//tableau qui va contenir le nombre de vecteurs de chaque categorie

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    printf("On dispose de %d vecteurs\n",nb_lignes-2);

    voisins(tab_vois,tableau,nb_lignes,Point,K,&nvlle_taille_vois);//verif fonction voisins
    //printf("nvlle taille=%d\n",nvlle_taille_vois);//verif si la taille se met bien a jour

    /*test pour verifier qu'on a les bons voisins->CA MARCHE
    for(int i=0;i<nvlle_taille_vois;i++){//pour chaque vecteur
        for(int j=0;j<taille_vec;j++){//pour chaque valeur dans ce vecteur
            printf("%d\t",tab_vois[i].donnees[j]);
        }
        printf("\tdistance=%f",distance(Point,tab_vec[i]));
        printf("\n");
    }
    */


    printf("On a %d vecteurs voisins (a l'interieur du cercle)\n\n",nvlle_taille_vois);

    compteur_cate(tab_vois,tab_cate,nvlle_taille_vois);


    for (int i=0;i<nb_cate;i++){
        printf("Il y a %d vecteurs de categorie %d\n",tab_cate[i],i);
    }
    printf("\nNOTRE VECTEUR EST DONC DE CATEGORIE %d\n",maxi(tab_cate,nb_cate));



	return 0;
}
