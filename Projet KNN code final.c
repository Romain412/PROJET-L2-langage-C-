#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



const int longueur_max_ligne = 2000;



struct vecteur{
	float *donnees;
	int taille;
	int categorie;
};typedef struct vecteur vecteur;



// Calcule le nombre de lignes d'un CSV et enleve 1 (pour ne pas compter l'en-tête avec les noms de colonne)
int nb_lignes_fichier_csv(FILE *f){
	fseek(f,0,SEEK_SET);
	char lettre = fgetc(f);
	int nb = 1;

	while( lettre != EOF) {
		lettre = fgetc(f);
		if(lettre == '\n') nb++;
	}

	fseek(f,0,SEEK_SET);	// Deplacement dans f de 0 caracteres a partir du debut (remet le curseur au debut du fichier)
	return nb - 1;
}



// Donne le nombre de colonnes
int nb_colonnes_fichier_csv(FILE *f){
    fseek(f,0,SEEK_SET);
    char lettre = fgetc(f);
    int nb = 1;

    while( lettre != '\n') {
        lettre = fgetc(f);
        if(lettre == ';') nb++;
    }

    fseek(f,0,SEEK_SET);
    return nb;
}



// Remplit un tableau de vecteurs avec les données d'un fichier CSV
void remplir_tableau(FILE *doc, int taille, vecteur *tab){
	int i=0;

	char line[longueur_max_ligne];					// Tableau qui stockera chaque ligne en chaîne de caractère
	char *nb_temp;							// Variable qui gardera les char entre chaque ";" du CSV

	while(fgetc(doc) != '\n') fgetc(doc); 			// Saute la ligne d'en-têtes

	while (fgets(line, longueur_max_ligne, doc) != NULL){ 	// Tant que la ligne n'est pas vide

		nb_temp = strtok(line, ";");				// Stocke dans nb_temp les caractère jusqu'au prochain caractère séparateur
		tab[i].donnees[0] = atof(nb_temp);			// Transforme la chaine de caractère en int et la stocke dans le tableau tab[i].donnees;

        for(int z = 1;z < taille-1; z++){     // Stocke le reste de la ligne dans tab[i].donnees
          nb_temp = strtok(NULL, ";");
          tab[i].donnees[z] = atof(nb_temp);
        }

        nb_temp = strtok(NULL,";");
        tab[i].categorie =atoi(nb_temp);        // Stocke la derniere valeur de la ligne dans tab[i].categorie

        i++;
	}
}




vecteur *creation_vecteur(int taille_vec){
    vecteur *v=malloc(sizeof(*v));
    v->donnees=malloc(sizeof(float)*taille_vec-1);
    v->taille=taille_vec-1;
    v->categorie=0;
    return v;
}


// Cree un tableau de vecteurs
void *creation_tab_vec(vecteur *tab_vec,int nb_lignes,int taille_vec){
    for(int i=0;i<nb_lignes;i++){
        tab_vec[i]=*creation_vecteur(taille_vec-1);
    }
}

// Calcule la distance euclidienne entre 2 vecteurs
float distance(vecteur vec1,vecteur vec2){
    float dist=0,tmp;
    for (int i=0;i<vec1.taille;i++){
        tmp=powf((vec1.donnees[i]-vec2.donnees[i]),2);
        dist=dist+tmp;
    }
    dist=sqrt(dist);
    return dist;
}


// Retourne 1 si le vecteur est dans le cercle, 0 sinon
int dans_cercle(vecteur vec,vecteur Point,int K){
	if (distance(Point,vec)<=K) return 1;
	return 0;
}



// Remplit le tableau des vecteurs voisins et qui nous donne sa nouvelle taille
void voisins(vecteur *tab_vois, vecteur *tab_vec, int taille_tab_vec, vecteur Point, int K,int *p_nv_taille){
    int j=0;
    for (int i=0;i<taille_tab_vec;i++){
        if(dans_cercle(tab_vec[i],Point,K)==1){
            tab_vois[j]=tab_vec[i];
            j++;
        }
    }
    *p_nv_taille=j-1;
}





// Compte le nombre de vecteurs par categorie et rempli le tableau associe
void compteur_cate(vecteur *tab_vois, int *tab_categ, int taille){
	vecteur vec;
	for (int i=0;i<taille;i++){
		vec=tab_vois[i];
		tab_categ[vec.categorie]++;	// +1 pour la categorie du vecteur selectionne a ce tour
	}						  // ex: si vec.cate=1 -> tab_categ[1]++,    si vec.cate=0 -> tab_categ[0]++
}



// Retourne la categorie la plus presente dans le tableau des categories
int maxi(int tab_categ[], int taille){
    int cate_max=0;
    for(int i=0;i<taille;i++){
        if (tab_categ[i]>tab_categ[cate_max]){
            cate_max=i;
        }
    }
    return cate_max;
}






int main(){

    int K=250000;
    int nb_cate=2;


	FILE *fichier = NULL;
	fichier = fopen("heart_failure_clinical_records_dataset.csv","r");	// Ouverture du fichier
    int nb_colonnes = nb_colonnes_fichier_csv(fichier);
    int nb_lignes=nb_lignes_fichier_csv(fichier);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	vecteur *tableau=malloc(sizeof(vecteur)*nb_lignes-1);	// Allocation du tableau de vecteurs

    creation_tab_vec(tableau,nb_lignes,nb_colonnes);
    remplir_tableau(fichier,nb_colonnes,tableau);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int donnees_point[]={18,0,150,1,60,0,250000,1,140,0,1,10};	// Ce sont des donnees arbitraires, il est parfaitement possible de les remplacer par celles que vous voulez
    vecteur Point={donnees_point,nb_colonnes-1,-1};	// Vecteur de categorie inconnue contenant les donnees de la ligne precedente

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    vecteur *tab_vois=malloc(sizeof(vecteur)*nb_lignes);	// Tableau qui va contenir tous les vecteurs dans le cercle (voisins)
    int nvlle_taille_vois=nb_lignes;	// Nouvelle taille du tableau des vecteurs voisins
    int *p_nv_taille=&nvlle_taille_vois;

    int *tab_cate=calloc(nb_cate,sizeof(int));	// Tableau qui va contenir le nombre de vecteurs de chaque categorie

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    printf("On dispose de %d vecteurs dans le fichier CSV\n",nb_lignes-1);

    voisins(tab_vois,tableau,nb_lignes,Point,K,&nvlle_taille_vois);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int menu;
    printf("\n\nSelectionner l'action a executer puis tapez Entree: \n1 - Afficher tout les vecteurs\n2 - Afficher les vecteurs voisins (= ceux presents dans le cercle)\nAutre chiffre - Continuer l'execution du programme \n\nVotre choix: ");
    scanf("%d",&menu);

    if (menu==1){
        // Affichage du tableau pour verifier
        for(int y=0;y<nb_lignes-1;y++){
            printf("\n%d\t",y);
            for(int z=0;z<nb_colonnes-1;z++){
                printf("%f |  ",tableau[y].donnees[z]);
            }
            printf("categorie:%d",tableau[y].categorie);
        }
        printf("\n\n\n\n\n\n");
    }

    if (menu==2){
        // Affichage des voisins
        for(int i=0;i<nvlle_taille_vois;i++){	// Pour chaque vecteur
                printf("\n%d\t",i);
            for(int j=0;j<nb_colonnes-1;j++){// Pour chaque valeur dans ce vecteur
                printf("%f | ",tab_vois[i].donnees[j]);
            }
            printf("categorie: %d\t distance: %f ",tab_vois[i].categorie,distance(tab_vois[i],Point));
        }
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    printf("\n\nOn a %d vecteurs voisins (a l'interieur du cercle)\n\n",nvlle_taille_vois);

    compteur_cate(tab_vois,tab_cate,nvlle_taille_vois);


    for (int i=0;i<nb_cate;i++){
        printf("Il y a %d vecteurs de categorie %d\n",tab_cate[i],i);
    }
    printf("\nNOTRE VECTEUR EST DONC DE CATEGORIE %d\n",maxi(tab_cate,nb_cate));

    printf("\n\n\n(La categorie 0 correspond a la survie apres arret cardiaque, la categorie 1 correspond au deces apres arret cardiaque)\n\n");

	return 0;
}

