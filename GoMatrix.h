//
// Created by nikita on 03.04.16.
//This Class provides full interface and logic for Go playing desk
//

#ifndef GOMATRIX_GOMATRIX_H
#define GOMATRIX_GOMATRIX_H

#include <iostream>

//Супер проостая вспомогательная структура-пара индексов
struct YX {
    int y;
    int x;

    YX(int Y, int X) : y(Y), x(X) { }

    bool operator!=(YX &left) {
        if (y == left.y && x == left.x) return false;
        else return true;
    }
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

class GoMatrix {
public:
    GoMatrix();

    GoMatrix(int X, int Y, int NPlayers);

    ~GoMatrix();

    void show();

    void setChip(int y, int x, int team);

    void buildContur(int startY, int startX);


private:
    Field **matrix;
    //игровая доска
    int xSize;
    //1й размер
    int ySize;
    //2й размер
    int numOfPlayers;
    //количество игроков
    int *playersScore;
    //очки iго игрока
    int *teamCounters;

    // массив счетчиков количества связных областей у iй команды
    //приватные функции
    void initBoundary();

    //присвоить лэйбл -1 всем границам
    //проверяет наличие в 8-окресности таких же фишек
    //и возвращает указатель на такую же фишку
    int *checkNeighboors(int y, int x, int incTeam);

    //Возвращает ячейку с pos от 0го до 7го включительно
    YX getNeighboor(int y, int x, int pos);

    //Объединяет контуры количеством от 2 до 4 принадлежащие комаде team
    //возвращает лэйбл к которому все привели
    int mergeSets(int *neighboors, int team);

    //
    YX getNextSameUclock(int y, int x);
};


#endif //GOMATRIX_GOMATRIX_H
