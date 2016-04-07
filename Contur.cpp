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
    start.set(-228, -228);
    //content=new vector<YX>;
}

//
Contur::Contur(GoMatrix *targetParent) {
    parent = targetParent;
    closed = false;
    start.set(-1, -1);
}

//
Contur::Contur(GoMatrix *targetParent, int y, int x) {
    parent = targetParent;
    closed = false;
    //content=new vector<YX>;
    content.push_back(YX(y, x));
    start.set(y, x);
}
//

Contur::~Contur() {
    //delete content;
}
//
void Contur::buildContur(int conturToAssign) {
    cout << "Before rebuiding" << endl;
    //   parent->show();
    freeContur();
    cout << "After contur cleaning" << endl;
    //   parent->show();
    //перед этим циклом гарантируется чио все точки текущей команды с текущим лэйблоом
    //обнулены в поле contur
    YX current(start.y, start.x);//текущая точка
    //выдергиваем след точку в направлении против часовой от 6 часов
    current = parent->getNextSameUclock(current.y, current.x);
    //мы ее прошли->икрементнем
    parent->getField(current.y, current.x).incrContur();
    content.push_back(current);
    //счетчик количества приходов в голову
    int headCounter = 0;
    while (/*current != start*/ headCounter != 2) {//пока не старт
        //идем в направлении против часовой хватая по хитруму правилу
        //из описания getNextSameUclock(current.y, current.x);
        current = parent->getNextSameUclock(current.y, current.x);
        if (current == start) headCounter++;
        //как только мы получили какое то поле мы проинкрементировали
        //количество проходов через него
        parent->getField(current.y, current.x).incrContur();
        //если это поле было пройдено только 1 раз пушанем его в вектор контента
        if (parent->getField(current.y, current.x).getContur() == 1)content.push_back(current);
    }
    //починим контур выставив всем полям 1ки в параметр контур
    for (int i = 0; i < content.size(); i++) {
        parent->getField(content[i].y, content[i].x).setContur(conturToAssign);
    }
    cout << "After contur rebuilding" << endl;
    //  parent->show();
    cout << endl << endl;
}

void Contur::freeContur() {
    //замочим старый контур
    for (int i = 0; i < content.size(); i++) {
        parent->getField(content[i].y, content[i].x).setContur(false);
    }
    content.erase(content.begin(), content.end());
    //
    content.push_back(start);
}

