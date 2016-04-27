#pragma once

#include "Hand.h"

class Game{
    public:
        Game();
        Game(const Game &g);
        ~Game();
        std::string toString();
        Hand* getHand(int index);
        void setVerbose(int v);
    private:
        void shuffle();
        void init();

        int verbose;
        int m_turn;
        int m_currentPlayer;

        Hand* m_hands[4];
        int m_scores[4];
        int m_contract;
};
