#pragma once

#include "Hand.h"



class Game{
    public:
        Game();
        Game(const Game &g);
        ~Game();
        std::string toString();

        // retourne la main numero index
        const Hand* getConstHand  (int index)const;
        Hand* getHand(int index);
        void setVerbose(int v);
        int getPlayer()const {return player;};
        int getCurrentPlayer()const {return m_currentPlayer;};
        int getFirstPlayer()const {return m_firstPlayer;};
        // fait tourner tout le jeu
        int launch();

        // fait jouer un joueur
        Card* play();

        // fait jouer un joueur aleatoirement
        Card* playRandom();

        // Joue en utilisant Montecarlo
        Card* playMontecarlo();

        //jouer une carte, incrémenter les compeurs de tour de jeu et continuer
        int playCard(int index);

        // 1 si l'equipe du joueur en cours est maitre
        int master();

        //renvoi un vecteur avex l'index des cartes jouables
        std::vector<int> playableCardsIndex();

        int* highestValueBoard();

        //lance une partie et affiche cette partie
        int launchAndPrint();
        int GetRandNum(int max);
    private:
    // distribue les cartes
        void shuffle();
        // initialise le game
        void init();

        // vide board
        void resetBoard();

        int verbose;

        // manche en cours
        int m_turn;

        // joueur en cours
        int m_currentPlayer;

        // les joueurs
        Hand m_hands[4];

        // cartes deja jouees ce tour
        Card* board[4];

        // score de chaque joueur
        int m_scores[4];

        // l'atout
        int m_contract;

        // le joueur qui a l'entame
        int m_firstPlayer;

        // nb de joueurs qui ont joue ce tour
        int player;
};

Card* MonteCarlo_launch(Game * game, int turn);
