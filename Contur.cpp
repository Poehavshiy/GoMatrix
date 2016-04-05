//
// Created by nikita on 05.04.16.
//
/*
class Contur {
    GoMatrix* parent;
    bool closed;
    vector<YX>*  content;
public:
    Contur();
    Contur( GoMatrix* targetParent);
    ~Contur();
    int calculateArea();
};*/


#include "Contur.h"
#include "GoMatrix.h"

Contur::Contur() {
    parent = NULL;
    closed = false;
    //content=new vector<YX>;
}

//
Contur::Contur(GoMatrix *targetParent) {
    parent = targetParent;
    closed = false;
    // content=new vector<YX>;
}

//
Contur::Contur(GoMatrix *targetParent, int y, int x) {
    parent = targetParent;
    closed = false;
    //content=new vector<YX>;
    content.push_back(YX(y, x));
}
//

Contur::~Contur() {
    //delete content;
}
//