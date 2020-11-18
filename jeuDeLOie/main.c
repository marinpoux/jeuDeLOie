#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//CONSTANTES
#define DEPART 0    //case d�part
#define ARRIVEE 66  //case ariv�e
#define MORT 58     //case retour d�part
#define OIE 9       //multiple des cases 'Oie'

#define DES_MIN 1   //valeur minimale d'un de
#define DES_MAX 6   //valeur maximale d'un de
#define DES_NB 2    //nombre de d�s

//DEFINITION + REGLES
//jeu de l'oie
//nb de places : 0 � 66 = 67 places
//jet de 2 d�s --> somme = 2 � 12
//d�part : 0
//arriv�e : 66
//tombe sur 66 : fini
    //sinon : recule
//oie toutes les 9 cases sauf 63 (9,18,27,36,45,54) --> d�placement*2
//tete de mort en 58 --> retour d�part


//prototypes
int partie(int casePion);
int lanceDes();
int nbRand();
int majPlateau(int casePion, int sommeDes);
int casesEffets(int casePion, int sommeDes);


int main()
{
    int casePion=DEPART;    //initialisation de la position du joueur

    printf("JEU DE L'OIE\nParvenez a atteindre la case %d du plateau !\n", ARRIVEE);

    //initialisation de la g�n�ration de nombres al�atoires
    srand(time(NULL));


    while(casePion != ARRIVEE) {
        //r�p�tition de la boucla tant que l'arriv�e n'est pas atteinte

        fflush;

        casePion = partie(casePion);
    }

    return 0;
}


int partie(int casePion) {
    //un tour complet : lanc� de d�s, annonce de la somme, case obtenue, effet �ventuel
    //entree: un entier (case sur laquelle se trouve le pion)
    //sortie: un entier (nouvelle case)
    int sommeDes = 0;
    char ok = "";

    printf("Appuyez sur ENTREE pour lancer les des !\n");
    scanf("%c", &ok);
    sommeDes = lanceDes();  //lanc� des d�s

    casePion = majPlateau(casePion, sommeDes);  //d�placement du pion

    casePion = casesEffets(casePion, sommeDes); //detection des cases sp�ciales

    return casePion;
}


int majPlateau(int casePion, int sommeDes){
    //mise � jour de la position du pion sur le plateau
    //entree: deux entiers (la case actuelle du pion, le nombre lanc� aux d�s)
    //sortie: un entier: la nouvelle case du pion
    int newCase = casePion + sommeDes;
    int surplus = 0;

    if (newCase > ARRIVEE) {
        //gestion du d�passement de la case d'arrivee

        surplus = newCase - ARRIVEE;
        newCase = ARRIVEE - surplus;

        printf("Vous etes alle au-dela de la case d'arrivee !\nVous reculez donc de %d depuis l'arrivee...\n", surplus);
    }

    printf("Vous avez atterri sur la case %d\n", newCase);

    return newCase;
}


int casesEffets(int casePion, int sommeDes) {
    //detection des cases a effet special
    //entree: deux entiers (nouvelle case du joueur, nombre lance aux des)
    //sortie: un entier (case du joueur, eventuellement modifiee)

    if (casePion == ARRIVEE) {       //case d'arrivee
        printf("VICTOIRE !!\n");
    }
    else if (casePion == MORT) {  //case tete de mort
        printf("Oh non, c'est la case 'Mort' !! Vous retournez a la case de depart !!\n");

        casePion = DEPART;
    }
    else if ((casePion % OIE == 0) && (casePion < (ARRIVEE-OIE))) {    //case oie
        casePion += sommeDes;                                       //multiple de 9 MAIS inferieur � arrivee-9

        printf("C'est une case 'Oie', votre deplacement est double!\nVous avancez donc en case %d\n", casePion);
    }

    return casePion;
}


int lanceDes() {
    //autant de lanc�s que de d�s, et addition des lanc�s obtenus
    //sortie: un entier (somme des d�s)

    int randTemp = 0, iTemp = 0, sommeDes = 0;

    //lance autant de fois que le nombre de d�s
    for (iTemp=0; iTemp<DES_NB; iTemp++) {

        randTemp = nbRand();
        sommeDes += randTemp;
    }

    printf("Vous avez lance un %d !\n", sommeDes);

    return sommeDes;
}

int nbRand(){
    //generation d'un nombre aleatoire entre 1 et 6
    //sortie: un entier (d� lanc�)

    int nbTemp = rand()%DES_MAX+DES_MIN;

    printf("nb genere : %d\n", nbTemp);

    return nbTemp;
}


