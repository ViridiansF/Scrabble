#include "../lib/libgraphique.h"
#include<stdio.h>
#include<string.h>

#define LARGEUR_ECRAN_TITRE 1000  
#define HAUTEUR_ECRAN_TITRE 600   

int main(int argc, char *argv[]){
Point p1 ={0,0};
Point p2;
ouvrir_fenetre(LARGEUR_ECRAN_TITRE,HAUTEUR_ECRAN_TITRE);
afficher_image("../Images/ecrantitre.bmp",p1);
actualiser();

p2= attendre_clic();
if ((p2.y>325) && (p2.y<430))
		{
		if ((p2.x>100) && (p2.x<125))
			printf("Bonne chance"); // Mettre un return start; pour commencer la partie.
		else if ((p2.x>655) && (p2.x<880))
			fermer_fenetre();
		}

actualiser();
attendre_clic();  //fin
fermer_fenetre();
return 0;
}
