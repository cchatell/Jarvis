#pragma once

#include <string>
#include <vector>
#include "Card.h"

class Hand
{
    public:
        Hand(int n,Card *c1, Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7, Card *c8);
        Hand();
        virtual ~Hand();
        void draw(Card* c);
        Card* discard(int index);
        Card* getCard(int index);
        std::string toString();
        int getNumber(){return m_number;};
    protected:
    private:
        std::vector<Card*> m_cards;
        int m_number;

};
