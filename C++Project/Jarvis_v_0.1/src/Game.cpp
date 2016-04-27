#include "Game.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

Game::Game(){
    Hand h1, h2, h3, h4;
    m_hands[0] = h1;
    m_hands[1] = h2;
    m_hands[2] = h3;
    m_hands[3] = h4;

    shuffle();
}

Game::~Game(){
}

void Game::shuffle(){
    vector<Card*> jeu(32);
    int i,j,c;
    srand(time(NULL));

    for (i=0;i<4;i++){
        for (j=0;j<8;j++){
            jeu[(i*8+j)]= const_cast<Card*>(&DECK[i][j]);
        }
    }

    for(i = 0; i<8; i++){
        for(j=0; j<4; j++){
            c = rand()%(32-(i*4)-j);
            m_hands[j].draw(jeu[c]);
            jeu.erase(jeu.begin()+c);
        }
    }

    m_contract = rand()%4;
}

string Game::toString(){
    ostringstream oss;

    oss << "Contract : " << COLORS[m_contract] << endl;
    oss << "Player 1" << endl << m_hands[0].toString() << endl;
    oss << "Player 2" << endl << m_hands[1].toString() << endl;
    oss << "Player 3" << endl << m_hands[2].toString() << endl;
    oss << "Player 4" << endl << m_hands[3].toString() << endl;

    return oss.str();
}
