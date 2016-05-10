#include "Game.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>


using namespace std;

Game::Game() : verbose(0), m_turn(0), m_currentPlayer(0), m_firstPlayer(0)
{
    int i=0;
    while(i<4){
        Hand h1(0);
        m_hands[i] = h1;
        m_scores[i++] = 0;
    }

    init();
}

Game::Game(const Game &g){
    verbose = g.verbose;
    m_turn = g.m_turn;
    m_currentPlayer = g.m_currentPlayer;
    m_contract = g.m_contract;
    int i =0;
    while(i<4){
        m_scores[i] = g.m_scores[i];
        Hand h1=*(g.getConstHand(i));
        m_hands[i]= h1;
        i++;
    }
}

Game::~Game(){
}

void Game::init(){
    if(verbose)
        cout << "Très bien monsieur. Le ciel est dégagé." << endl;

    // On distribue les cartes
    shuffle();

    if(verbose) cout << "Pour cette partie les atouts seront les " << COLORS[m_contract] << ". Prenez place." << endl;
}

void Game::shuffle(){
    vector<Card*> jeu(32);
    int i,j,c;
    srand(time(NULL));

    for (i=0;i<4;i++){
        for (j=0;j<8;j++){
            jeu[(i*8+j)]= const_cast<Card*>(&DECK[i][j]);
        }
    }

    for(i = 0; i<8; i++){
        for(j=0; j<4; j++){
            c = rand()%(32-(i*4)-j);
            m_hands[j].draw(jeu[c]);
            jeu.erase(jeu.begin()+c);
        }
    }

    m_contract = rand()%4;
}

string Game::toString(){
    ostringstream oss;

    oss << "Contract : " << COLORS[m_contract] << endl;
    oss << "Player 1" << endl << m_hands[0].toString() << endl;
    oss << "Player 2" << endl << m_hands[1].toString() << endl;
    oss << "Player 3" << endl << m_hands[2].toString() << endl;
    oss << "Player 4" << endl << m_hands[3].toString() << endl;

    return oss.str();
}

const Hand* Game::getConstHand  (int index)const{
    return (&(m_hands[index]));
}

Hand* Game::getHand(int index){
    return (&(m_hands[index]));
}

void Game::setVerbose(int v){
    verbose = v;
}

void Game::resetBoard(){
    int i;
    for(i=0;i<4;i++){
        board[i] = 0;
    }
}

int Game::launch(){
    int turn, i, scorePli;
    int gagne;

    for(turn = 0; turn < 8; turn++){
        m_turn = turn;
        resetBoard();

        m_currentPlayer = m_firstPlayer;
        // Chaque joueur joue
        for(player = 0; player<4; player++){
            m_currentPlayer = (m_currentPlayer+1)%4;
            if(verbose) cout << "Joueur " << player << ", a votre tour." << endl;
            board[player] = play();
        }

        // Calcul des points
        Card* currCard;
        scorePli = 0;
        int maxValue = -1, value, idWinner;
        bool contract = false;

        for(i = 0; i<4; i++){
            currCard = board[i];
            if(currCard->getColor() == m_contract){ // si il y a une carte de l'atout
                value = VALUES_CONTRACT[currCard->getValue()];
                scorePli += value;
                contract = true;

                if(maxValue < value){
                    maxValue = value;
                    idWinner = i;
                }
            }
            else{
                value = VALUES[currCard->getValue()];
                scorePli += value;

                if(!contract && (maxValue < value)){
                    maxValue = value;
                    idWinner = i;
                }
            }
        }

        m_scores[idWinner] += scorePli;
        m_firstPlayer = idWinner;
    }

    for(i = 0; i<4; i++){
        cout << i << " = " << m_scores[i] << endl;
    }

    // L'IA est le joueur 0
    // equipes 0,1 ; 2,3
    if(m_scores[0]+m_scores[1] > m_scores[2]+m_scores[3]) gagne = 1;
    else gagne = 0;

    return gagne;
}

Card* Game::play(){
    if(m_hands[m_currentPlayer].getType() == 0) return playRandom();
}

Card* Game::playRandom(){

    /*
    si l'équipe du joueur qui joue est maitre
        si il a une carte de la famille demandée par la première carte
            il joue une carte de cette famille
        sinon
            n'importe quelle autre carte
    sinon
        si il a pas une carte de la famille demandée par la première carte
            si il a de l'atout
                il joue de l'atout
            sinon
                il jour n'importe quelle carte
        sinon
            il joue une carte de cette famille

    */
    if(m_currentPlayer == 0){
        Card* ret = m_hands[m_currentPlayer].discard(GetRandNum(0, 8-m_turn));
        return ret;
    }  // si pas de carte on joue n'importe la quelle
    else{
        int color = board[0]->getColor();


    }
}

int Game::isMaster(){
    // si il y a de l'atout, c'est celui qui à posé la plus grosse d'atout qui gagne

    // sinon
        //c'est celui qui a la plus grosse carte de la famille demandée par la première carte
}

int Game::GetRandNum(int min, int max){
    return (min + rand() %(max - min + 1));
}
