//
// Created by nikita on 07.04.16.
//

#ifndef GOMATRIX_GOGAME_H
#define GOMATRIX_GOGAME_H

#include "Player.h"

class GoGame {
private:
    GoMatrix *GameMatrix;
    vector<Player> players;
    int Nplayers;
public:
    GoGame();

    GoGame(int ysize, int xsize, int NplayersInc);

    ~GoGame();

    void setChip(int y, int x, int playerID);

    void show() {
        GameMatrix->show();
    };
};


#endif //GOMATRIX_GOGAME_H
