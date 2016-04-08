//
// Created by nikita on 07.04.16.
//

#include "Player.h"

int isIncluded(int start, vector<int> collection, const int &target) {
    for (int i = start; i < collection.size(); i++) {
        if (target == collection[i]) return i;
    }
    return 0;
}

//
Player::Player() {
    parent = NULL;
    score = 0;
    playerID = -1;
}

Player::Player(GoMatrix *table, int ID) {
    parent = table;
    score = 0;
    playerID = ID;

}

//
Player::~Player() {
}

//эта функция принимает вектор информации о вставке фишке из renewMatrix и обновляет контура
void Player::reBuildConturs(const vector<int> &information) {
    //есди контур был создан заново то добавим его по координатам
    //information[1], information[0]
    if (information[0] == 0) {
        Contur newContur(parent, information[1], information[2]);//создаем новый контур
        conturs.push_back(newContur);//и пушим его в вектор контуров игрока
        parent->getField(information[1], information[2]).setContur(conturs.size() - 1);
        //очевидно что контур с iм номером занимает iю позицию в векторе контуров для team команды
        parent->getField(information[1], information[2]).setLabel(
                conturs.size() - 1);//и присвоить этот новый лэйбл полю матрицы

    }
        //если фишка была добавлена к существующему, просто перестроить тот контур, к которому ее добавили
    else if (information[0] == 1 && information[1] == 0) {
        conturs[information[2]].buildContur(information[2]);
    }
        //если контуры были смержены то нужно удалить все контуры из вектора контуров этой команды
        // , которые есть в векторе information кроме того, к которому привели
    else if (information[0] == 1 && information[1] == 1) {
        //начинаем с одного, потому что в 0м лежит вспомогательный несуществующий элемент для нумерации
        for (int i = conturs.size(); i > 0; i--) {
            //если iй индекс содержится в векторе информации и он не равен тому, к чему мы все привели
            if (isIncluded(2, information, i) != 0 && i != information.back()) {
                conturs[i].freeContur();
                conturs.erase(conturs.begin() + i);
            }
        }
        //ну и перестроим контур с которым мы все смержили
        conturs[information.back()].buildContur(information.back());
    }
}
