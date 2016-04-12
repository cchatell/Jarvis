
#ifndef HAND_H
#define HAND_H
#include <string>
#include "Card.h"
class Hand
{
    public:
            Hand(Card *c1, Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7, Card *c8);
             std::string toString();
             Hand();
        virtual ~Hand();
    protected:
    private:
        Card* cards[8];

};

#endif // HAND_H
