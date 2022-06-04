/* 
Ici se trouvent les fonctions et procédures qui permettent le bon déroulement du jeu.
*/

#include"header.h"

unsigned long getTimeMicroSec(){//Fonction qui permet le calcul du temps de prise de décision de la part du joueur. Il renvoi l'heure en microsecondes.
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return(1000000 * tv.tv_sec) + tv.tv_usec;
}

void entername(char* playername2){//Procédure qui permet de rentrer le nom du joueur sur 100 caractères.

char name[100];

    printf("Veuillez rentrer votre nom :\n");
   scanf ("%s",name);
getchar();

for(int i=0;i<100;i++){
    playername2[i]=name[i];
}


}


int** initiateplate(){//Fonction qui permet l'initialisation du plateau de jeu. Toutes les cases se remplissent de 0, et sont considérées vides. Elle retourne un pointeur.

int** ptr=NULL;
ptr=malloc(10*sizeof(int*));
for(int i=0;i<10;i++){
ptr[i]=malloc(10*sizeof(int));
for(int j=0;j<10;j++){
ptr[i][j]=0;
}

}
return ptr;
}


Piece initiatepiece(Piece pieceaini,int numpieceaini){//Fonction qui initialise la forme de chaque piece en regardant le fichier "pieceshape.txt". Elle est appelée 7 fois pour les 7 pièces.
FILE* fichierpieces=NULL;
fichierpieces=fopen("pieceshape.txt","r+");
if (fichierpieces==NULL){
    printf("Ouverture impossible\n");
    printf("Code d'erreur = %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

int q=1;
int c=0;
pieceaini.numpiece=numpieceaini;
rewind(fichierpieces);

while(q!=numpieceaini){
    for(int u=0;u<80;u++){
        c=fgetc(fichierpieces);
    }
    q++;
}

for(int i=0;i<4;i++){
    for(int f=0;f<4;f++){
    for(int x=0;x<4;x++){
        c=fgetc(fichierpieces);
        
        if(c==' '){
            pieceaini.tabpieceform[i][f][x]=0;
            
        }
        else{
            pieceaini.tabpieceform[i][f][x]=1;
           
        };
            
    }
   c=fgetc(fichierpieces);
    }
    
}

fclose(fichierpieces);
return pieceaini;
}


void showplate(int** ptr){//Procedure qui affiche le plateau principal.
   system("clear");

    printf(" ");
   for(int a=0;a<10;a++){
    printf("%c ",(65+a));
   }
   printf("\n|");
   for(int j=0;j<9;j++){

   for(int i=0;i<10;i++){
       if(ptr[j][i]==0){
           printf(" |");
       }
       else{printf("@|");}
   }
   printf("\n|");
   }
    for(int p=0;p<10;p++){
        if(ptr[9][p]==0){
           printf(" |");
       }
       else{printf("@|");}
    }
    printf("\n");
}

void showpiecesenschoice(Piece actualpiece2){//Procédure qui affiche les 4 sens de la pièce actuelle et qui demande a ce qu'on en choisissent une.
printf("Choisir l'orientation de la piece :\n");



printf("  ");
for(int i=0;i<4;i++){
    printf("%d    ",(i+1));
}
printf("\n");

for(int m=0;m<4;m++){
for(int j=0;j<4;j++){
    for(int h=0;h<4;h++){
        if(actualpiece2.tabpieceform[j][m][h]==0){
            printf(" ");
        }
        else{
            printf("@");
        };
    }
    printf(" ");
}
printf("\n");
}

}

void showpiecelinechoice(){//Procedure qui affiche l'indication de choisir une ligne du plateau de jeu.

printf("Placez la pièce entre la colonne 1 et 10(incluses)\n");

}


int verifplacement(int **ptr, int choiceofcolum,Piece apiece,int senspiece){//Fonction qui verifie si la piece ne dépasse pas les cadres lors de la pose.

int largeurmax=0;
int bool=0;


for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
        if(apiece.tabpieceform[senspiece-1][j][i]==1)
        bool=1;
    }
    if(bool==1){
        largeurmax++;
        bool=0;
    }
}


if((choiceofcolum+largeurmax)>10){
    return 1;//Retourn un problème
}
else{
    return 0;// Retourne qu'il n'y a pas de problèmes
}

}


int possibletoplace(int** plat,Piece actualpiece2,int choicesens){//Fonction qui verifie si la piece rentre dans AU MOINS une case du plateau de jeu.
int bool=1;

for(int i=0;i<10;i++){
    if(verifplacement(plat,i,actualpiece2,choicesens)==0){
        bool=0;
       
    }
}

return bool;//Si 0, plaçable a un endroit au moins, sinon on perdra.

}

int piecefalling(int** plat,Piece apiece,int choiceofcolum,int choicesens){// Fonction fait tomber la piece et vérifie qu'elle peut bien descendre a chaque itération. Si elle n'est pas plaçable entierement dans le plateau, on perd.
int g=0;//booléen qui regarde si on peut descendre d'un cran
int compteurdescente=0;//compteur qui indique de combien de case la piece peut descendre



while(g==0){

for(int p=0;p<4;p++){
    for(int q=0;q<4;q++){
        
        if(apiece.tabpieceform[choicesens-1][p][q]!=0){
            if(p+compteurdescente>8){
                g=1;
                
            }
            if((q+choiceofcolum-1>9)&&(apiece.tabpieceform[choicesens-1][p][q]==1)){
                g=1;
                
            }
            if(g!=1){
                if((apiece.tabpieceform[choicesens-1][p][q]==1)&&(plat[p+compteurdescente][choiceofcolum-1+q]==1)){
                g=1;
                compteurdescente--;
                
            }
            }
        }
    }   
    
    }
if(g==0){
    compteurdescente++;
}

}
if(compteurdescente==-1){
    return 1;//Retourne qu'il y a un probleme
}

//On place la piece.
for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
        if((apiece.tabpieceform[choicesens-1][i][j]==1)&&(plat[i+compteurdescente][choiceofcolum-1+j]==0)){
            plat[i+compteurdescente][choiceofcolum-1+j]=1;
    }
}
}
return 0;

}

int selectchoiceofsens(int** plat,Piece apiece,double timestaying2[]){//Fonction qui montre le plateau, les 4 sens de la pièce, indique qu'il faut en choisir une et retourne celle choisi.
int ch=0;
unsigned long begin = getTimeMicroSec();


do{
showplate(plat);
showpiecesenschoice(apiece);
scanf("%d",&ch);
getchar();
}while((ch<1)||(ch>4));

unsigned long end = getTimeMicroSec();

unsigned long millis = (end-begin) / 1000; 

timestaying2[0]=timestaying2[0]*1000;

timestaying2[0]=(timestaying2[0]-millis);

timestaying2[0]=(timestaying2[0]/1000);//Le temps restant est réduit du temps que l'on a pris a rentrer la variable.

return ch;
}

int destroyaline(int** ptr){//Fonction qui detruit les lignes et retourne les points gagnés.
int scor=0;
int h=0;
int k=0;



for(int i=0;i<10;i++){
    h=0;
    k=0;
    for(int j=0;j<10;j++){
        if(ptr[i][j]==1){
            h++;
        }
    }
    if(h==10){//Si la ligne est pleine, le score monte et la ligne est detruite.
        scor++;
        for(k=i;k>0;k--){
            for(int g=0;g<10;g++){
            ptr[k][g]=ptr[k-1][g];
            }
        }
        for(int d=0;d<10;d++){
            ptr[0][d]=0;
        }

    }
}

return scor;
}

int selectchoiceofcolumn(int** plat,Piece apiece,double timestaying2[]){//Fonction qui demande a l'utilisateur de choisir une des lignes de jeu, et qui retourne celle choisi.
int ch=0;
unsigned long begin = getTimeMicroSec();


do{
showpiecelinechoice();
scanf("%d",&ch);
getchar();
}while((ch<1)||(ch>10));

unsigned long end = getTimeMicroSec();

unsigned long millis = (end-begin) / 1000; 

timestaying2[0]=timestaying2[0]*1000;

timestaying2[0]=(timestaying2[0]-millis);

timestaying2[0]=(timestaying2[0]/1000);//Le temps restant est réduit du temps que l'on a pris a rentrer la variable.

return ch;
}

void savehighscore(Player p){//Procedure qui enregistre le "playerX.score" dans le fichier "score.txt", à la fin. 
FILE* fichierscore=NULL;
fichierscore=fopen("score.txt","a+");
if (fichierscore == NULL) {
    printf("Ouverture impossible\n");
    printf("Code d'erreur = %d\n", errno);
    printf("%s\n", strerror(errno));
    exit(1);
}

fprintf(fichierscore, "\n");
fprintf(fichierscore, "%s", p.playername);
fprintf(fichierscore, "\n");
fprintf(fichierscore, "%d", p.playerscore);

fclose(fichierscore);
}






void showscores(){//Procédure qui affiche les score de "score.txt"
FILE* fichierscore=NULL;
fichierscore=fopen("score.txt","r+");
if (fichierscore==NULL){
    printf("Ouverture impossible\n");
    printf("Code d'erreur = %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}
rewind(fichierscore);
printf("Voici les scores :\n\n");

int v = 0;
while ((v = fgetc(fichierscore)) != EOF) {
    printf("%c", v);
}
printf("\n");

fclose(fichierscore);
}


