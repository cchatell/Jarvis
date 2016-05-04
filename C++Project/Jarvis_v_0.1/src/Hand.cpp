#include "Ultron.h"


using namespace std;

Hand::Hand(int n,Card *c1, Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7, Card *c8): m_number(n)
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

Hand::Hand(const Hand &h)
{
    m_number = h.m_number;
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

Card* Hand::play(){
}

string Hand::toString(){
    unsigned int i;
    string s1("");
    for (i=0;i<m_cards.size();i++){
        s1 += (m_cards[i]->toString()+"; ");
    }

    if (s1 == "") s1 = "Rien";
    return s1;
}

Card* Ultron::play(){
    return 0;
}

IA_random::IA_random(int n,Card *c1, Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7, Card *c8):
        Hand(n,c1, c2, c3,c4,c5,c6,c7,c8)
{

}

IA_random::IA_random(){

}

IA_random::IA_random(const IA_random &i)
{
    setNumber(i.getNumber());
    vector<Card*> new_(i.getCards());
    setCards(new_);
}


Card* IA_random::play(){
    return 0;
}
