#ifndef CARD_H
#define CARD_H
#include <string>
namespace IA{


class Card
{
    public:
        Card(std::string *c, std::string *v);
        virtual ~Card();
        std::string* getColor() { return m_color; }
        void setColor(std::string* val) { m_color = val; }
        std::string* getValue() { return m_value; }
        void setValue(std::string* val) { m_value = val; }
    protected:
    private:
        std::string* m_color;
        std::string* m_value;
};
}
#endif // CARD_H
