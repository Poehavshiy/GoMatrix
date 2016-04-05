//
// Created by nikita on 05.04.16.
//

#ifndef GOMATRIX_HELPINGCLASSES_H
#define GOMATRIX_HELPINGCLASSES_H

#include <iostream>
#include <vector>

//Супер проостая вспомогательная структура-пара индексов
struct YX {
    int y;
    int x;

    YX(int Y, int X) : y(Y), x(X) { }

    bool operator!=(YX &left) {
        if (y == left.y && x == left.x) return false;
        else return true;
    }

    ~YX() { }
};

using namespace std;
//Описание класса
/*Этот класс инкапсулирует ячейку на доске
в нем содержится информация о номере контура и о принадлежности этого контура
определенной комнде*/
class Field {
    //это метка контура, контуры с одинаковыми лэйблами могут быть дифференцированы
    //с помощью поля team.
    //0-пустая, -1-вспомогательная
    int label;
    // указывает на пренадлежность данного поля
    //определенной команде, либо границе игровой зоны, либо пустому полю
    int team;
    //
    bool contur;
public:
    Field() {
        label = 0;
        team = 0;
        contur = 0;
    }

    Field(int &incLabel, int &incTeam) {
        label = incLabel;
        team = incTeam;
        contur = 0;
    }

    //простецкий интерфейс
    void set(int incLabel, int incTeam) {
        label = incLabel;
        team = incTeam;
    }

    int getLabel() { return label; }

    int getTeam() { return team; }

    void setLabel(int inc) { label = inc; }

    void setTeam(int inc) { team = inc; }

    bool isContur() { return contur; }

    void setContur(bool inc) { contur = inc; }


};

#endif //GOMATRIX_HELPINGCLASSES_H
