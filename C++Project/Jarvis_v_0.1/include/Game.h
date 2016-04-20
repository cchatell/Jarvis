#pragma once

#include "Hand.h"

class Game{
    public:
        Game();
        ~Game();
    private:
        void shuffle();

        Hand m_hands[4];
        int contract;
};
