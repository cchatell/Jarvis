#pragma once

#include "Hand.h"

class Game{
    public:
        Game();
        Game(const Game &g);
        ~Game();
        std::string toString();
       const Hand* getConstHand  (int index)const;
        Hand* getHand  (int index);
        void setVerbose(int v);

        int play();
    private:
        void shuffle();
        void init();
        void resetBoard();

        int verbose;
        int m_turn;
        int m_currentPlayer;

        Hand m_hands[4];
        Card* board[4];
        int m_scores[4];
        int m_contract;
};
