#include "Game.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

Game::Game() : verbose(0), m_turn(0), m_currentPlayer(0), m_firstPlayer(0)
{
    int i=0;
    while(i<4)
    {
        Hand h1(0);
        m_hands[i] = h1;
        m_scores[i++] = 0;
    }

    init();
}

Game::Game(const Game &g)
{
    verbose = g.verbose;
    m_turn = g.m_turn;
    m_currentPlayer = g.m_currentPlayer;
    m_contract = g.m_contract;
    int i =0;
    while(i<4)
    {
        m_scores[i] = g.m_scores[i];
        Hand h1=*(g.getConstHand(i));
        m_hands[i]= h1;
        i++;
    }
}

Game::~Game()
{
}

void Game::init()
{
    if(verbose)
        cout << "Très bien monsieur. Le ciel est dégagé." << endl;

    // On distribue les cartes
    shuffle();

    if(verbose) cout << "Pour cette partie les atouts seront les " << COLORS[m_contract] << ". Prenez place." << endl;
}

void Game::shuffle()
{
    vector<Card*> jeu(32);
    int i,j,c;
    srand(time(NULL));

    for (i=0; i<4; i++)
    {
        for (j=0; j<8; j++)
        {
            jeu[(i*8+j)]= const_cast<Card*>(&DECK[i][j]);
        }
    }

    for(i = 0; i<8; i++)
    {
        for(j=0; j<4; j++)
        {
            c = rand()%(32-(i*4)-j);
            m_hands[j].draw(jeu[c]);
            jeu.erase(jeu.begin()+c);
        }
    }

    m_contract = rand()%4;
}

string Game::toString()
{
    ostringstream oss;

    oss << "Contract : " << COLORS[m_contract] << endl;
    oss << "Player 1" << endl << m_hands[0].toString() << endl;
    oss << "Player 2" << endl << m_hands[1].toString() << endl;
    oss << "Player 3" << endl << m_hands[2].toString() << endl;
    oss << "Player 4" << endl << m_hands[3].toString() << endl;

    return oss.str();
}

const Hand* Game::getConstHand  (int index)const
{
    return (&(m_hands[index]));
}

Hand* Game::getHand(int index)
{
    return (&(m_hands[index]));
}

void Game::setVerbose(int v)
{
    verbose = v;
}

void Game::resetBoard()
{
    int i;
    for(i=0; i<4; i++)
    {
        board[i] = 0;
    }
}

int Game::launch()
{
    int turn, i, scorePli;
    int gagne;

    for(turn = 0; turn < 8; turn++)
    {
        m_turn = turn;
        resetBoard();

        m_currentPlayer = m_firstPlayer;
        // Chaque joueur joue
        for(player = 0; player<4; player++)
        {
            m_currentPlayer = (m_currentPlayer+1)%4;
            if(verbose) cout << "Joueur " << m_currentPlayer << ", a votre tour." << endl;
            board[player] = play();
        }

        // Calcul des points
        Card* currCard;
        scorePli = 0;
        int maxValue = -1, value, idWinner;
        bool contract = false;

        for(i = 0; i<4; i++)
        {
            currCard = board[i];
            if(currCard->getColor() == m_contract)  // si il y a une carte de l'atout
            {
                value = VALUES_CONTRACT[currCard->getValue()];
                scorePli += value;
                contract = true;

                if(maxValue < value)
                {
                    maxValue = value;
                    idWinner = i;
                }
            }
            else
            {
                value = VALUES[currCard->getValue()];
                scorePli += value;

                if(!contract && (maxValue < value))
                {
                    maxValue = value;
                    idWinner = i;
                }
            }
        }

        m_scores[idWinner] += scorePli;
        m_firstPlayer = idWinner;
    }

    for(i = 0; i<4; i++)
    {
        cout << i << " = " << m_scores[i] << endl;
    }

    // L'IA est le joueur 0
    // equipes 0,1 ; 2,3
    if(m_scores[0]+m_scores[1] > m_scores[2]+m_scores[3]) gagne = 1;
    else gagne = 0;

    return gagne;
}

Card* Game::play()
{
    if(m_hands[m_currentPlayer].getType() == 0) return playRandom();
}

Card* Game::playRandom()
{

    int colorAsked = board[0]->getColor();
    Hand* actualHand = &m_hands[m_currentPlayer];
    int* highestValue = highestValueBoard();
    if(board[0] == 0)  // si premier a jouer, on joue n'importe quelle carte
    {
        int i = GetRandNum(0,8-m_turn);
        return actualHand->discard(i);
    }
    else if(actualHand->containsColor(colorAsked))  // Si il a la bonne couleur, joue parmi celles ci (si atout, + haut, sinon n'imp)
    {
        // On récupère les index des cartes de la bonne couleur
        vector<int> index = actualHand->getIndexFromColor(colorAsked);
        vector<int> tmp;

        if(colorAsked==m_contract)
        {
            for(std::vector<int>::iterator it = index.begin(); it != index.end(); ++it)
            {
                if(actualHand->getCard(*it)->valueContract() > highestValue[1]) tmp.push_back(*it);
            }
            if(tmp.size() != 0) index = tmp;
        }
        return actualHand->discard(index[GetRandNum(0,index.size())]);
    }
    else
    {
        //sinon
        //si pas maitre, et a de l'atout,
        // pose l'atout forcément plus haut si il y a déjà un atout sinon atout plus bas

        if (actualHand->containsColor(m_contract)){ // si il a de l'atout
            if(player == 1 || !(highestValue[0] == player-2)){ // pas maitre
                vector<int> index = actualHand->getIndexFromColor(m_contract);
                vector<int> tmp;
                for(std::vector<int>::iterator it = index.begin(); it != index.end(); ++it)
                {
                    if(actualHand->getCard(*it)->valueContract() > highestValue[1]) tmp.push_back(*it);
                }
                if(tmp.size() != 0) index = tmp;
                return actualHand->discard(index[GetRandNum(0,index.size())]);
            }
            else{ // maitre
                vector<int> tmp;
                Card* c;
                int trouve = 0;
                for(int i = 0; i <8-m_turn; ++i)
                {
                    c = actualHand->getCard(i);
                    if(c->getColor() != m_contract || (c->getColor() == m_contract && c->valueContract() > highestValue[1])){
                        tmp.push_back(i);
                        if(c->getColor() == m_contract && c->valueContract() > highestValue[1]) trouve = 1;
                    }
                }

                if(trouve){
                    return actualHand->discard(tmp[GetRandNum(0,tmp.size())]);
                }
                else{
                    return actualHand->discard(GetRandNum(0,8-m_turn));
                }
            }
        }
        else{ //IL A PAS D'ATOUT
            int i = GetRandNum(0,8-m_turn);
            return actualHand->discard(i);
        }//sinon pose n'imp, sauf les atouts moins forts
    }
}

// Le numero du joueur maitre du pli
int Game::master()
{
    int* val = highestValueBoard();
    return (m_firstPlayer+val[0])%4;
}

int* Game::highestValueBoard()
{
    int ret[2]; // 0: index, 1: valeur
    ret[0] = -1;
    ret[1] = -1;
    int cont = 0;
    for(int i = 0; i < player; i++)
    {
        if(m_contract != board[i]->getColor() && board[i]->getColor() == board[0]->getColor())  // Si pas de la couleur de l'atout et de la couleur demandée
        {
            if(!cont && ret[1] < board[i]->value())  // si pas encore d'atout, et valeur plus grande
            {
                ret[1] = board[i]->value(); // c'est le max
                ret[0] = i;
            }
        }
        else if(m_contract == board[i]->getColor())  // sinon (couleur = atout)
        {
            if(!cont)  // si c'est le premier atout, c'est le max
            {
                ret[1] = board[i]->valueContract();
                cont = 1;
                ret[0] = i;
            }
            else if(ret[1] < board[i]->valueContract())  // sinon, si la valeur est plus grande, c'est le max
            {
                ret[1] = board[i]->valueContract();
                ret[0] = i;
            }
        }
    }
    return ret;
}

int Game::GetRandNum(int min, int max)
{
    return (min + rand() %(max - min + 1));
}
