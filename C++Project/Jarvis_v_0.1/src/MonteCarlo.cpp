#include "MonteCarlo.h"
#include <iostream>

using namespace std;
MonteCarlo::MonteCarlo(Game* g):m_game(g)
{
    //ctor
}

MonteCarlo::~MonteCarlo()
{
    //dtor
}

Card* MonteCarlo::launch(){
    int i=0;
    for (i=0;i<8;i++){
        cout << m_game->toString()<<endl;
       Game g1=*m_game;
        g1.getHand(0)->discard(0);
        cout << m_game->toString()<<endl;
        Card* cardToTest = g1.getHand(0)->getCard(i);

        return 0;
    }
}
