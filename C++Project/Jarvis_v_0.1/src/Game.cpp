#include "Game.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <pthread.h>
#include <unistd.h>
#include <map>

using namespace std;

Game::Game() : verbose(0), m_turn(0), m_currentPlayer(0), m_firstPlayer(0), player(0)
{

    Hand h1(1);
    Hand h2(0);
    Hand h3(1);
    Hand h4(0);
    m_hands[0]=h1;
    m_hands[1]=h2;
    m_hands[2]=h3;
    m_hands[3]=h4;

    int i=0;
    while(i<4)
    {
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
    m_firstPlayer=g.getFirstPlayer();
    player=g.getPlayer();
    int i =0;
    while(i<4)
    {
        board[i]=g.board[i];
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

    resetBoard();
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
    int turn = m_turn, i, scorePli;
    int gagne;

    for(turn; turn < 8; turn++)
    {
        m_turn = turn;


        // Chaque joueur joue
        for(player; player<4; player++)
        {
            Card* c = play();
            board[player]=c;
            m_currentPlayer = (m_currentPlayer+1)%4;
        }

        player = 0;

        // Calcul des points
        Card* currCard;
        scorePli = 0;
        int maxValue = -1, value, idWinner;
        bool contract = false;

        for(i = 0; i<4; i++)
        {
            currCard = board[i];
            if(currCard->getColor() == m_contract && !contract)  // si c'est une carte d'atout mais qu'il n'y en a pas encore eu alors elle gagne
            {
                value = VALUES_CONTRACT[currCard->getValue()];
                scorePli += value;
                contract = true;
                maxValue = value;
                idWinner = (m_firstPlayer+i)%4;
            }
            else if (currCard->getColor() == m_contract && contract){// si c'est une carte d'atout et qu'il y en déjà eu on fait le max
                value = VALUES_CONTRACT[currCard->getValue()];
                scorePli += value;
                contract = true;

                if(maxValue < value)
                {
                    maxValue = value;
                    idWinner = (m_firstPlayer+i)%4;

                }
            }else
            {
                value = VALUES[currCard->getValue()];
                scorePli += value;

                if(!contract && (maxValue < value))
                {
                    maxValue = value;
                    idWinner =(m_firstPlayer+i)%4;;
                }
            }
        }

        //10 de der: le dernier pli à 10 points de plus
        if (turn ==7) scorePli+=10;
        m_scores[idWinner] += scorePli;

        m_firstPlayer = idWinner;

        m_currentPlayer = m_firstPlayer;
        resetBoard();
    }

    // L'IA est le joueur 0
    // equipes 0,2 ; 1,3
    if(m_scores[0]+m_scores[2] > m_scores[1]+m_scores[3]) gagne = 1;
    else gagne = 0;

    return gagne;
}

int Game::launchAndPrint()
{
    int turn = m_turn, i, scorePli;
    int gagne;

    for(turn; turn < 8; turn++)
    {
        m_turn = turn;


        // Chaque joueur joue
        for(player; player<4; player++)
        {
            Card* c = play();
            board[player]=c;
            cout<<"Joueur : " << m_currentPlayer<< " joue la carte "<<c->toString()<<endl;
            m_currentPlayer = (m_currentPlayer+1)%4;
        }
        cout <<endl <<endl <<"Fin "<<turn+1<<" tour"<<endl;
        player = 0;

        // Calcul des points
        Card* currCard;
        scorePli = 0;
        int maxValue = -1, value, idWinner;
        bool contract = false;

        for(i = 0; i<4; i++)
        {
            currCard = board[i];
            if(currCard->getColor() == m_contract && !contract)  // si c'est une carte d'atout mais qu'il n'y en a pas encore eu alors elle gagne
            {
                value = VALUES_CONTRACT[currCard->getValue()];
                scorePli += value;
                contract = true;
                maxValue = value;
                idWinner = (m_firstPlayer+i)%4;
            }
            else if (currCard->getColor() == m_contract && contract){// si c'est une carte d'atout et qu'il y en déjà eu on fait le max
                value = VALUES_CONTRACT[currCard->getValue()];
                scorePli += value;
                contract = true;

                if(maxValue < value)
                {
                    maxValue = value;
                    idWinner = (m_firstPlayer+i)%4;

                }
            }else
            {
                value = VALUES[currCard->getValue()];
                scorePli += value;

                if(!contract && (maxValue < value))
                {
                    maxValue = value;
                    idWinner =(m_firstPlayer+i)%4;;
                }
            }
        }

        //10 de der: le dernier pli à 10 points de plus
        if (turn ==7) scorePli+=10;
        m_scores[idWinner] += scorePli;

        m_firstPlayer = idWinner;
        cout<< "le Joueur "<<idWinner<<" remporte le pli contenant "<<scorePli<<" points "<<endl<<endl;
        m_currentPlayer = m_firstPlayer;
        resetBoard();
    }

    for(i = 0; i<4; i++)
    {
        cout << i << " = " << m_scores[i] << endl;
    }

    // L'IA est le joueur 0
    // equipes 0,2 ; 1,3
    if(m_scores[0]+m_scores[2] > m_scores[1]+m_scores[3]) gagne = 1;
    else gagne = 0;

    return gagne;
}


Card* Game::play()
{
    if(m_hands[m_currentPlayer].getType() == 0) return playRandom();
    else if(m_hands[m_currentPlayer].getType() == 1) return playMontecarlo();
}

Card* Game::playMontecarlo()
{
    Card* c= MonteCarlo_launch(this, m_turn);
    int index=getHand(m_currentPlayer)->getIndexFromCard(c);
    return getHand(m_currentPlayer)->discard(index);
}

int Game::playCard(int index)
{

    Hand* actualHand = &m_hands[m_currentPlayer];
    //cout << this->toString() << endl;
    board[player] = actualHand->discard(index);
    //cout << "carte teste"
    //joueur suivant
    player++;

    actualHand->setType(0);
    m_hands[(m_currentPlayer+2)%4].setType(0);

    m_currentPlayer = (m_currentPlayer+1)%4;
    return launch();
}

Card* Game::playRandom()
{
    Hand* actualHand = &m_hands[m_currentPlayer];
    vector<int> index(playableCardsIndex());

    try{
        int toPlay = GetRandNum((int)index.size());
        return actualHand->discard(index[toPlay]);
    }
    catch(std::exception const& e)
    {
        cout << "index : " << index.size() << endl;
        cerr << "ERREUR : " << e.what() << endl;
    }
}

vector<int> Game::playableCardsIndex()
{
    Hand* actualHand = &m_hands[m_currentPlayer];

    // n'importe quelle carte de la main;
    int a;
    vector<int> i;
    vector<Card*> v = actualHand->getCards();
    for(a=0; a<v.size();a++)
    {
        i.push_back(a);
    }


    if(board[0] == 0)  // si premier a jouer, on joue n'importe quelle carte
    {
        return i;
    }
    else
    {
        int colorAsked = board[0]->getColor();
        int* highestValue = highestValueBoard();

        if(actualHand->containsColor(colorAsked))  // Si il a la bonne couleur, joue parmi celles ci (si atout, + haut, sinon n'imp)
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

            return index;
        }
        else
        {
            //sinon
            //si pas maitre, et a de l'atout,
            // pose l'atout forcément plus haut si il y a déjà un atout sinon atout plus bas

            if (actualHand->containsColor(m_contract))  // si il a de l'atout
            {
                if(player == 1 || !(highestValue[0] == player-2))  // pas maitre
                {
                    vector<int> index = actualHand->getIndexFromColor(m_contract);
                    vector<int> tmp;
                    for(std::vector<int>::iterator it = index.begin(); it != index.end(); ++it)
                    {
                        if(actualHand->getCard(*it)->valueContract() > highestValue[1]) tmp.push_back(*it);
                    }
                    if(tmp.size() != 0) index = tmp;
                    return index;
                }
                else  // maitre
                {
                    vector<int> tmp;
                    Card* c;
                    int trouve = 0;
                    for(int i = 0; i <8-m_turn; ++i)
                    {
                        c = actualHand->getCard(i);
                        if(c->getColor() != m_contract || (c->getColor() == m_contract && c->valueContract() > highestValue[1]))
                        {
                            tmp.push_back(i);
                            if(c->getColor() == m_contract && c->valueContract() > highestValue[1]) trouve = 1;
                        }
                    }

                    if(trouve)
                    {
                        return tmp;
                    }
                    else
                    {
                        return i;//on joue nimp
                    }
                }
            }
            else  //IL A PAS D'ATOUT
            {
                return i; //on joue nimp
            }//sinon pose n'imp, sauf les atouts moins forts
        }
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

int Game::GetRandNum(int max)
{
    return (rand()%max);
}

//scores
map<const Card*,std::vector<int> > scores;

struct thread_arg
{
    Card* cardToTest;
    Game* g;
    int index;
};


void* do_loop(void* data)
{
    int i;
    //MonteCarlo pour 100 parties
    struct thread_arg *args = (struct thread_arg *)data;
    Game originalGame=*(args->g);
    //const Card *cardToTest = (Card*)data;
    for (i=0; i<10000; i++)
    {
        Game testGame=originalGame;
        //int winnerIndex=rand()%(1-0 + 1) + 0;;

        // A DECOMMENTER QUAND PLAY SERA IMPLEMENTE DANS GAME, on joue une partie

        int winnerIndex=testGame.playCard(args->index);
        scores[args->cardToTest].push_back(winnerIndex);
        //cout << pthread_self()<< ": "<< cardToTest->toString()<<" : "<< scores[cardToTest][i]<<"\n";
    }

    delete (data);
    pthread_exit(NULL);

}

Card* MonteCarlo_launch(Game * game, int turn)
{
    int i;
    //tableau des threads
    pthread_t threads[8];
    //cout << "lancement de monteCarlo..."<<endl<<endl;
    //pour chaque carte de notre main on lance un thread pour faire x parties et on regarde
    vector<int> cardsToTest(game->playableCardsIndex());
    for (i=0; i<cardsToTest.size(); i++)
    {
        pthread_t p_thread;
        int thr_id;
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        struct thread_arg* args = (struct thread_arg *)malloc(sizeof(struct thread_arg));
        args->cardToTest=game->getHand(game->getCurrentPlayer())->getCard(cardsToTest[i]);
        args->g=game;
        args->index=i;

        //on lance le thread pour qu'il execute doloop avec l'argument card
        thr_id=pthread_create(&p_thread, &attr,do_loop,(void*) (args));
        threads[i]=p_thread;

    }

    for (i=0; i<cardsToTest.size(); i++)
    {
        //on attend que tout le monde ait fini
        (void) pthread_join(threads[i], NULL);
    }


    int resultsPerCard[8]= {0,0,0,0,0,0,0,0};
    //on calcule la carte ou on a le plus gagner


    for (i=0; i<8-turn; i++)
    {
        Card* c1= game->getHand(game->getCurrentPlayer())->getCard(i);

        for(std::vector<int>::iterator it = scores[c1].begin(); it != scores[c1].end(); ++it)
        {
            resultsPerCard[i]+=*it;
        }
        //cout << resultsPerCard[i]<<endl;
    }
    scores.clear();

    int maxi=*std::max_element(resultsPerCard,resultsPerCard+8-turn);
    //cout <<"max : "<<maxi<<endl;

    Card* maxCard;
    int index=-1;
    for (i=0; i<8-turn; i++)
    {
        if (resultsPerCard[i]==maxi)
        {
            maxCard=game->getHand(game->getCurrentPlayer())->getCard(i);
            index=i+1;
            break;
        }


    }

    //cout << "meilleure carte : "<<index<<" ème carte de la main : "<< maxCard->toString()<<endl;
    return maxCard;
}
