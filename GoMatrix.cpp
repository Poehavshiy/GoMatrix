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
    //и массива контуров
//    playersConturs=new vector<Contur>[numOfPlayers];
    playersConturs.resize(numOfPlayers);
    //и их инициализация
    /* for(int i=0; i<numOfPlayers; i++) {
         playersConturs[i].resize(10);
     }*/
    for (int i = 0; i < numOfPlayers; i++) {
        playersScore[i] = 0;
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
    //и его инициализация
    // playersConturs=new vector<Contur>[numOfPlayers];
    playersConturs.resize(numOfPlayers);
    /*for(int i=0; i<numOfPlayers; i++) {
        playersConturs[i].resize(10);
    }*/
    for (int i = 0; i < numOfPlayers; i++) {
        playersScore[i] = 0;
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
//    delete[] playersConturs;
}

//y-строка->1й индекс x-столбец->2й индекс
void GoMatrix::setChip(int y, int x, int team) {
    int realX = x + 1;
    int realY = y + 1;
    vector<int> information = renewMatrix(realY, realX, team);
    int i = 0;
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
    int leastLabel = neighboors[0];//к этому лэйблу все и будет приведено
    for (int i = 0; i < neighboors[4]; i++) {//neighboors[4] содержит количество разных лэйблов по соседству
        if (neighboors[i] < leastLabel) leastLabel = neighboors[i];
    }
    //теперь всем контурам этой команды, что лежат в neighboors присвоим leastLabel
    //для этого увы и ах придется пройти по всей матрице и экзаменовать каждый элемент
    //возможно я и придумаю что нибудь лучше в последствии
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

//эта функция обновляет поля глобальной матрицы
// и возвращает информацию о произведенных преобразованиях
vector<int> GoMatrix::renewMatrix(int realY, int realX, int team) {
    //Очень хитрый вектор информации о произошедшем
    /* 0-новый создался контур или же фишка была добавлена к существующему 0/1
     в этом случае больше ничего не добавляется в information так как он был несложно обновлен
     * 1-добавленая фишка была присоединена к чему то или смержила 0/1
     * 2-номер 1го контура, в случае если предъидущтй пункт 0-это последние поле вектора information
     * 3-номер 2го контура
     * 4-номер 3го контура
     * 5-номер 4го контура
     * в случае мержа 2 и более +1 поле-отвечает за номер контура, к которому все было приведено*/
    vector<int> information;
    matrix[realY][realX].setTeam(team);
    //теперь проверим, есть ли такие же фишки в 8-окресности
    int *neighboors = checkNeighboors(realY, realX, team);
    if (neighboors[4] == 0) {//если таких же нет
        cout << endl << "Nothing in neig" << endl;//для дебага
        Contur newContur(this, realY, realX);//создаем новый контур
        playersConturs[team - 1].push_back(newContur);//и пушим его в вектор контуров команды team
        //очевидно что контур с iм номером занимает iю позицию в векторе контуров для team команды
        matrix[realY][realX].setLabel(playersConturs[team - 1].size());//и присвоить этот новый лэйбл
        information.push_back(0);//обновим и вернем инфу о произошедшем
    }
    else {
        //если такие же есть
        //если такая же фишка в окресности только одного типа
        //присоединим вставляемую фишку к имеющимуся контуру
        if (neighboors[4] == 1) {
            matrix[realY][realX].setLabel(neighboors[0]);
            //в таком случае составим вектор информации в соответствии с его описанием
            information.push_back(1);//фишка была добавлена к существующему
            information.push_back(0);//фишка была добавлена без мержа
            information.push_back(neighboors[0]);//контур к которому была добавлена фишка
        }
        else {
            int labelToset = mergeSets(neighboors, team);//лэйбл к которому все приведется
            matrix[realY][realX].setLabel(labelToset);//его то мы и поставили
            information.push_back(1);//фишка была добавлена к существующему
            information.push_back(1);//фишка была добавлена с мержем
            for (int i = 0; i < neighboors[4]; i++) {//последовательно добавляем лэйблы
                information.push_back(neighboors[i]);//в вектор инфы
            }
            information.push_back(labelToset);//последним добавляется номер лэйбла, к которому мы все привели
        }
    }
    delete[] neighboors;
    return information;
}