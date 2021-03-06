
#pragma once
#define np 100
#define npc 100000
#include <string>

enum{HEART,DIAMOND,CLUB,SPADE};
const std::string COLORS[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};

enum{ACE,TEN,KING,QUEEN,JACK,NINE,EIGHT,SEVEN};
const std::string NAMES[8] = {"Ace of ", "10 of ", "King of ", "Queen of ", "Jack of ", "9 of ", "8 of ", "7 of "};
const int VALUES[8] = {11, 10, 4, 3, 2, 0, 0, 0};
const int VALUES_CONTRACT[8] = {11, 10, 4, 3, 20, 14, 0, 0};

class Card
{
    public:
    bool equals(const Card &h);
        Card();
        Card(int c, int v);
        virtual ~Card();
        int getColor() const { return m_color; }
        void setColor(int val) { m_color = val; }
        int getValue() const{ return m_value; }
        int value(){ return VALUES[m_value];}
        int valueContract(){ return VALUES_CONTRACT[m_value];}
        void setValue(int val) { m_value = val; }
        bool operator< (const Card& rhs){ return (this->getValue()<rhs.getValue() && this->getColor()<rhs.getColor());}
        Card(const Card &c);
        std::string toString()const {return (NAMES[m_value]+COLORS[m_color]);}
    protected:
    private:
        int m_color;
        int m_value;
};

const Card DECK[4][8] = {{Card(HEART, ACE), Card(HEART, TEN), Card(HEART, KING), Card(HEART, QUEEN),
                    Card(HEART, JACK),Card(HEART, NINE),Card(HEART, EIGHT),Card(HEART, SEVEN)},
                    {Card(DIAMOND, ACE), Card(DIAMOND, TEN), Card(DIAMOND, KING), Card(DIAMOND, QUEEN),
                    Card(DIAMOND, JACK),Card(DIAMOND, NINE),Card(DIAMOND, EIGHT),Card(DIAMOND, SEVEN)},
                    {Card(CLUB, ACE), Card(CLUB, TEN), Card(CLUB, KING), Card(CLUB, QUEEN),
                    Card(CLUB, JACK),Card(CLUB, NINE),Card(CLUB, EIGHT),Card(CLUB, SEVEN)},
                    {Card(SPADE, ACE), Card(SPADE, TEN), Card(SPADE, KING), Card(SPADE, QUEEN),
                    Card(SPADE, JACK),Card(SPADE, NINE),Card(SPADE, EIGHT),Card(SPADE, SEVEN)}};
