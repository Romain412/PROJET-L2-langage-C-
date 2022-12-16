# -*- coding: utf-8 -*-
"""
Created on Tue Dec 13 09:29:06 2022

@author: Romain
"""

import csv




nom_fichier="projet v1 (KNN avec vecteurs arbitraires).c"
fichier =open(nom_fichier,"r")
chaine=fichier.read()
fichier.close()

#chaine = ['b', '\n', ' ', 'f', 'o', 'r', '\t', '\t', '\n', 'e', 'l', 's', 'e',
#   '{', '\n', 'i', 'n', 't',' ', 'n', 'o', 'm', 'b', 'r', 'e', ' ', '=', '4', ',', 'n', '2', '=','4', 'EOF']  # contient un programme C sous forme de tableau de caracteres
#chaine = ''.join(chaine)
## on coupe le fichier pour avoir chaque ligne separee
chaine = chaine.split('\n')





nb_boucles_for=0
nb_boucles_while=0
nb_condi_if=0
nb_condi_else=0
nb_variables=0

liste_types=['char','int','float','double','unsigned','short','long']


def detect_for(ligne):#retourne le nombre de for dans une ligne
    res=0
    if 'for' in ligne:#si il y a le mot for dans la ligne
        ind=ligne.index('for')#on recupere l'indice de sa premiere lettre
        if ligne[ind+3] in [' ','\t','(']:#on verifie qu'il s'agit du mot 'for' isole et pas d'un nom de variable
            res=1
    return res


def detect_while(ligne):#retourne le nombre de while dans une ligne
    res=0
    if 'while' in ligne:
        ind=ligne.index('while')
        if ligne[ind+5] in [' ','\t','(']:
            res=1
    return res


def detect_if(chaine):#retourne le nombre de if dans une ligne
    res=0
    if 'if' in ligne:
        ind=ligne.index('if')
        if ligne[ind+2] in [' ','\t','(']:
            res=1
    return res



def detect_else(chaine):#retourne le nombre de else dans une ligne
    res=0
    if 'else' in ligne:
        ind=ligne.index('else')
        if ligne[ind+4] in [' ','\t','{']:
            res=1
    return res



""" LA FONCTION detect_var N'EST PAS AU POINT (ELLE COMPTE LES FONCTIONS ET LES PARAMETRES
DE FONCTIONS EN TANT QUE VARIABLES)
    
LES AUTRES FONCTIONS MARCHENT """

def detect_var(chaine):#retourne le nombre de variables dans une ligne
    res=0
    for i in liste_types:#on regarde pour chaque type si il est present
        if i in chaine:
            ind=ligne.index(i)#on recupere l'indice auquel se trouve le mot
            
            if ligne[ind+len(i)] in [' ','\t']:#si le caractere d'apres est dans cette liste
                if '{' not in ligne[ind+len(i)+1:]:#si on n'a pas '{' dans la ligne alors ce n'est pas une fonction
                    res+=1
                    if ',' in ligne[ind+len(i):]:#si il y a une virgule quelque part apres
                        res+=1
                        
        #if 'struct' in chaine:#cas ou on cree nous meme un type
            
                    
    return res
            

        

for ligne in chaine:
    ind=None
    if len(ligne)>1:#problemes quand les lignes ont 0 ou 1 element
        while ligne[0]==' ' or ligne[0]=='\t' :#on enleve les espaces qu'il peut y avoir au debut
            ligne=ligne[1:]
        
        nb_boucles_for+=detect_for(ligne)
        
        nb_boucles_while+=detect_while(ligne)
            
        nb_condi_if+=detect_if(ligne)
        
        nb_condi_else+=detect_else(ligne)
        
        nb_variables+=detect_var(ligne)
         
            
         

#Affichage
print("\nFICHIER:",nom_fichier,'\n')
print("Nombre de boucles for =",nb_boucles_for)
print("Nombre de boucles while =",nb_boucles_while)
print("Nombre de conditions if =",nb_condi_if)
print("Nombre de conditions else =",nb_condi_else)
print("Nombre de variables =",nb_variables)#IL FAUT ENCORE CODER LE CAS OU ON DECLARE UN NOUVEAU TYPE DE VARIABLES (AVEC STRUCT)

donnees=str(nb_boucles_for)+';'+str(nb_boucles_while)+';'+str(nb_condi_if)+';'+str(nb_condi_else)+';'+str(nb_variables)





#enregistrement dans un fichier csv

nom_fichier='data.csv'

with open(nom_fichier, 'w', newline='') as fichier_csv:
    ecrivain = csv.writer(fichier_csv)

    #On ecrit les en-tetes
    ecrivain.writerow(['Nombre boucles for;Nombre boucles while;Nombre conditions if;Nombre conditions else;Nombre variables'])

    #On ecrit les donnees
    ecrivain.writerow([donnees])




