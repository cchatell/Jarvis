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

Card* MonteCarlo::launch()
{
    int i=0;
    for (i=0; i<8; i++)
    {
        Game g1=*(m_game);
        Card* cardToTest = g1.getHand(0)->getCard(i);
        return 0;
    }
}
