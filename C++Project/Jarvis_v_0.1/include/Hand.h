#pragma once

#include <string>
#include <vector>
#include "Card.h"

class Hand
{
    public:
        Hand(int n,Card *c1, Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7, Card *c8);
        Hand();

        Hand(const Hand &h);

        virtual ~Hand();

        // adds c to m_cards
        void draw(Card* c);

        // removes the card #index from m_hands
        Card* discard(int index);

        // gets the card #index from m_hands (not deleted)
        Card* getCard (int index)const ;

        void setCards(std::vector<Card*> c){m_cards=c;};

        std::vector<Card*> getCards() const {return m_cards;};

        std::string toString() const;

        int getNumber() const {return m_number;};

        void setNumber(int n){m_number=n;};

        virtual Card* play(){ return 0;};

    protected:
    private:
        std::vector<Card*> m_cards;
        int m_number;

};

class IA_random : public Hand
{
    public:
        IA_random(int n,Card *c1, Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7, Card *c8);
        IA_random();
        IA_random(const IA_random &i);
        Card* play();
};
