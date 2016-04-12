#include "Hand.h"

Hand::Hand(Card *c1, Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7, Card *c8)
{

    this->cards[0]=c1;
    this->cards[1]=c2;
    this->cards[2]=c3;
    this->cards[3]=c4;
    this->cards[4]=c5;
    this->cards[5]=c6;
    this->cards[6]=c7;
    this->cards[7]=c8;
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
    //dtor
}
