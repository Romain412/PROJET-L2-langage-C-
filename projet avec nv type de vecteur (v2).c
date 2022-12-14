#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


struct vecteur{
    int *donnees;
    int taille;
    int cate;
};typedef struct vecteur vecteur;


int alea_tmp(){ //FONCTION PROVISOIRE POUR AVOIR DES VECTEURS ALEATOIRES
    //srand(TIME(NULL));
    int val=rand()%10;
    return val;
}

vecteur *creation_vecteur(int taille_vecteur,int categorie,int valeurs[]){//LA FONCTION MARCHE
    vecteur *v=malloc(sizeof(*v));
    v->donnees=malloc(sizeof(int)*taille_vecteur);
    v->taille=taille_vecteur;
    v->cate=categorie;
    for(int i=0;i<v->taille;i++){
        v->donnees[i]=valeurs[i]+alea_tmp();
    }
    return v;
}


void *creation_tab_vec(vecteur *tab_vec,int taille_tab_vec,int taille_vec,int categorie, int valeurs[]){//LA FONCTION MARCHE
    for(int i=0;i<taille_tab_vec;i++){
        tab_vec[i]=*creation_vecteur(taille_vec,categorie,valeurs);
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
		tab_categ[vec.cate]++;//+1 pour la categorie du vecteur selectionne a ce tour
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
    //DECLARATIONS DES VARIABLES, TABLEAUX...
    int K=12;
    int taille_vec=3;//nombre de dimensions des vecteurs (arbitraire pour l'instant)
    int categorie=2;//categorie de chaque vecteur (arbitraire pour l'instant)
    int donnees_test[]={1,3,8};//valeurs utilisees pour tester les fonctions (arbitraires pour l'instant)
    int donnees_point[]={4,3,18};//valeurs de notre vecteur (arbitraires pour l'instant)
    int taille_tab=3;//nombre de vecteurs hormi le notre (arbitraire pour l'instant)
    vecteur Point={donnees_point,taille_vec,categorie};//vecteur de categorie inconnue
    vecteur v_test={donnees_test,taille_vec,categorie};//vecteurs arbitraires utilises pour tester les fonctions

    vecteur *tab_vec=malloc(sizeof(vecteur)*taille_tab);//tableau de tous les vecteurs

    vecteur *tab_vois=malloc(sizeof(vecteur)*taille_tab);//tableau qui va contenir tous les vecteurs dans le cercle (voisins)
    int nvlle_taille_vois=taille_tab;//nouvelle taille du tableau des vecteurs voisins
    int *p_nv_taille=&nvlle_taille_vois;

    int nb_cate=3;//nombre de categories (arbitraire pour l'instant)
    int *tab_cate=calloc(nb_cate,sizeof(*tab_cate));//tableau qui va contenir le nombre de vecteurs de chaque categorie



    //TEST ET UTILISATION DES FONCTIONS

    creation_tab_vec(tab_vec,taille_tab,taille_vec,categorie,donnees_test);//verif fonction creation_tab_vec
    /*printf("\ndistance=%f",distance(v_test,Point));//verif fonction distance
    printf("\ndans cercle=%d",dans_cercle(v_test,Point,K));//verif fonction dans_cercle
    */

    printf("On dispose de %d vecteurs\n",taille_tab);

    voisins(tab_vois,tab_vec,taille_tab,Point,K,&nvlle_taille_vois);//verif fonction voisins
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
