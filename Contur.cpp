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
    closed = false;//content=new vector<YX>;
}

//
Contur::Contur(GoMatrix *targetParent) {
    parent = targetParent;
    closed = false;
    start.set(-100, -100);
}

//
Contur::Contur(GoMatrix *targetParent, int y, int x) : start(y, x) {
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
void Contur::buildContur(int conturToAssign) {
    //  cout << "Before rebuiding" << endl;
    freeContur();
    //  cout << "After contur cleaning" << endl;
    //   parent->show();
    //перед этим циклом гарантируется чио все точки текущей команды с текущим лэйблоом
    //обнулены в поле contur
    YX current(start.y, start.x);//текущая точка
    //выдергиваем след точку в направлении против часовой от 6 часов
    current = nextStep(current.y, current.x);
    //мы ее прошли->икрементнем
    parent->getField(current.y, current.x).incrContur();
    content.push_back(current);
    //счетчик количества приходов в голову
    int headCounter = 0;
    while (/*current != start*/ headCounter != 2) {//пока не старт
        //идем в направлении против часовой хватая по хитруму правилу
        //из описания getNextSameUclock(current.y, current.x);
        current = nextStep(current.y, current.x);
        if (current == start) headCounter++;
        //как только мы получили какое то поле мы проинкрементировали
        //количество проходов через него
        parent->getField(current.y, current.x).incrContur();
        //если это поле было пройдено только 1 раз пушанем его в вектор контента
        if (parent->getField(current.y, current.x).getContur() == 1)content.push_back(current);
        //  parent->show(); cout<<endl;
    }
    //починим контур выставив всем полям 1ки в параметр контур
    for (int i = 0; i < content.size(); i++) {
        parent->getField(content[i].y, content[i].x).setContur(conturToAssign);
    }
    // cout << "After contur rebuilding" << endl;
    //  parent->show();
    // cout << endl << endl;
}

//
//Гипер важная функция которая является ключевой для построения замкнутых контуров
YX Contur::nextStep(int y, int x) {
    Field *income = &(parent->getField(y, x));
    YX resultID;
    for (int i = 0; i < 8; i++) {
        YX currentID = parent->getNeighboor(y, x, i);
        Field *current = &(parent->getField(currentID.y, currentID.x));
        /*идем по окрестности находя туто первый попавшийся с таким же лэйблом и командой  */
        if (current->getTeam() == income->getTeam() && current->getLabel() == income->getLabel()) {
            resultID = currentID;
            break;
        }
    }
    //все ниже описанное является поиском элемента такого же команды/лэйбла
    //c наименьшим значением параметра contur
    for (int i = 0; i < 8; i++) {
        YX currentID = parent->getNeighboor(y, x, i);
        Field *current = &(parent->getField(currentID.y, currentID.x));
        /*идем по окрестности отбирая только те точки, у которых совпадает команда и лэйбл  */
        if (current->getTeam() == income->getTeam() && current->getLabel() == income->getLabel()) {
            //если у вновь отобраной точки количество прохождений через нее меньше чем у результата
            //переприсвоим результат
            if ((parent->getField(currentID.y, currentID.x)).getContur() <
                (parent->getField(resultID.y, resultID.x)).getContur()) {
                resultID = currentID;
            }
        }
    }
    return resultID;
}
//

void Contur::freeContur() {
    //замочим старый контур
    for (int i = 0; i < content.size(); i++) {
        parent->getField(content[i].y, content[i].x).setContur(-1);
    }
    content.erase(content.begin(), content.end());
    //
    content.push_back(start);
}

