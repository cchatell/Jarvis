#include "Game.h"

Game::Game(){
    Hand h1, h2, h3, h4;
    m_hands = {h1, h2, h3, h4};

    shuffle();
}

Game::shuffle(){
    Card jeu[32];
    Card c1;

    for (i=0;i<4;i++){
        for (j=0;j<8;j++){
            c1.setColor(i);
            c1.setValue(j);
            jeu[(i*8+j)]=c1;
        }
    }


}
