#include "Hand.h"

Hand::Hand(Card *c1, Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7, Card *c8)
{

    this->cards.push_back(c1);
    this->cards.push_back(c2);
    this->cards.push_back(c3);
    this->cards.push_back(c4);
    this->cards.push_back(c5);
    this->cards.push_back(c6);
    this->cards.push_back(c7);
    this->cards.push_back(c8);
}

Hand::Hand()
{
}

std::string Hand::toString(){
    int i;
    std::string s1;
    for (i=0;i<8;i++){
        s1+=(cards[i]->toString())+="; ";
    }
    return s1;
}
Hand::~Hand()
{
}
