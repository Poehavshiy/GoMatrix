//
// Created by nikita on 07.04.16.
//

#include "GoGame.h"

GoGame::GoGame() {
    GameMatrix = new GoMatrix(19, 19);
    Nplayers = 2;
    players.resize(Nplayers);
    for (int i = 0; i < Nplayers; i++) {
        players[i].setIDandTable(i, GameMatrix);
    }
}

//
GoGame::GoGame(int ysize, int xsize, int NplayersInc) {
    GameMatrix = new GoMatrix(ysize, xsize);
    Nplayers = NplayersInc;
    players.resize(Nplayers);
    for (int i = 0; i < Nplayers; i++) {
        players[i].setIDandTable(i, GameMatrix);
    }
}

//
void GoGame::setChip(int y, int x, int playerID) {
    vector<int> information = GameMatrix->setChip(y, x, playerID);
    players[playerID].reBuildConturs(information);
}

GoGame::~GoGame() {
    delete GameMatrix;
}