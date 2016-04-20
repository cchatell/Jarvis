#ifndef CARD_H
#define CARD_H

#include "Global.h"

class Card
{
    public:
        Card();
        Card(int c, char v);
        virtual ~Card();
        int getColor() { return m_color; }
        void setColor(int val) { m_color = val; }
        char getValue() { return m_value; }
        void setValue(char val) { m_value = val; }
        std::string toString(){return COLORS[m_color]+" "+VALUES[m_value];}
    protected:
    private:
        int m_color;
        int m_value;
};
#endif // CARD_H
