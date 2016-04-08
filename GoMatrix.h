//
// Created by nikita on 03.04.16.
//This Class provides full interface and logic for Go playing desk
//

#ifndef GOMATRIX_GOMATRIX_H
#define GOMATRIX_GOMATRIX_H

#include "Contur.h"
#include "helpingClasses.h"

class GoMatrix {
public:
    friend class Contur;

    GoMatrix();

    GoMatrix(int X, int Y);

    ~GoMatrix();

    void show();

    vector<int> setChip(int y, int x, int team);

    Field &getField(int y, int x);


private:
    Field **matrix;
    //игровая доска
    int xSize;
    //1й размер
    int ySize;
    //приватные функции
    void initBoundary();

    //присвоить лэйбл -1 всем границам
    //проверяет наличие в 8-окресности таких же фишек
    //и возвращает указатель на такую же фишку
    int *checkNeighboors(int y, int x, int team);

    //Возвращает ячейку с pos от 0го до 7го включительно
    YX getNeighboor(int y, int x, int pos);

    //Объединяет контуры количеством от 2 до 4 принадлежащие комаде team
    //возвращает лэйбл к которому все привели
    int mergeSets(int *neighboors, int team);
    //эта обновляет поля матрицы непосредственно
    //и возвращает инфу о произошедшем
    vector<int> renewMatrix(int realY, int realX, int team);
};


#endif //GOMATRIX_GOMATRIX_H
