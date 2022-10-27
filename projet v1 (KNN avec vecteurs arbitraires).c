#include <stdio.h>


struct vecteur{
	int val1;
	int val2;
	int val3;
	int cate;//le nom de la categorie est remplacé par un int
};typedef struct vecteur vecteur;


vecteur init_vecteur(val1,val2,val3,cate){
	vecteur vec={val1,val2,val3,cate};
	return vec;
}


vecteur creation_tab(*tab){//creation du tableau de vecteurs (points)
	int val1,val2,val3,cate;
	for(int i=0;i<taille;i++){
		scanf("%d",val1);// remplacer les scanf par des fscanf pour plus de rapidite
		scanf("%d",val2);
		scanf("%d",val3);
		scanf("%d",cate);
		tab[i]=init_vecteur(val1,val2,val3,cate);
	}
	return tab;
}


int distance(vecteur vec1, vecteur vec2){//calcule la distance euclidienne entre 2 vecteurs
	int dist;
	dist=sqrt(pow((vec1.val1-vec2.val1),2)+pow((vec1.val3-vec2.val3),2)+pow((vec1.val3-vec2.val3),2));
	return dist;
}


int dans_cercle(vecteur vec){
	if (distance(point,vec)<=K) return 1;
	return 0;
}

void selec_vec(vecteur *tab_knn[] vecteur *tab[], int taille){//rempli le tableau knn qui est la liste des vecteurs compris dans le cercle 
	for(int i=0;i<taille;i++){
		if (dans_cercle(tab[i])==1){
			knn[i]=tab[i];
		}
	}
}


int compteur_cate(int *tab_knn[], int taille_tab_knn, int *cpt[]){//pour chaque knn on regarde a quel categorie il appartient
	for(int i=0;i<taille_tab_knn;i++){
		if (tab_knn[i].cate==1) cpt[0]++;//ici on a mis arbitrairement 2 categories différentes (pour l'instant)
		if (tab_knn[i].cate==2) cpt[1]++; 
	}
	return cpt;
}


int point_cate(int *cpt, int nb_cate,){//retourne la categorie du point de categorie inconnue
	int maxi=cpt[0];
	for(int i=0;i<nb_cate;i++){
		if (tab[i]>tab[maxi]){
			maxi=i;
		}
	}
	return maxi+1;//on met plus 1 car les indices commencent a 0
}





int main(){
	vecteur point=init_vecteur(val1,val2,val3,cate);//point dont on veut connaitre la catégorie
	int K=x;//x valeur arbitraire pour l'instant
	int taille=y// nombre de vecteurs qu'on a (valeur arbitraire pour l'instant)
	vecteur *tab[]=malloc(sizeof(vecteur)*taille);//declaration tableau de vecteurs
	
	vecteur *tab_knn[]=malloc(sizeof(vecteur);//tableau des vecteurs contenus dans le cercle de diametre K

	
	int nb_cate;//nombre de categories de vecteur (arbitraire pour l'instant)
	
	int *cpt[nb_cate];
	
	return 0;
}

