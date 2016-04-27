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

        // adds c to m_cards
        void draw(Card* c);

        // removes the card #index from m_hands
        Card* discard(int index);

        // gets the card #index from m_hands (not deleted)
        Card* getCard(int index);

        std::string toString();

        int getNumber(){return m_number;};

        virtual Card* play()=0;
    protected:
    private:
        std::vector<Card*> m_cards;
        int m_number;

};

class Ultron : Hand
{
    public:
        virtual Card* play();
};

class IA_random : Hand
{
    public:
        virtual Card* play();
};
