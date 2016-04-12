#include <iostream>
#include "Card.h"
#include "Hand.h"
using namespace std;

int main()
{
    cout << "Bonjour M. Stark, en quoi puis-je vous aider ?" << endl<<endl;

    //famille
    string  color[4];
    enum{HEARTS,DIAMONDS,CLUBS,SPADES};
    color[0]="HEARTS"; //coeur
    color[1]="DIAMONDS"; //carreau
    color[2]="CLUBS"; //trèfle
    color[3]="SPADES"; //pique

    //valeur
    enum{ACE,TEN,KING,QUEEN,JACK,NINE,EIGHT,SEVEN};
    char value[8];
    value[0]='A'; //As
    value[1]='D';  //10
    value[2]='K';//roi
    value[3]='Q'; //dame
    value[4]='J'; //valet
    value[5]='9';
    value[6]='8';
    value[7]='7';

    //exemples de cartes
   Card as_trefle(&color[CLUBS],&value[ACE]);
   Card roi_carreau(&color[DIAMONDS],&value[KING]);
   Card neuf_pique(&color[SPADES],&value[NINE]);
   Card huit_pique(&color[SPADES],&value[EIGHT]);
   Card valet_trefle(&color[CLUBS],&value[JACK]);
   Card dame_trefle(&color[CLUBS],&value[QUEEN]);
   Card sept_trefle(&color[CLUBS],&value[SEVEN]);
   Card dix_trefle(&color[CLUBS],&value[TEN]);

    //exemple de main
   Hand h1(&as_trefle,&roi_carreau,&neuf_pique,&huit_pique,&valet_trefle,&dame_trefle,&sept_trefle,&dix_trefle);
    cout << "carte exemple as_trefle : " << as_trefle.toString()<<endl<<endl;
    cout << "main exemple h1 : " << h1.toString()<<endl<<endl;


    //génération d'un jeu de carte
    Card jeu[32];
    Hand familles[4];
    Card famille[8];

    int i;
    int j;
    cout << "familles de cartes generees"<<endl;
    for (i=0;i<4;i++){
    Card c1;
        for (j=0;j<8;j++){
            c1.setColor(&color[i]);
            c1.setValue(&value[j]);
            famille[j]=c1;
            jeu[(i*8+j)]=c1;
        }
         Hand h1(&famille[0],&famille[1],&famille[2],&famille[3],&famille[4],&famille[5],&famille[6],&famille[7]);
         familles[i]=h1;
        cout<< h1.toString()<<endl<<endl;
    }
    cout << "Jeu entier genere"<<endl;
    for (i=0; i<32;i++){
        cout << jeu[i].toString()<<endl;
    }


    return 0;
}
