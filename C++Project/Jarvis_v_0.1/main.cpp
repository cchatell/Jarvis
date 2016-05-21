
#include <iostream>
#include <fstream>
#include <cstdlib>
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
    /*
    int results[100];

    int i=1;
    double tot=0;
    for (i;i<101;i++){
     Game g;
    results[i]=g.launch();
    cout <<" partie numéro "<<i<<" :"<<results[i]<<endl;
    tot+=results[i];

    cout <<(tot/i)*100<<"%"<<endl;
    }
    */

    int nbParties=np; //voir Card.h
    int nbPartiesParCarte=npc; //voir Card.h
    int ecart=10;

    /*

    POUR TESTER LE POURCENTAGE DE VICTOIRE

  */
    for (nbPartiesParCarte;nbPartiesParCarte<5000000;nbPartiesParCarte+=ecart){
    double win = 0;
    for(int i = 1; i<nbParties; i++){
        Game g(nbPartiesParCarte);
        cout << g.toString()<<endl<<endl;
        int v=g.launchAndPrint();
        if (v){
            cout<<"L'IA remporte la partie!"<<endl;
            win++;
        }
        else cout <<"defaite..."<<endl;
        cout << "WINS : " << (win/i)*100 << "%, sur " << i << " parties pour "<< nbPartiesParCarte<<" partie/carte."<< endl;
    }
    cout <<"\n\n ECRITURE DANS RESULTS.TXT...\n\n";
    ofstream myfile;
    myfile.open("./results.txt",ios::app);
    myfile << "Pour "<<nbParties<<" parties, avec "<<nbPartiesParCarte<<" parties/carte dans MonteCarlo : \n" << (win/nbParties)*100 << "% de win.\n";
    myfile.close();
    }


    /*

    POUR AVOIR l'AFFICHAGE DE LA PARTIE

     Game g(nbPartiesParCarte);
        cout << g.toString()<<endl<<endl;
        int v=g.launchAndPrint();
        if (v){
            cout<<"L'IA remporte la partie!"<<endl;
        }
        else cout <<"defaite..."<<endl;

*/



    // 100 parties, Montecarlo 10000 : 70% de win
    // 100 parties, Montecarlo 1000 : 64% de win
    // 100 parties, Montecarlo 1000 : 63% de win
    // 100 parties, Montecarlo 1000 : 69% de win

    return 0;
}
