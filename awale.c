#include <stdio.h>
#include <stdlib.h>
#include "awale.h"
#include <time.h>

int main() {
	int jeu[12]; // tableau de 12 entiers 
	int J1;
	int J2;
	int sensRotation; // 0 = Sens Horaire; 1 = Anti-horaire
	int tourJeu;  // 0 = J1; 1 = J2
	int caseNum = 0;
	int nb_graine;
	int num;
	int test;
	int modeJeu = 0 ;
	int nb ;
	int win  = 0;
	srand(time(NULL));
	
    initialiserJeu( &J1, &J2, &sensRotation, &tourJeu, jeu);
    mode(&modeJeu) ;
    AfficherJeu(&J1, &J2,  &sensRotation,  &tourJeu, jeu);
    do {
        saisieCase(&caseNum, &tourJeu, jeu, &modeJeu, &nb);
        distribution(jeu, &caseNum, &nb_graine, &tourJeu, &J1, &J2, &num, &test, &modeJeu);
        AfficherJeu(&J1, &J2,  &sensRotation,  &tourJeu, jeu);
        if(modeJeu == 1 && (jeu[0] + jeu[1] + jeu[2] + jeu[3] + jeu[4] + jeu[5] == 0)){
            printf("Fin du jeu : le Joueur 2 a gagné ! ") ;
            win = 2 ;     // Si win = 2 J2 ou IA gagnant
        }
        if(modeJeu == 1 && (jeu[6] + jeu[7] + jeu[8] + jeu[9] + jeu[10] + jeu[11] == 0)){
            printf("Fin du jeu : le Joueur 1 a gagné ! ") ;
            win = 1 ;     // Si win = 1 le Joueur 1 gagnant
        }
        if(modeJeu == 2 && (jeu[0] + jeu[1] + jeu[2] + jeu[3] + jeu[4] + jeu[5] == 0)){
            printf("Fin du jeu : l'IA a gagné ! ") ;
            win = 2 ;
        }
        if(modeJeu == 2 && (jeu[6] + jeu[7] + jeu[8] + jeu[9] + jeu[10] + jeu[11] == 0)){
            printf("Fin du jeu : le Joueur a gagné ! ") ;
            win = 1 ;
        }
    } while (win != 1 || win != 2);
}
void initialiserJeu(int *pJ1, int *pJ2, int *psensRotation, int *ptourJeu, int *tab) {
	
	*pJ1 = 0;
	*pJ2 = 0;
	*psensRotation = 1;
	*ptourJeu = 0;
	
	for(int i = 0; i < 12; i++){
		tab[i] = 4;
	}

}

void mode(int *pmodeJeu){
    printf("Voici les modes de jeu pour l'awalé : \n") ;
    printf("1 = Mode Joueur VS Joueur \n") ;
    printf("2 = Mode Joueur VS IA (IA facile) \n") ;
    printf("Veuillez choisir le mode de jeu : ") ;
    scanf("%d", pmodeJeu) ;
    while(*pmodeJeu == 0 || *pmodeJeu > 2){
        printf("Erreur, veuilez rechoisir un mode : ") ;
        scanf("%d", pmodeJeu) ;
    }
}

void AfficherJeu(int *pJ1, int *pJ2, int *psensRotation, int *ptourJeu, int *tab) {

    for (int i = 11; i > 5; i--)
    {
        printf("%2d [%2d] ",i, tab[i]);
    }

    printf("\n");

    for (int i = 0; i  < 6 ; i++)
    {
        printf("%2d [%2d] ",i , tab[i]);
    }

    printf("\n\n");

    printf("Score du joueur 1 : %d \n", *pJ1);
    printf("Score du joueur 2 : %d \n", *pJ2);

    printf("\n");
}

void saisieCase(int *pcaseNum, int *ptourJeu, int *tab, int *pmodeJeu, int *pnb){
    printf("Tour joueur : %d", *ptourJeu);
    printf("\n");
        if(*pmodeJeu == 2){               // Choix de la case IA
        if(*ptourJeu == 1){
            *pnb = rand() % (12 - 6) + 6 ;
            while(tab[*pnb] == 0){
                *pnb = rand() % (12 - 6) + 6 ;
            }
        }
        *pcaseNum = *pnb ;
    }
    if((*pmodeJeu == 1 && *ptourJeu == 0 ) || (*pmodeJeu == 2 && *ptourJeu == 0) || (*pmodeJeu == 1 && *ptourJeu == 1)){
        printf("Quelle case voulez-vous choisir ? ");
        scanf("%d", pcaseNum);
    }
    if((*pmodeJeu == 1 || *pmodeJeu == 2) && *ptourJeu == 0){
    while((*ptourJeu == 0 && *pcaseNum > 5) || (*ptourJeu == 0 && *pcaseNum < 6 && tab[*pcaseNum] == 0)){
        if(*ptourJeu == 0 && *pcaseNum < 6 && tab[*pcaseNum] == 0){
            printf("Cette case est vide, veuillez choisir une autre case : ");
        }
        else{
            printf("Vous ne pouvez pas jouer cette case ! ");
        }
        scanf("%d", pcaseNum);
    }
    }
    if(*pmodeJeu == 1 && *ptourJeu == 1) {          // Choix de la case du Joueur 2
    while((*ptourJeu == 1 && *pcaseNum < 6) || (*ptourJeu == 1 && *pcaseNum > 5 && tab[*pcaseNum] == 0) || (*ptourJeu == 1 && *pcaseNum > 11)){

        if(*ptourJeu == 1 && *pcaseNum > 5 && tab[*pcaseNum] == 0){
            printf("Cette case est vide, veuillez choisir une autre case : ");
        }
        
        if(*ptourJeu == 1 && *pcaseNum > 11){
            printf("Cette case n'existe pas, veuillez saisir une case entre 6 et 11 : ") ;
        }
        else{
            printf("Vous ne pouvez pas jouer cette case ! ");
        }
        scanf("%d", pcaseNum);
        }
    }
    
    

    printf("La case %d a été choisi \n", *pcaseNum );
}

void distribution(int *tab, int *pcaseNum, int *pnb_graine, int *ptourJeu, int *pJ1, int *pJ2, int *pnum, int *ptest, int *pmodeJeu){
    *pnb_graine = tab[*pcaseNum]; // On sauvegarde le nombre de graine dans la variable
    
    if(*pnb_graine >= 12)       ((*ptest) = 1);
    else{
        (*ptest) = 0 ;
    }
    
	for (int i = (*pcaseNum); (*pnb_graine) != 0 ; i++){
	*pnum = i + 1;      // On mémorise la dernière case
	
	    tab[*pcaseNum]--; // On décremente le nombre de graine de la case choisie
	    
	    if(i == 11 && (*pnb_graine) == 1){
	        tab[0]++;
	        *pnum = 0 ;
	    }
	    
	    if(i > 11){
	        i = 0;
	        tab[i]++;
	    }
	    
	    if((*ptest) == 1 && i == (*pcaseNum)){
	        tab[*pcaseNum] = 0;
	        i++;
	        tab[i]++;
	    }
	    tab[i+1]++; // On incrémente le nombre de graine de la case i
	    (*pnb_graine)--; // On décremente le nombre de graine
	}
	
    
    while(*ptourJeu == 0 && *pnum > 5 && tab[*pnum] < 4){           // Boucle récupération graine
            *pJ1 = *pJ1 + tab[*pnum];
            tab[*pnum] = 0;
            (*pnum)--;
    }
    
    while(*ptourJeu == 1 && *pnum < 6 && tab[*pnum] < 4){
            *pJ2 = *pJ2 + tab[*pnum];
            tab[*pnum] = 0;
            (*pnum)--;
    }

    if(*ptourJeu == 0){
        *ptourJeu = 1;
    }
    else{
        *ptourJeu = 0;
    }
    
}
