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



void compteur_cate(vecteur *tab_vois, int *tab_categ, int taille){//FONCTION A TESTER
	vecteur vec;
	for (int i=0;i<taille;i++){
		vec=tab_vois[i];
		tab_categ[vec.cate]++;//+1 pour la categorie du vecteur selectionne a ce tour 
	}						  // ex: si vec.cate=1 -> tab_categ[1]++,    si vec.cate=2 -> tab_categ[2]++
}


int main(){
    //DECLARATIONS DES VARIABLES, TABLEAUX...
    int K=12;
    int taille_vec=3;
    int categorie=1;
    int donnees_exemple[]={1,3,8};
    int donnees_point[]={4,3,18};
    int taille_tab=3;
    vecteur Point={donnees_point,taille_vec,categorie};
    vecteur v_test={donnees_exemple,taille_vec,categorie};

    vecteur *tab_vec=malloc(sizeof(vecteur)*taille_tab);

    vecteur *tab_vois=malloc(sizeof(vecteur)*taille_tab);
    int nvlle_taille_vois=taille_tab;
    int *p_nv_taille=&nvlle_taille_vois;
    
    int nb_cate=2;//pour l'instant on a que 2 categories differentes
    int *tab_cate=calloc(nb_cate,sizeof(*tab_cate));



    //TEST ET UTILISATION DES FONCTIONS
    
    creation_tab_vec(tab_vec,taille_tab,taille_vec,categorie,donnees_exemple);//verif fonction creation_tab_vec
    /*printf("\ndistance=%f",distance(v_test,Point));//verif fonction distance
    printf("\ndans cercle=%d",dans_cercle(v_test,Point,K));//verif fonction dans_cercle
    */

    voisins(tab_vois,tab_vec,taille_tab,Point,K,&nvlle_taille_vois);//verif fonction voisins
    printf("nvlle taille=%d\n",nvlle_taille_vois);//verif si la taille se met bien a jour
    
    /*test pour verifier qu'on a les bons voisins->CA MARCHE
    for(int i=0;i<nvlle_taille_vois;i++){//pour chaque vecteur
        for(int j=0;j<taille_vec;j++){//pour chaque valeur dans ce vecteur
            printf("%d\t",tab_vois[i].donnees[j]);
        }
        printf("\tdistance=%f",distance(Point,tab_vec[i]));
        printf("\n");
    }
    */
    
    

    return 0;
}
