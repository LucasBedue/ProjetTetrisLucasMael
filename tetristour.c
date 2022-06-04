/* 
Le programme du jeu Tetris est le programme "Tetrisgame". Il initie toute les variables éxécute le jeu. 
*/

#include"header.h"

Player Tetrisgame(Player player2){//Fonction représentant les tours de jeu.

int** plate=NULL;//initialisation du pointeur du plateau de jeu
double timeofturn=60;//initialisation du temps d'un seul tour au départ
int choiceofcolumn=0;//Pour choisir la colonne de dépot de pièce
int choiceofsens=0;//Pour choisir le sens de la pièce
Piece tabpiece[7];//initialisation tableau de pieces
Piece actualpiece;//la pièce que l'on aura durant le tour actuel
plate=initiateplate();//initialisation du plateau de jeu
for(int i=0;i<7;i++){
tabpiece[i]=initiatepiece(tabpiece[i],i+1);//initialisation du profil des pieces
}
//on initie les caractéristique du joueur.
player2.defeat=0;
player2.playerscore=0;
player2.playername=malloc(100*sizeof(char));
entername(player2.playername);//on rentre le prénom du joueur
int nbactualpiece=0;//sert a choisir aléatoirement la pièce que l'on aura sur ce tour

int youcanplaceit=0;//sert a savoir si le plateau est déja plein ou non

double timestaying[1];//permet de connaitre le temps restant
timestaying[0]=0;



do{//Début de tour
//On initie les variables et prend une pièce au hasard
timestaying[0]=timeofturn;
nbactualpiece=rand()%7;
actualpiece=tabpiece[nbactualpiece];//On prend une piece au hasard
choiceofsens=0;

//Tour de sélection du sens de la piece,on choisi au hasard si on passe trop de temps a choisir le sens.
choiceofsens=selectchoiceofsens(plate,actualpiece,timestaying);

if(timestaying[0]>0){//Si il reste assez de temps, on continue, sinon ca passe notre tour avec des variables au hasard.

if(possibletoplace(plate,actualpiece,choiceofsens)==0){
//On regarde si elle rentre dans AU MOINS une case du tableau: si oui, on continue, sinon, on perd.

do{

choiceofcolumn=0;
youcanplaceit=0;

choiceofcolumn=selectchoiceofcolumn(plate,actualpiece,timestaying);//on choisi la colonne de dépot de la piece

if(timestaying[0]<0){//si pn a pris trop de temps, on prend une valeur au hasard
    choiceofcolumn=rand()%10+1;
}

youcanplaceit=verifplacement(plate,choiceofcolumn-1,actualpiece,choiceofsens);//On verifie si la pièce est acceptable dans le tableau(si elle ne sort pas du cadre).
if(youcanplaceit==1){
    printf("You can't place it here!\n");
}

}while(youcanplaceit==1);

}
else{player2.defeat=1;}
}
else{
    choiceofsens=rand()%4+1;
    choiceofcolumn=rand()%10+1;
}


player2.defeat=piecefalling(plate,actualpiece,choiceofcolumn,choiceofsens);//Dépot de la piece sur le plateau a l'endroit choisi

player2.playerscore=player2.playerscore+destroyaline(plate);//On casse les lignes pleines, et incrémente le score du joueur
timeofturn=timeofturn*0.90;
}while(player2.defeat==0);//Condition de perte remplie?

    return player2;//Renvoie le profil du joueur.
}