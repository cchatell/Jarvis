#include <iostream>

#include "Game.h"
using namespace std;

int main()
{
    cout << "Bonjour M. Stark, en quoi puis-je vous aider ?" << endl<<endl;

    //exemples de cartes
    /*Card as_trefle(CLUB,ACE);
    Card roi_carreau(DIAMOND,KING);
    Card neuf_pique(SPADE,NINE);
    Card huit_pique(SPADE,EIGHT);
    Card valet_trefle(CLUB,JACK);
    Card dame_trefle(CLUB,QUEEN);
    Card sept_trefle(CLUB,SEVEN);
    Card dix_trefle(CLUB,TEN);

    //exemple de main
    Hand h1(0,&as_trefle,&roi_carreau,&neuf_pique,&huit_pique,&valet_trefle,&dame_trefle,&sept_trefle,&dix_trefle);
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
            c1.setColor(i);
            c1.setValue(j);
            famille[j]=c1;
            jeu[(i*8+j)]=c1;
        }
         Hand h1(0,&famille[0],&famille[1],&famille[2],&famille[3],&famille[4],&famille[5],&famille[6],&famille[7]);
         familles[i]=h1;
        cout<< h1.toString()<<endl<<endl;
    }
    cout << "Jeu entier genere"<<endl;
    for (i=0; i<32;i++){
        cout << jeu[i].toString()<<endl;
    }*/

    Game g;

    cout << g.toString() << endl;

    //g.getHand(0)->discard(1);

    //cout << g.toString() << endl;

    return 0;
}
