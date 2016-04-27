#pragma once

#include "Hand.h"

class Game{
    public:
        Game();
        ~Game();
        std::string toString();
        Hand* getHand(int index);

        void start();
    private:
        void shuffle();

        Hand* m_hands[4];
        int m_scores[4];
        int m_contract;
};
