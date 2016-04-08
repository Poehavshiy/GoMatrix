//
// Created by nikita on 07.04.16.
//

#ifndef GOMATRIX_PLAYER_H
#define GOMATRIX_PLAYER_H

#include "GoMatrix.h"

class Player {
public:
    Player();

    Player(GoMatrix *table, int playerID);

    ~Player();

    void setIDandTable(int ID, GoMatrix *tableInc) {
        playerID = ID;
        parent = tableInc;
    }

    void reBuildConturs(const vector<int> &information);

private:
    vector<Contur> conturs;
    GoMatrix *parent;
    int score;
    int playerID;

};


#endif //GOMATRIX_PLAYER_H
