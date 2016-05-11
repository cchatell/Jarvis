#include "Ultron.h"
#include <iostream>
#include <ctime>

using namespace std;

Hand::Hand(int n,Card *c1, Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7, Card *c8): m_type(n)
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

Hand::Hand(int n) : m_type(n)
{
}

Hand::Hand(const Hand &h)
{
    m_type = h.m_type;
    vector<Card*> new_(h.m_cards);
    m_cards = new_;
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

Card* Hand::getCard(int index)const {
    return m_cards[index];
}

string Hand::toString()const{
    unsigned int i;
    string s1("");
    for (i=0;i<m_cards.size();i++){
        s1 += (m_cards[i]->toString()+"; ");
    }

    if (s1 == "") s1 = "Rien";
    return s1;
}

int Hand::containsColor(int c){
    int i, ret = 0;
    for (i=0;i<m_cards.size();i++){
        if(m_cards[i]->getColor() == c) ret = 1;
    }

    return ret;
}

vector<int> Hand::getIndexFromColor(int color){
    vector<int> res;
    int i;
    for ( i = 0 ; i<8 ; i++){
        if (m_cards[i]->getColor()==color){
            res.push_back(i);
        }
    }
    return res;

}


