#ifndef MONTECARLO_H
#define MONTECARLO_H

#define NBPARTIES 100
#include "Game.h"
#include <pthread.h>

class MonteCarlo
{
    public:
        MonteCarlo(Game* g);
        virtual ~MonteCarlo();
        Game* Getgame() { return m_game; }
        void Setgame(Game* val) { m_game = val; }
        Card* launch();
    protected:
    private:
        Game* m_game;
};

#endif // MONTECARLO_H
