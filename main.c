/* Le programme représente le menu principal. Il initie le "srand" et demande au joueur si il souhaite lancer une partie, voir les
* high-scores, ou juste s'en aller.*/



#include"header.h"

int main(int argc,char ** argv){

srand(time(NULL));//initialisation de l'aléatoire

int choicemenu=0; //initialisation menu

Player player1; //initialisation du profil du joueur


do{ 
printf("Souhaite-tu :\n1) Jouer\n2) Quitter\n3) Voir les high-scores\n");
scanf("%d",&choicemenu);

}while((choicemenu<1)||(choicemenu>3));

switch(choicemenu){
case 1 :{//option lancer la partie
    player1=Tetrisgame(player1);
    printf("Bravo %s! tu a eu %d points!\n",player1.playername,player1.playerscore);
    savehighscore(player1);
    showscores();
}

break;

case 2 :{//option quitter
    printf("Ok bye!\n");
    }
break;

case 3 :{//option voir les scores
    showscores();
    }
break;
}

return 0;//fin programme
}