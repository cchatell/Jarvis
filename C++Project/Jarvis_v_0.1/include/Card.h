#ifndef CARD_H
#define CARD_H
#include <string>

class Card
{
    public:
        Card();
        Card(std::string *c, char *v);
        virtual ~Card();
        std::string* getColor() { return m_color; }
        void setColor(std::string* val) { m_color = val; }
        char* getValue() { return m_value; }
        void setValue(char* val) { m_value = val; }
        std::string toString(){return *(this->getColor())+" "+*(this->getValue());}
    protected:
    private:
        std::string* m_color;
        char* m_value;
};
#endif // CARD_H
