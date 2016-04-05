//
// Created by nikita on 03.04.16.
//
/*
private:
Field** matrix;//игровая доска
int xSize;//1й размер
int ySize;//2й размер
int numOfPlayers;//количество игроков
int* playersScore;//очки iго игрока
};*/

#include "GoMatrix.h"

//конструктор по умолчанию
GoMatrix::GoMatrix() {
    xSize = 19;//стандартный размер для игры в Go 19х19
    ySize = 19;
    numOfPlayers = 2;//на 2 игроков
    playersScore = new int[numOfPlayers];//выделение массива очков на 2 игроков
    teamCounters = new int[numOfPlayers];//выделение массива счетчиков
    //и его инициализация
    for (int i = 0; i < numOfPlayers; i++) {
        playersScore[i] = 0;
        teamCounters[i] = 0;
    }
    //+2 выделяется для создания вспомогательных граничных элементов
    matrix = new Field *[ySize + 2];
    for (int i = 0; i < ySize + 2; i++) {
        matrix[i] = new Field[xSize + 2];
    }
    //заполнение -1ми вспомогательных границ
    initBoundary();
}

//пользовательский конструктор
GoMatrix::GoMatrix(int X, int Y, int NPlayers) {
    xSize = X;//стандартный размер для игры в Go 19х19
    ySize = Y;
    numOfPlayers = NPlayers;//на 2 игроков
    playersScore = new int[numOfPlayers];//выделение массива очков на numOfPlayers игроков
    teamCounters = new int[numOfPlayers];//выделение массива счетчиков
    //и его инициализация
    for (int i = 0; i < numOfPlayers; i++) {
        playersScore[i] = 0;
        teamCounters[i] = 0;
    }
    //+2 выделяется для создания вспомогательных граничных элементов
    matrix = new Field *[ySize + 2];
    for (int i = 0; i < ySize + 2; i++) {
        matrix[i] = new Field[xSize + 2];
    }
    //заполнение -1ми вспомогательных границ
    initBoundary();
}

GoMatrix::~GoMatrix() {
    for (int i = 0; i < ySize + 2; i++) {
        delete[] matrix[i];
    }
    delete matrix;
    delete playersScore;
    delete[] teamCounters;
}

//y-строка->1й индекс x-столбец->2й индекс
void GoMatrix::setChip(int y, int x, int team) {
    int realX = x + 1;
    int realY = y + 1;
    matrix[realY][realX].setTeam(team);
    //теперь проверим, есть ли такие же фишки в 8-окресности
    int *neighboors = checkNeighboors(realY, realX, team);
    if (neighboors[4] == 0) {//если таких же нет
        cout << endl << "Nothing in neig" << endl;
        teamCounters[team]++;//увеличить счетчик связных областей занятых фишками iй команды
        matrix[realY][realX].setLabel(teamCounters[team]);//и присвоить этот новый лэйбл
    }
    else {
        //если такие же есть
        //если такая же фишка в окресности только одного типа
        //присоединим вставляемую фишку к имеющимуся контуру
        if (neighboors[4] == 1) {
            matrix[realY][realX].setLabel(neighboors[0]);
        }
        else matrix[realY][realX].setLabel(mergeSets(neighboors, team));
    }
    delete[] neighboors;
}


//Показывалка
void GoMatrix::show() {
    for (int i = 0; i < ySize + 2; i++) {
        for (int j = 0; j < xSize + 2; j++) {
            cout << matrix[i][j].getTeam() << "/";
            if (matrix[i][j].getLabel() != -1) cout << ' ';
            cout << matrix[i][j].getLabel() << '/';
            cout << matrix[i][j].isContur() << "  ";
        }
        cout << endl;
    }
}

//приватные функции
void GoMatrix::initBoundary() {
    //1я строка
    for (int i = 0; i < xSize + 2; i++) {
        matrix[0][i].setLabel(-1);
    }
    //последняя строка
    for (int i = 0; i < xSize + 2; i++) {
        matrix[ySize + 1][i].setLabel(-1);
    }
    //1й столбец
    for (int i = 0; i < ySize + 2; i++) {
        matrix[i][0].setLabel(-1);
    }
    //последний столбец
    for (int i = 0; i < ySize + 2; i++) {
        matrix[i][xSize + 1].setLabel(-1);
    }
}
//

int *GoMatrix::checkNeighboors(int y, int x, int incTeam) {
    //описание этого массива
    /* хранит встреченные лэйблы фишек той же команды
      0, 1, 2, 3- различные встреченные лэйблы этой же команды
      4-их общее количество
     * */
    int *neighboors = new int[5];
    for (int i = 0; i < 5; i++) {
        neighboors[i] = 0;
    }
    int LabelCounter = 0;
    //int incMeetingStatus=0;
    //идем по часовой
    int i = 0;//счетчик позиций
    for (int i = 0; i < 8; i++) {
        YX curID = getNeighboor(y, x, i);
        Field *current = &matrix[curID.y][curID.x];
        if (current->getTeam() == incTeam) {//
            if (LabelCounter == 0) {
                neighboors[4] = 1;
                neighboors[0] = current->getLabel();
                LabelCounter++;
            }
            else {
                //если вноаь встреченная фишка той же команды пренадлежит другому контуру
                if (current->getLabel() != neighboors[LabelCounter - 1]) {
                    neighboors[4]++;//количество встреченных различных лэйблом той же команды
                    neighboors[LabelCounter] = current->getLabel();
                    LabelCounter++;
                }

            }
        }
    }
    return neighboors;
}

//
YX GoMatrix::getNeighboor(int y, int x, int pos) {
    //возвращает позицию как если бы идти против часовой стрелке
    switch (pos) {
        case 0:
            return YX(y + 1, x);
        case 1:
            return YX(y + 1, x + 1);
        case 2:
            return YX(y, x + 1);
        case 3:
            return YX(y - 1, x + 1);
        case 4:
            return YX(y - 1, x);
        case 5:
            return YX(y - 1, x - 1);
        case 6:
            return YX(y, x - 1);
        case 7:
            return YX(y + 1, x - 1);
    }
}

int GoMatrix::mergeSets(int *neighboors, int team) {
    //найдем самый маленький лэйбл
    int leastLabel = neighboors[0];
    for (int i = 0; i < neighboors[4]; i++) {
        if (neighboors[i] < leastLabel) leastLabel = neighboors[i];
    }
    //теперь всем контурам этой команды, что лежат в neighboors присвоим leastLabel
    for (int i = 1; i < ySize + 1; i++) {
        for (int j = 1; j < xSize + 1; j++) {
            bool needToreset = false;
            if (matrix[i][j].getTeam() == team) {
                for (int k = 0; k < neighboors[4]; k++) {
                    //если один из лэйблов для замены лежит в ячейке
                    if (neighboors[k] == matrix[i][j].getLabel()) needToreset = true;
                }
            }
            if (needToreset == true) matrix[i][j].setLabel(leastLabel);
        }
    }
    return leastLabel;
}

//
void GoMatrix::buildContur(int startY, int startX) {
    YX start(startY, startX);
    YX current(startY, startX);
    //matrix[startY][startX].setContur(true);
    current = getNextSameUclock(current.y, current.x);
    matrix[current.y][current.x].setContur(true);
    while (current != start) {
        current = getNextSameUclock(current.y, current.x);
        matrix[current.y][current.x].setContur(true);
    }
}

//
YX GoMatrix::getNextSameUclock(int y, int x) {
    Field *income = &matrix[y][x];
    for (int i = 0; i < 8; i++) {
        YX curID = getNeighboor(y, x, i);
        Field *current = &matrix[curID.y][curID.x];
        if (current->getTeam() == income->getTeam() && current->getLabel() == income->getLabel()
            && current->isContur() == false) {
            return curID;
        }
    }
    //еслм все обыскали и не нашли вернем элемент, являющийся контуром
    for (int i = 0; i < 8; i++) {
        YX curID = getNeighboor(y, x, i);
        Field *current = &matrix[curID.y][curID.x];
        if (current->getTeam() == income->getTeam() && current->getLabel() == income->getLabel()
            /*&& current->isContur() == false*/) {//на последнее условие теперь забьем
            return curID;
        }
    }
    return YX(-1, -1);//если уж совсем ничего не нашли
}
