//liste des bibliothèques
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>
#include<math.h>
#include<errno.h>

//liste des structures
typedef struct{
char* playername;//son nom
int playerscore;//son score
int defeat;//le joueur a t il perdu?
}Player;

typedef struct{
int numpiece;//le num de la piece
int tabpieceform[4][4][4];//le sens,puis sa forme dans la matrice
}Piece;


//Liste des fonctions
Player Tetrisgame(Player player2);
unsigned long getTimeMicroSec();
void entername();
int** initiateplate();
Piece initiatepiece(Piece pieceaini,int numpieceaini);
void showplate(int** ptr);
void showpiecesenschoice(Piece actualpiece);
void showpiecelinechoice();
int verifplacement(int **ptr, int choiceofcolum,Piece apiece,int senspiece);
int possibletoplace(int** plat,Piece actualpiece2,int choicesens);
int piecefalling(int** plat,Piece apiece,int choiceofcolum,int choicesens);
int selectchoiceofsens(int** plat,Piece apiece,double timestaying2[]);
int destroyaline(int** ptr);
int selectchoiceofcolumn(int** plat,Piece apiece,double timestaying2[]);
void savehighscore(Player p);
void showscores();

