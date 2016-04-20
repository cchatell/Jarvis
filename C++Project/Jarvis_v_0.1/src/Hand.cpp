#include "Hand.h"

using namespace std;

Hand::Hand(Card *c1, Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7, Card *c8)
{

    this->m_cards.push_back(c1);
    this->m_cards.push_back(c2);
    this->m_cards.push_back(c3);
    this->m_cards.push_back(c4);
    this->m_cards.push_back(c5);
    this->m_cards.push_back(c6);
    this->m_cards.push_back(c7);
    this->m_cards.push_back(c8);
}

Hand::Hand()
{
}

Hand::~Hand()
{
}

void Hand::draw(Card* c){
    m_cards.push_back(c);
}

Card* Hand::discard(int index){
    Card* c = m_cards[index];
    m_cards.erase(m_cards.begin()+index);
    return c;
}

Card* Hand::getCard(int index){
    return m_cards[index];
}

string Hand::toString(){
    int i;
    string s1;
    for (i=0;i<8;i++){
        s1+=(m_cards[i]->toString())+="; ";
    }
    return s1;
}
