#include "../lib/libgraphique.h"
#include<stdio.h>
#include<string.h>

//beaucoup de define se trouivent dans la libgraphique et sont chargés avec celle-ci

#define FILEDICO ".././dictionnaire_fr_ss_accents" // chemin du fichier dico
#define SIZEDICO 318897                         // taille large du dico
#define MAXLENMOT 26                            // taille du mot max

#define TRUE 1 
#define FALSE 0

typedef struct{
	char lettre;			//La lettre
	int points;				//Valeur en points
	char chemin[19];		//Chemin de l'image
}Lettre;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   
//	PROTOTYPES
//                                                                                                 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void defbonus(int bonus[15][15]);

int rechercheMot(Lettre plateau[15][15],char tabdico[SIZEDICO][MAXLENMOT],int c, int l,int bonus[15][15]);

void reprendre(Lettre m[7],Lettre plateau[15][15],Point p);

void defausse(Lettre m[7],Lettre tab_pioche[100]);

Lettre pioche(Lettre tab_pioche[100],int scoreJ1,int scoreJ2);

void afficher_main(Lettre m[7]);

int chargeDico(char *filedico, char tabdico[SIZEDICO][MAXLENMOT]);

int verifMot(char tabdico[SIZEDICO][MAXLENMOT],char mot[MAXLENMOT]);

void deplacementjeton(Lettre m[7],Lettre plateau[15][15],Point p,Lettre tab_pioche[27],Point pinf);

int fin (int scoreJ1, int scoreJ2, int abandon);

void Ecrantitre(void);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   
//	MAIN
//                                                                                                 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(void)
	{
		
//definitions

	int nbmots,i,j,k,t=1,w=0,scoreJ1=0,scoreJ2=0,pointsTour=0,l,c,bonus[15][15]={{0}};
    char tabdico[SIZEDICO][MAXLENMOT],sJ1[3],sJ2[3],stemp[3]; // moche, mais simple
    Point p ={0,0},pinf={610,150},psc1={650,50},psc2={650,100},psct={475,640};
   
	defbonus(bonus);

    Lettre la ={'a',1,"../Images/a.bmp"};
	Lettre lb ={'b',3,"../Images/b.bmp"};
	Lettre lc ={'c',3,"../Images/c.bmp"};
	Lettre ld ={'d',2,"../Images/d.bmp"};
	Lettre le ={'e',1,"../Images/e.bmp"};
	Lettre lf ={'f',4,"../Images/f.bmp"};
	Lettre lg ={'g',2,"../Images/g.bmp"};
	Lettre lh ={'h',4,"../Images/h.bmp"};
	Lettre li ={'i',1,"../Images/i.bmp"};
	Lettre lj ={'j',8,"../Images/j.bmp"};
	Lettre lk ={'k',10,"../Images/k.bmp"};
	Lettre ll ={'l',1,"../Images/l.bmp"};
	Lettre lm ={'m',2,"../Images/m.bmp"};  
	Lettre ln ={'n',1,"../Images/n.bmp"};
	Lettre lo ={'o',1,"../Images/o.bmp"};
	Lettre lp ={'p',3,"../Images/p.bmp"};
	Lettre lq ={'q',8,"../Images/q.bmp"};
	Lettre lr ={'r',1,"../Images/r.bmp"};
	Lettre ls ={'s',1,"../Images/s.bmp"};
	Lettre lt ={'t',1,"../Images/t.bmp"};
	Lettre lu ={'u',1,"../Images/u.bmp"};
	Lettre lv ={'v',4,"../Images/v.bmp"};
	Lettre lw ={'w',10,"../Images/w.bmp"};
	Lettre lx ={'x',10,"../Images/x.bmp"};
	Lettre ly ={'y',10,"../Images/y.bmp"};
	Lettre lz ={'z',10,"../Images/z.bmp"};
	Lettre vide={' ',0,""};
	Lettre joker={'*',0,"../Images/joker.bmp"};


	Lettre tab_pioche[100]={la,la,la,la,la,la,la,la,la,lb,lb,lc,lc,ld,ld,ld,le,le,le,le,le,le,le,le,le,le,le,le,le,le,le,lf,lf,lg,lg,lh,lh,li,li,li,li,li,li,li,li,lj,lk,ll,ll,ll,ll,ll,lm,lm,lm,ln,ln,ln,ln,ln,ln,lo,lo,lo,lo,lo,lo,lp,lp,lq,lr,lr,lr,lr,lr,lr,ls,ls,ls,ls,ls,ls,lt,lt,lt,lt,lt,lt,lu,lu,lu,lu,lu,lu,lv,lv,lw,lx,ly,lz};
    Lettre plateau[15][15];
    for (i=0;i<15;i++)
		{
		for (j=0;j<15;j++)
			plateau[i][j]=vide;
		}

	Lettre m1[7],m2[7],ma[7];				//initialisation des mains de joueurs
    
    
//chargement dico	

    nbmots = chargeDico(FILEDICO,tabdico);

    if(nbmots==0)
        {
        fprintf(stderr,"chargeDico: qqc s'est mal passé\n");
        return 1;
        }

    printf("%d mots dans le dictionnaire\n", nbmots);

	
		
		
/////////////////////////////////////////début du vrai main/////////////////////////////////////////////////////////////////////		
	
	Ecrantitre();	
		
	for (i=0;i<6;i++)		//initialisation des mains avec un joker
		m1[i]=pioche(tab_pioche,scoreJ1,scoreJ2);
	m1[6]=joker;
		
	for (i=0;i<6;i++)	
		m2[i]=pioche(tab_pioche,scoreJ1,scoreJ2);
	m2[6]=joker;
		
	ouvrir_fenetre(LARGEUR_ECRAN,HAUTEUR_ECRAN);	
	afficher_image("../Images/plateau2.bmp",p);		//création du plateau

	p.x=POSABANX;			//création de la case abandon
	p.y=POSABANY;
	dessiner_rectangle(p,110,50,blanc);
	p.x=POSABANX+5;
	p.y=POSABANY+15;
	afficher_texte("Abandonner ?", 15, p, noir);	
	
	p.x=POSDEFX;			//création de la défausse
	p.y=POSDEFY;
	dessiner_rectangle(p,100,100,blanc);
	p.x=POSDEFX+13;
	p.y=POSDEFY+15;
	afficher_texte("DEFAUSSE", 15, p, noir);

	p.x=POSCHECKX;			//création de la case check
	p.y=POSCHECKY;
	dessiner_rectangle(p,100,100,blanc);
	p.x=POSCHECKX+13;
	p.y=POSCHECKY+15;
	afficher_texte("CHECK", 15, p, noir);
	
	p.x=POSFINX;			//création de la case fin
	p.y=POSFINY;
	dessiner_rectangle(p,100,100,blanc);
	p.x=POSFINX+13;
	p.y=POSFINY+15;
	afficher_texte("FIN", 15, p, noir);
	
	afficher_texte("Score J1 : ",20,psc1,blanc);
	afficher_texte("Score J2 : ",20,psc2,blanc);
	psc1.x+=110;	
	psc2.x+=110;	

////////////////////////////////////////////////// TOUR DE JEU //////////////////////////////////////////////////////////////
		
	
	for (i=0;i<100;i++) 			//100 est le maximum de tours pouvant être joué
		{
		p.x=40;
		p.y=POSITION_MAIN;
	
		if (t==1)	//initialise "ma" qui est la main du joueur actif
			{
			for(k=0;k<7;k++)
				ma[k]=m1[k];
			dessiner_rectangle(p,700,75,noir);	
			afficher_texte(stemp,15,psct,blanc);	

			afficher_texte("TOUR DU JOUEUR 1 (cliquez pour continuer)", 20, p, blanc);
			actualiser();
			
			}
		else
			{
			for(k=0;k<7;k++)
				ma[k]=m2[k];
			dessiner_rectangle(p,700,75,noir);	
			afficher_texte("TOUR DU JOUEUR 2 (cliquez pour continuer)", 20, p, blanc);
			actualiser();
			}
		attendre_clic();
		

		
		for(j=0;j<7;j++)	//pioche si un emplacement de la main est vide
			{
			if (ma[j].lettre==(' '))
				ma[j]=pioche(tab_pioche,scoreJ1,scoreJ2);
			}
		dessiner_rectangle(p,700,75,noir);	
		afficher_main(ma);
		actualiser();
		w=0;
		
		while(w==0)	//le joueur peut agir dans cette boucle
			{
			p=attendre_clic();	
			
			if ((((p.x>49) && (p.x<86)) || ((p.x>99) && (p.x<136)) || ((p.x>149) && (p.x<186)) || ((p.x>199) && (p.x<236)) || ((p.x>249) && (p.x<286)) || ((p.x>299) && (p.x<336)) || ((p.x>349) && (p.x<386))) && ((p.y>630) && p.y<660))		//Déplacer un jeton 	
				deplacementjeton(ma,plateau,p,tab_pioche,pinf);
				
			else if ((p.x<TAILLE_TABLEAU_SCRABBLE) && (p.y<TAILLE_TABLEAU_SCRABBLE))	//reprendre un jeton en main
				reprendre(ma,plateau,p);
			else if ( (p.x>POSFINX) && (p.x<POSFINX + 100) && (p.y>POSFINY) && (p.y<POSFINY + 100) ) 	//Mettre fin à son tour
				{
		
				if (t==1)
					{
					for(k=0;k<7;k++)
						m1[k]=ma[k];
					if((pointsTour!=0) && (m1[0].lettre==(' ')) && (m1[1].lettre==(' ')) && (m1[2].lettre==(' ')) && (m1[3].lettre==(' ')) && (m1[4].lettre==(' ')) && (m1[5].lettre==(' ')) && (m1[6].lettre==(' ')))
						scoreJ1+=50;
					scoreJ1+=pointsTour;
					sprintf(sJ1,"%d",scoreJ1);
					dessiner_rectangle(psc1,80,20,noir);
					afficher_texte(sJ1,20,psc1,blanc);
					t=2;
					}
				else
					{
					for(k=0;k<7;k++)
						m2[k]=ma[k];
					if((pointsTour!=0) && (m1[0].lettre==(' ')) && (m1[1].lettre==(' ')) && (m1[2].lettre==(' ')) && (m1[3].lettre==(' ')) && (m1[4].lettre==(' ')) && (m1[5].lettre==(' ')) && (m1[6].lettre==(' ')))
						scoreJ2+=50;
					scoreJ2+=pointsTour;
					sprintf(sJ2,"%d",scoreJ2);
					dessiner_rectangle(psc2,80,20,noir);
					afficher_texte(sJ2,20,psc2,blanc);
					t=1;
					}
				w=1;
				
		
				}
						
			else if ( (p.x>POSDEFX) && (p.x<POSDEFX + 100) && (p.y>POSDEFY) && (p.y<POSDEFY + 100) )	//Defausser des lettres
				{
				afficher_texte("Cliquez sur un jeton pour le defausser", 15, pinf, blanc);
				actualiser();
				defausse(ma,tab_pioche);
				dessiner_rectangle(pinf,500,75,noir);				
				actualiser();
				}
						
			else if ( (p.x>POSCHECKX) && (p.x<POSCHECKX + 100) && (p.y>POSCHECKY) && (p.y<POSCHECKY + 100) )	//Trouver un mot sur le plateau à partir d'une lettre choisie
				{
				afficher_texte("Selectionnez une lettre a partir de laquelle", 15, pinf, blanc);
				pinf.y+=15;
				afficher_texte("s'effectuera la recherche de mot", 15, pinf, blanc);
				pinf.y-=15;
				actualiser();	
				p=attendre_clic();
				p.x = p.x - (p.x % 40) + 2 ; 
				p.y = p.y - (p.y % 40) + 2 ;
				c = ((p.x -2)/40);
				l = ((p.y -2)/40);
										
				pointsTour=rechercheMot(plateau,tabdico,c,l,bonus);
				dessiner_rectangle(pinf,100,100,noir);
				dessiner_rectangle(pinf,500,75,noir);	
				
				
				afficher_texte("Points marques a ce tour :",15,psct,blanc);	
				sprintf(stemp,"%d",pointsTour);
				psct.x+=210;
				dessiner_rectangle(psct,50,50,noir);
				afficher_texte(stemp,15,psct,blanc);	
				psct.x-=210;			
				actualiser();
				}
			else if ( (p.x>POSABANX) && (p.x<POSABANX + 100) && (p.y>POSABANY) && (p.y<POSABANY + 50) )	//Abandonner la partie
				{
				p.x=POSOUIX;			//creation de la case de confirmation
				p.y=POSOUIY;
				dessiner_rectangle(p,49,30,blanc);
				p.x+=10;
				p.y+=5;
				afficher_texte("Oui", 15, p, noir);	
				
				p.x=POSNONX;
				p.y=POSNONY;

				dessiner_rectangle(p,49,30,blanc);
				p.x+=10;
				p.y+=5;
				afficher_texte("Non", 15, p, noir);	
				actualiser();
				
				do 
				{
				p=attendre_clic();
				}
				while(( (p.x<POSOUIX) || (p.x>POSOUIX + 49) || (p.y<POSOUIY) || (p.y>POSOUIY + 30) ) && ( (p.x<POSNONX) || (p.x>POSNONX + 49) || (p.y<POSNONY) || (p.y>POSNONY + 30) ));
				
				if ( (p.x>POSOUIX) && (p.x<POSOUIX + 49) && (p.y>POSOUIY) && (p.y<POSOUIY + 30) )	//Confirmer l'abandon
					{
					w=1;
					if (t==1)
						i=fin(scoreJ1,scoreJ2,1);	
					else
						i=fin(scoreJ1,scoreJ2,2);
					}
				
				else if ( (p.x>POSNONX) && (p.x<POSNONX + 49) && (p.y>POSNONY) && (p.y<POSNONY + 30) )	//Confirmer l'abandon
					{
					p.x=POSOUIX;
					p.y=POSOUIY;
					dessiner_rectangle(p,100,40,noir);
					actualiser();
					}
				
				}
			}
		}
	attendre_clic();  //fin
	fermer_fenetre();
	return 0;
	}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   
//	FONCTIONS
//                                                                                                 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


int verifMot(char tabdico[SIZEDICO][MAXLENMOT], char mot[MAXLENMOT]) //recherche dichotomique dans le dictionnaire
	{
	int d=0,f=SIZEDICO-1,m=(d+f)/2;
	int valeur;

	do
		{
		valeur=strcmp(mot,tabdico[m]);
		if (valeur>0)
			d=m+1;
		else if (valeur<0) 
			f=m-1;
		m=(d+f)/2;
		}
	while ((d<=f) && valeur!=0);	
	
	if (valeur==0)
		return TRUE;
	else
		return FALSE;
	}



int rechercheMot(Lettre plateau[15][15],char tabdico[SIZEDICO][MAXLENMOT],int c, int l,int bonus[15][15])		//Cette fonction permet de trouver les mots sur le plateau qui partent d'une certaine lettre
	{
	int i=0,ct=c,lt=l,cbonus=c,lbonus=l,phor=0,pver=0,ptot=0;
	char hormot[MAXLENMOT],vermot[MAXLENMOT];
		
	while ((plateau[c][l].lettre != (' ')) && (c>=0) && (c<15))		//On remonte le mot vers la gauche jusqu'à rencontrer une case vide ou le bord du plateau
		c-=1;
	c+=1;

	while ((plateau[c][l].lettre != (' ')) && (c>=0) && (c<15))		//On inscrit les lettres de la ligne dans un tableau jusqu'à rencontrer une case vide ou le bord du plateau
		{
		hormot[i]=plateau[c][l].lettre;
		phor+=plateau[c][l].points;		
		i+=1;
		c+=1;
		}
	hormot[i]=('\0');												//Quand on a fini d'écrire le mot on ferme le tableau avec \0
		
	
	i=0;	
		
		
	while ((plateau[ct][lt].lettre != (' ')) && (ct>=0) && (ct<15))	//idem pour les colonnes
		lt-=1;
	lt+=1;
	
	while ((plateau[ct][lt].lettre != (' ')) && (ct>=0) && (ct<15))	
		{
		vermot[i]=plateau[ct][lt].lettre;
		pver+=+plateau[ct][lt].points;
		i+=1;
		lt+=1;
		}
	vermot[i]=('\0');

		
	if (verifMot(tabdico,hormot)==TRUE)							//on vérifie si le mot trouvé est dans le dictionnaire
		{
		if (bonus[cbonus][lbonus]==LETTRE_DOUBLE)				//vérification des cases bonus LETTRE
			phor+=plateau[cbonus][lbonus].points;
		if (bonus[cbonus][lbonus]==LETTRE_TRIPLE)				
			phor+=(plateau[cbonus][lbonus].points)*2;			
		ptot+=phor;
		}
	
	if (verifMot(tabdico,vermot)==TRUE)							//idem
		{
		if (bonus[cbonus][lbonus]==LETTRE_DOUBLE)								
			pver+=plateau[cbonus][lbonus].points;
		if (bonus[cbonus][lbonus]==LETTRE_TRIPLE)								
			pver+=(plateau[cbonus][lbonus].points)*2;
		ptot+=pver;
		}
		
	if (bonus[cbonus][lbonus]==MOT_DOUBLE)						//on vérifie les cases bonus MOT
		ptot=ptot*2;
		
	if (bonus[cbonus][lbonus]==MOT_TRIPLE)
		ptot=ptot*3;
	
	return ptot;	
	}


int chargeDico(char *filedico, char tabdico[SIZEDICO][MAXLENMOT])
{
    FILE *f = fopen(filedico,"r"); // ouverture du fichier

    if (!f) // si ouverture ratee
        {
        fprintf(stderr,"fopen: problème d'ouverture du fichier '%s'\n'",filedico);
        return 0;
        }

    char line[MAXLENMOT]; // la ligne servant à la lecture du fichier

    int mots=0; // indice dans tabdico 
    while(fgets(line,MAXLENMOT,f)) // tant que fgets ne renvoie pas nul (eof)
        {
        sscanf(line,"%s\n",tabdico[mots]); // je scanne line et ecris dans tabdico
        mots++;
        }
    fclose(f); // fermeture du fichier
    
    return mots;
}

	
void afficher_main(Lettre m[7])		//affiche la main
	{
	Point p={50,POSITION_MAIN};
	int i;	
	for (i=0;i<7;i++)
		{
		afficher_image(m[i].chemin,p);
		p.x+=50;
		}
	}

Lettre pioche(Lettre tab_pioche[100],int scoreJ1,int scoreJ2)		//Cette fonction tire une lettre aleatoire
	{
	int ale,i,j=0;	
	Lettre x;
	Lettre vide={' ',0,""};
	
	for (i=0;i<100;i++)				//Si la pioche est vide la partie est finie
		if (tab_pioche[i].lettre==(' '))
			j+=1;
	if (j==100)
		fin(scoreJ1,scoreJ2,0);
	
	do  		//On pioche une nouvelle lettre jusqu'a ce qu'on tombe sur une pouvant être piochee
		{
		ale=entier_aleatoire(100);
		}
	while(tab_pioche[ale].lettre==(' '));
	
	x=tab_pioche[ale];
	tab_pioche[ale]=vide;			//la lettre piochée devient une case vide dans le tableau tab_pioche
	return x;
	
	}


void deplacementjeton(Lettre m[7],Lettre plateau[15][15],Point p,Lettre tab_pioche[27],Point pinf) {		//Cette fonction permet de deplacer les jetons sur le plateau
	Point p1;
	int l,c,i,joker;
	Lettre vide={' ',0,""};
	afficher_texte("Cliquez sur une case pour placer le jeton", 15, pinf, blanc);
	actualiser();
	
	p1=attendre_clic();
	p1.x = p1.x - (p1.x % 40) + 2 ; //coordonnées en pixel du coin supérieur gauche de la case
	p1.y = p1.y - (p1.y % 40) + 2 ;

	c = ((p1.x -2)/40);				//transfère des coordonnées pixels en points
	l = ((p1.y -2)/40);	

	if ((p.x>49) && (p.x<86))		//On regarde quelle lettre le joueur a choisi
		i=0;
	else if ((p.x>99) && (p.x<136))
		i=1;					
	else if ((p.x>149) && (p.x<186))
		i=2;			
	else if ((p.x>199) && (p.x<236))
		i=3;			
	else if ((p.x>249) && (p.x<286))
		i=4;
	else if ((p.x>299) && (p.x<336))
		i=5;												
	else if ((p.x>349) && (p.x<386))
		i=6;


	if ( ((p1.x<TAILLE_TABLEAU_SCRABBLE) && (p1.y<TAILLE_TABLEAU_SCRABBLE)) && (plateau[c][l].lettre==(' ')) )	//si le joueur clique dans le plateau de jeu
		{
		if ( ((c==7) && (l==7)) || ( ( (plateau[c-1][l].lettre!=(' ')) || (plateau[c+1][l].lettre!=(' ')) ) || ( (plateau[c][l-1].lettre!=(' ')) || (plateau[c][l+1].lettre!=(' ')) )  ) )	//si le joueur clique sur la case de départ ou sur une case adjacente à une autre lettre
			{
			if (m[i].points == 0)	//si la lettre que veut poser le joueur est un joker
				{
				dessiner_rectangle(pinf,500,75,noir);	
				afficher_texte("Entrez une lettre au clavier", 20, pinf, blanc);
				actualiser();
				do{					//le joueur entre une valeur valide au clavier
				joker=attendre_touche();
				}
				while((joker != SDLK_a) && (joker != SDLK_b) && (joker != SDLK_c) && (joker != SDLK_d) && (joker != SDLK_e) && (joker != SDLK_f) && (joker != SDLK_g) && (joker != SDLK_h) && (joker != SDLK_i) && (joker != SDLK_j) && (joker != SDLK_k) && (joker != SDLK_l) && (joker != SDLK_m) && (joker != SDLK_n) && (joker != SDLK_o) && (joker != SDLK_p) && (joker != SDLK_q) && (joker != SDLK_r) && (joker != SDLK_s) && (joker != SDLK_t) && (joker != SDLK_u) && (joker != SDLK_v) && (joker != SDLK_w) && (joker != SDLK_x) && (joker != SDLK_y) && (joker != SDLK_z) );
				if(joker == SDLK_a)
					m[i].lettre=('a');
				else if (joker==SDLK_b)
					m[i].lettre=('b');
				else if (joker==SDLK_c)
					m[i].lettre=('c');
				else if (joker==SDLK_d)
					m[i].lettre=('d');
				else if (joker==SDLK_e)
					m[i].lettre=('e');
				else if (joker==SDLK_f)
					m[i].lettre=('f');
				else if (joker==SDLK_g)
					m[i].lettre=('g');
				else if (joker==SDLK_h)
					m[i].lettre=('h');
				else if (joker==SDLK_i)
					m[i].lettre=('i');
				else if (joker==SDLK_j)
					m[i].lettre=('j');
				else if (joker==SDLK_k)
					m[i].lettre=('k');
				else if (joker==SDLK_l)
					m[i].lettre=('l');
				else if (joker==SDLK_m)
					m[i].lettre=('m');
				else if (joker==SDLK_n)
					m[i].lettre=('n');
				else if (joker==SDLK_o)
					m[i].lettre=('o');
				else if (joker==SDLK_p)
					m[i].lettre=('p');
				else if (joker==SDLK_q)
					m[i].lettre=('q');
				else if (joker==SDLK_r)
					m[i].lettre=('r');
				else if (joker==SDLK_s)
					m[i].lettre=('s');
				else if (joker==SDLK_t)
					m[i].lettre=('t');
				else if (joker==SDLK_u)
					m[i].lettre=('u');
				else if (joker==SDLK_v)
					m[i].lettre=('v');
				else if (joker==SDLK_w)
					m[i].lettre=('w');
				else if (joker==SDLK_x)
					m[i].lettre=('x');
				else if (joker==SDLK_y)
					m[i].lettre=('y');
				else if (joker==SDLK_z)
					m[i].lettre=('z');	
				}			
			afficher_image(m[i].chemin,p1);			//on affiche le jeton et on remplit le tableau
			p.x=50*i+50;
			p.y=630;
			dessiner_rectangle(p,40,40,noir);
			plateau[c][l]=m[i];
			m[i]=vide;								//la lettre utilisée est supprimée de la main
			}
		}
	dessiner_rectangle(pinf,500,75,noir);			
	actualiser();
}

void defausse(Lettre m[7], Lettre tab_pioche[27])		//Cette fonction permet de se defausser d'un jeton
	{
	int i;
	Lettre vide={' ',0,""};
	Point p;
	p=attendre_clic();
	
	if ((((p.x>49) && (p.x<86)) || ((p.x>99) && (p.x<136)) || ((p.x>149) && (p.x<186)) || ((p.x>199) && (p.x<236)) || ((p.x>249) && (p.x<286)) || ((p.x>299) && (p.x<336)) || ((p.x>349) && (p.x<386))) && ((p.y>630) && p.y<660))	//si le joueur clique sur l'un de ses jetons
		{
		if ((p.x>49) && (p.x<86))
			i=0;
		else if ((p.x>99) && (p.x<136))
			i=1;					
		else if ((p.x>149) && (p.x<186))
			i=2;			
		else if ((p.x>199) && (p.x<236))
			i=3;			
		else if ((p.x>249) && (p.x<286))
			i=4;
		else if ((p.x>299) && (p.x<336))
			i=5;												
		else if ((p.x>349) && (p.x<386))
			i=6;
		}
	
	m[i]=vide;					//il se défausse de ce jeton
	p.x=50*i+50;
	p.y=630;
	dessiner_rectangle(p,40,40,noir);

	actualiser();

	}

void reprendre(Lettre m[7],Lettre plateau[15][15],Point p)		//Cette fonction permet de prendre un jeton du plateau dans sa main
	{						
	Lettre vide={' ',0,""};
	int i=0,c,l;	
	c = ((p.x -2)/40);
	l = ((p.y -2)/40);
	
	if (plateau[c][l].lettre!=(' '))							//si la case du plateau sur laquelle le joueur a cliqué contient une lettre			
		{
		while ((m[i].lettre!=(' ')) && (i<6))					//on cherche un emplacement libre dans la main du joueur
			i+=1;
		if (m[i].lettre==(' '))									//si on en trouve un
			{
			m[i]=plateau[c][l];									//on retire le jeton du plateau et on le met dans la main du joueur
			plateau[c][l]=vide;
			p.x = p.x - (p.x % 40)+2; 
			p.y = p.y - (p.y % 40)+2;
			dessiner_rectangle(p,36,36,beige);
			p.x = 50+(50*i); 
			p.y = POSITION_MAIN;	
			afficher_image(m[i].chemin,p);
			}

		
		}

	actualiser();	
	}
	
void defbonus(int bonus[15][15])								//initialisation des cases bonus
	{
	bonus[0][0]=MOT_TRIPLE;
	bonus[7][0]=MOT_TRIPLE;
	bonus[14][0]=MOT_TRIPLE;
	bonus[0][7]=MOT_TRIPLE;
	bonus[14][7]=MOT_TRIPLE;
	bonus[0][14]=MOT_TRIPLE;
	bonus[7][14]=MOT_TRIPLE;
	bonus[14][14]=MOT_TRIPLE;	

	bonus[1][1]=MOT_DOUBLE;
	bonus[2][2]=MOT_DOUBLE;
	bonus[3][3]=MOT_DOUBLE;
	bonus[4][4]=MOT_DOUBLE;
	bonus[13][1]=MOT_DOUBLE;
	bonus[12][2]=MOT_DOUBLE;
	bonus[11][3]=MOT_DOUBLE;
	bonus[10][4]=MOT_DOUBLE;
	bonus[1][13]=MOT_DOUBLE;
	bonus[2][12]=MOT_DOUBLE;
	bonus[3][11]=MOT_DOUBLE;
	bonus[4][10]=MOT_DOUBLE;
	bonus[13][13]=MOT_DOUBLE;
	bonus[12][12]=MOT_DOUBLE;
	bonus[11][11]=MOT_DOUBLE;
	bonus[10][10]=MOT_DOUBLE;

	bonus[3][0]=LETTRE_DOUBLE;
	bonus[11][0]=LETTRE_DOUBLE;
	bonus[6][2]=LETTRE_DOUBLE;
	bonus[8][2]=LETTRE_DOUBLE;
	bonus[14][2]=LETTRE_DOUBLE;
	bonus[0][3]=LETTRE_DOUBLE;
	bonus[7][3]=LETTRE_DOUBLE;
	bonus[14][3]=LETTRE_DOUBLE;
	bonus[2][6]=LETTRE_DOUBLE;	
	bonus[6][6]=LETTRE_DOUBLE;
	bonus[8][6]=LETTRE_DOUBLE;
	bonus[12][6]=LETTRE_DOUBLE;
	bonus[3][7]=LETTRE_DOUBLE;
	bonus[11][7]=LETTRE_DOUBLE;
	bonus[2][8]=LETTRE_DOUBLE;
	bonus[6][8]=LETTRE_DOUBLE; 
	bonus[8][8]=LETTRE_DOUBLE;
	bonus[12][8]=LETTRE_DOUBLE;
	bonus[0][11]=LETTRE_DOUBLE;
	bonus[7][11]=LETTRE_DOUBLE;
	bonus[14][11]=LETTRE_DOUBLE;
	bonus[6][12]=LETTRE_DOUBLE;
	bonus[8][12]=LETTRE_DOUBLE;
	bonus[3][14]=LETTRE_DOUBLE;	
	bonus[11][14]=LETTRE_DOUBLE;

	bonus[5][1]=LETTRE_TRIPLE;
	bonus[9][1]=LETTRE_TRIPLE;
	bonus[1][5]=LETTRE_TRIPLE;
	bonus[5][5]=LETTRE_TRIPLE;
	bonus[9][5]=LETTRE_TRIPLE;
	bonus[13][5]=LETTRE_TRIPLE;
	bonus[1][9]=LETTRE_TRIPLE;
	bonus[5][9]=LETTRE_TRIPLE;
	bonus[9][9]=LETTRE_TRIPLE;
	bonus[13][9]=LETTRE_TRIPLE;
	bonus[5][13]=LETTRE_TRIPLE;
	bonus[9][13]=LETTRE_TRIPLE;
}

int fin (int scoreJ1, int scoreJ2,int abandon)
	{
	Point p = {50,POSITION_MAIN};
	dessiner_rectangle(p,500,100,noir);
	
	if (abandon == 1)											//on regarde si la fonction a été appelée par l'abandon d'un des deux jo
		afficher_texte("VICTOIRE DU JOUEUR 2",50,p,blanc);

	else if (abandon == 2)
		afficher_texte("VICTOIRE DU JOUEUR 1",50,p,blanc);

	else 														//si ce n'est pas le cas on regarde qui a le meilleur score
		{
		if (scoreJ1>scoreJ2)
			afficher_texte("VICTOIRE DU JOUEUR 1",50,p,blanc);
			
		else if (scoreJ2>scoreJ1)
			afficher_texte("VICTOIRE DU JOUEUR 2",50,p,blanc);
		else if (scoreJ2==scoreJ1)
			afficher_texte("EGALITE", 50,p,blanc);	
		}
	actualiser();
	return 100;
	}

void Ecrantitre(void)
	{
	Point p1 ={0,0};
	Point p2;
	ouvrir_fenetre(LARGEUR_ECRAN_TITRE,HAUTEUR_ECRAN_TITRE);
	afficher_image("../Images/ecrantitre.bmp",p1);
	actualiser();

	do
	{
	p2= attendre_clic();
	}
	while( (((p2.y<325) || (p2.y>430)) && ((p2.x<100) || (p2.x>125))) && (((p2.y<325) || (p2.y>430) )&&( (p2.x<655) || (p2.x>880))) );
	
	if ((p2.y>325) && (p2.y<430) && (p2.x>100) && (p2.x<125))				//si le joueur appuie sur start
		printf("Bonne chance"); 
	else if ((p2.y>325) && (p2.y<430) && ((p2.x>655) && (p2.x<880) ))		//si le joueur appuie sur quitter
			fermer_fenetre();
	}
	
