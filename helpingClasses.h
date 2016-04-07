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

    YX() : y(-1), x(-1) { }

    YX(int Y, int X) : y(Y), x(X) { }

    void set(int y, int x) {
        y = y;
        x = x;
    }

    bool operator!=(YX &left) {
        if (y == left.y && x == left.x) return false;
        else return true;
    }

    bool operator==(YX &left) {
        if (y == left.y && x == left.x) return true;
        else return false;
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
    // int он потому что в процессе нахождения замкнутых контуров
    //это число будет показывать, сколько раз через него прошел "жук"
    int contur;
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

    int getContur() { return contur; }

    void setContur(int inc) { contur = inc; }

    void incrContur() { contur++; }

};

// простой поиск элемента в контэйнере с какой то начальной позиции и возвращаем индес

#endif //GOMATRIX_HELPINGCLASSES_H
