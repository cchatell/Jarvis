#pragma once

#include "Hand.h"

class Game{
    public:
        Game();
        ~Game();
        std::string toString();
    private:
        void shuffle();

        Hand m_hands[4];
        int m_contract;
};
