#include "Card.h"

using namespace std;

Card::Card(int c, int v) : m_color(c),m_value(v)
{
}
Card::Card()
{
}
Card::~Card()
{
}

Card::Card(const Card &c){
    m_color=c.getColor();
    m_value=c.getValue();
}

bool Card::equals(Card const& b){
    return (getColor()==b.getColor() && getValue()==b.getValue());
 }
