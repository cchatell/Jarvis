#pragma once

#include <string>
#include <vector>
#include "Card.h"

class Hand
{
    public:
        Hand(int n,Card *c1, Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7, Card *c8);
        Hand();
        Hand(int n);

        Hand(const Hand &h);

        virtual ~Hand();

        // adds c to m_cards
        void draw(Card* c);

        // removes the card #index from m_hands
        Card* discard(int index);

        // gets the card #index from m_hands (not deleted)
        Card* getCard (int index)const ;

        void setCards(std::vector<Card*> c){m_cards=c;};

        int getIndexFromCard(Card* c);

        std::vector<Card*> getCards() const {return m_cards;};

        std::string toString() const;

        int getType() const {return m_type;};

        void setType(int n){m_type=n;};

        Card* play(Card* board[], int size);

        Card* playRandom(Card* board[], int size);

        //Card* playMontecarlo(Card* board[]);

        int containsColor(int c);

        std::vector<int> getIndexFromColor(int color);
    protected:
    private:
        std::vector<Card*> m_cards;
        int m_type; // 0 : random, 1 : will play montecarlo
};


