#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAILLE_TAB 4

void affiche(int tableau[TAILLE_TAB]){
    //prend un tableau rempli de 4 chiffre au préalable puis passe les chiffres en lettres
    for (int i = 0; i < TAILLE_TAB; i++)
    {
        if (tableau[i]==1)
        {
            printf("P");
        }
        if (tableau[i]==2)
        {
            printf("B");
        }
        if (tableau[i]==3)
        {
            printf("M");
        }
        if (tableau[i]==4)
        {
            printf("Y");
        }
        if (tableau[i]==5)
        {
            printf("O");
        }
        if (tableau[i]==6)
        {
            printf("G");
        } 
    }
}
void afficheP(int tableau[TAILLE_TAB],int d,int t){
    /*prend en paramètre un tableau avec des chiffres indiquant le bon placement ou non de la saisie du joueur
    et renvoie les caractères correspondant, le . pour dire que sa lettre saisie n'est pas dans le code secret
    , le R pour dire que la lettre est dans le code mais pas à la bonne place puis le w pour dire que la lettre
    est dns le code et à la bonne place.
    prend en parametre deux chiffre, d pour savoir à partir de quelle valeur on commence à afficher,puis t pour
    le nombre de lettre qu'on va afficher
    */
    for (int i = d; i < t; d++)
    {
        if (tableau[i]==0)
        {
            printf(".");
        }
        if (tableau[i]==1)
        {
            printf("W");
        }
        if (tableau[i]==2)
        {
            printf("R");
        }
    }
}

void responseGen(int tab[TAILLE_TAB]){
    //prend un tableau de taille 4 et le remplie de chiffre aléatoire entre 1 et 6
    srand(time(NULL));
    int i;
    for (i = 0; i < TAILLE_TAB; i++)
    {
        tab[i] = rand()%6 + 1;
    }
    printf("\n");

}
int rangementTaTor(int tab[TAILLE_TAB],int v){
    /*prend un tableau et une valeur(0,1,2) -> mise dans le tableau de façon aléatoire 
    -> s'affiche quand il est plein*/
    srand(time(NULL));
    if (v<0 || v>2 )
    {
        printf("La valeur n'est pas compris entre 0 et 2, veuillez recommencer \n");
        return 0;
    }
    int max = 0;
    int tmp = 1;
    while (tmp != 0)
    {
        int a = rand()%4;
        if (tab[a] == 9)
        {
            tab[a] = v;
            tmp = 0;
        }
    }
}

void saisir(int tab[TAILLE_TAB]){
    //remplie un tableau de taille 4 avec 4 valeurs saisie par le joueur entre 1 et 6 representant les lettres
    int tmp = 0;
    printf("Valeurs pouvant etre rentrer: 1->P,2->B,3->M,4->Y,5->O et 6->G\n");
    printf("Quelle valeur voulez vous entrer? \n");
    scanf("%d %d %d %d",&tab[tmp],&tab[tmp+1],&tab[tmp+2],&tab[tmp+3]);
}

int compare(int secret[TAILLE_TAB],int saisie[TAILLE_TAB],int test[TAILLE_TAB]){
    /*prend en parametre les trois tableau, celui du code secret, de la saisie joueur, et celui affichant les 
    bon placement des lettres
    parcour les tableaux du code secret et de la saisie, et 
    -si la lettre saisie est dans le code et à la bonne place appel rangementTaTor pour lui dire qu'elle
    est a la bonne place et incremente de 1 win qui si il arrive a 4 signifie que les deux codes sont indentiques
    donc le joueur gagne
    -si la lettre saisie est dans le code mais pas à la bonne place, appel rangementTaTor pour lui dire qu'elle
    est pas à la bonne place
    -si la lettre saisie n'est pas dans le code, appel rangementTaTor pour lui dire qu'elle n'y est pas*/
    int win = 0;
    for (int i = 0; i < TAILLE_TAB; i++){
        if (saisie[i]==secret[i]){
            rangementTaTor(test,1);
            printf("1");
            win+=1;
        }else{
            int nul = 0;
            for (int j = 0; j < TAILLE_TAB; j++){
                if (saisie[i]==secret[j]){
                    rangementTaTor(test,2);
                    printf("2");
                }else
                {
                    nul+=1;
                }
                
            }
            if (nul==4){
                    rangementTaTor(test,0);
                    printf("0");
                }
        }              
    }
    if (win==4){
        return 1;
    }else{
        return 0;
    }
}
void bla(int tab[TAILLE_TAB]){
    for (int i = 0; i < TAILLE_TAB; i++)
    {
        printf("%d",tab[i]);
    } 
}

int main(){
    /*fonction principal permettant de jouer et où les trois tableaux sont initialisés*/
    int secret[TAILLE_TAB];
    int test[TAILLE_TAB] = {9,9,9,9};
    int tour = 0;
    responseGen(secret);
    affiche(secret);
    while (tour!= 10)
    {    
        int saisie[TAILLE_TAB];
        saisir(saisie);
        printf("apres saisi\n");
        bla(test);
        
        printf("debut if\n");
        if (compare(secret,saisie,test))
        {
            printf("si win\n");
            printf("Vous avez trouvé le code secret en %d tours, bravo!\n",tour);
            printf("Le code secret: ");
            affiche(secret);
            printf("\n");
            printf("Votre code: ");
            affiche(saisie);
            printf("\n");
            break;
        }else{
            printf("apres compare\n");
            printf("-----------------|##| tour: %d\n",tour+1);
            printf("                 |");
            afficheP(test,0,2);
            printf("|\n");
            affiche(saisie);
            printf("             |");
            afficheP(test,2,4);
            printf("|\n");
            tour += 1;
            for (int i = 0; i < TAILLE_TAB; i++)
            {
                printf("lol");
                test[i] = 9;
                bla(test);
            }
        }
        
        printf("fin boucle\n"); 
    }
    if (tour==10)
    {
        printf("Vous avez atteint 10 tours, vous avez perdu, le code secret était: ");
        affiche(secret);
    }
    
    system("pause");
}