#include "GoGame.h"
#include <fstream>

int main() {
    ifstream myfile;
    myfile.open("/home/nikita/ClionProjects/TP/algoritms/GoMatrix/testSetChip.txt");
    GoGame A(5, 5, 3);
    int step = 0;
    int x;
    int y;
    int team;
    int iter = 1;
    A.show();
    while (myfile >> y >> x >> team) {
        //  cout<<"in main"<<endl;
        cout << y << ' ' << x << ' ' << team << endl;
        cout << "Iteration:" << iter << endl;
        A.setChip(y, x, team);
        A.show();
        iter++;
    }
    cout << endl << "RESULT:" << endl;
    A.show();
    myfile.close();
    return 0;
}
/*,банда 4х ооп*/