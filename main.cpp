#include "GoMatrix.h"
#include <fstream>

int main() {
    ifstream myfile;
    myfile.open("/home/nikita/ClionProjects/TP/algoritms/GoMatrix/txtMzfk.txt");
    GoMatrix A(5, 5, 3);
    A.show();
    int step = 0;
    int x;
    int y;
    int team;
    while (myfile >> y >> x >> team) {
        A.setChip(y, x, team);
        cout << y << ' ' << x << ' ' << team << endl;
        A.show();
        cout << endl;
    }
    A.buildContur(1, 1);
    A.show();
    myfile.close();
    return 0;
}