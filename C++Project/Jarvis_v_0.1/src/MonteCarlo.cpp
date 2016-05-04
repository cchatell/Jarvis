#include "MonteCarlo.h"
#include<iostream>
#include <pthread.h>
#include <unistd.h>
#include <map>
#include <algorithm>    // std::min_element, std::max_element


using namespace std;
MonteCarlo::MonteCarlo(Game* g):m_game(g)
{
    //ctor
}

MonteCarlo::~MonteCarlo()
{
    //dtor
}

//scores
map<const Card*,std::vector<int> > scores;

void* do_loop(void* data)
{
    int i;
    //MonteCarlo pour 100 parties
    for (i=0; i<1000; i++)
    {

        const Card *cardToTest = (Card*)data;
        int winnerIndex=rand()%(1-0 + 1) + 0;;

        // A DECOMMENTER QUAND PLAY SERA IMPLEMENTE DANS GAME, on joue une partie

        //winnerIndex=game.play(cardToTest);
        scores[cardToTest].push_back(winnerIndex);
        //cout << pthread_self()<< ": "<< cardToTest->toString()<<" : "<< scores[cardToTest][i]<<"\n";
    }
    pthread_exit(NULL);

}

Card* MonteCarlo::launch()
{
    int i;
    //tableau des threads
    pthread_t threads[8];

    //pour chaque carte de notre main on lance un thread pour faire x parties et on regarde
    for (i=0; i<8; i++)
    {
        pthread_t p_thread;
        int thr_id;
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        //on lance le thread pour qu'il execute doloop avec l'argument card
        thr_id=pthread_create(&p_thread, &attr,do_loop,(void*) (m_game->getHand(0)->getCard(i)));
        threads[i]=p_thread;

    }

    for (i=0; i<8; i++)
    {
        //on attend que tout le monde ait fini
        (void) pthread_join(threads[i], NULL);
    }


    int resultsPerCard[8]={0,0,0,0,0,0,0,0};
    //on calcule la carte ou on a le plus gagner


    for (i=0; i<8; i++)
    {
        Card* c1= m_game->getHand(0)->getCard(i);

        for(std::vector<int>::iterator it = scores[c1].begin(); it != scores[c1].end(); ++it)
        {
            resultsPerCard[i]+=*it;
        }
        cout << resultsPerCard[i]<<endl;
    }

    int maxi=*std::max_element(resultsPerCard,resultsPerCard+8);
    cout <<"max : "<<maxi<<endl;

    Card maxCard;
    int index=-1;
    for (i=0; i<8; i++)
    {
        if (resultsPerCard[i]==maxi) {
        maxCard=*(m_game->getHand(0)->getCard(i));
        index=i+1;
        break;
        }


    }

    cout << "meilleure carte : "<<index<<" ème carte de la main : "<< maxCard.toString()<<endl;
    return &maxCard;
}
