//
// Created by nikita on 05.04.16.
//

#ifndef GOMATRIX_CONTUR_H
#define GOMATRIX_CONTUR_H
//
#include "helpingClasses.h"

class GoMatrix;
//

class Contur {
    GoMatrix *parent;
    bool closed;
    vector<YX> content;
public:
    Contur();

    Contur(GoMatrix *targetParent);

    Contur(GoMatrix *targetParent, int y, int x);

    ~Contur();

    int calculateArea();

    void setParent(GoMatrix *targetParent) { parent = targetParent; }

    bool isClosed() { return closed; }

    void add(int y, int x) { content.push_back(YX(y, x)); }

};


#endif //GOMATRIX_CONTUR_H
