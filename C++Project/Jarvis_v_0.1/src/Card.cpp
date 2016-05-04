#include "Card.h"

using namespace std;

Card::Card(int c, char v) : m_color(c),m_value(v)
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
