#include "GoMatrix.h"
#include <fstream>

int main() {
    ifstream myfile;
    myfile.open("/home/nikita/ClionProjects/TP/algoritms/GoMatrix/testContors3.txt");
    GoMatrix A(6, 6, 3);
    int step = 0;
    int x;
    int y;
    int team;
    int iter = 1;
    while (myfile >> y >> x >> team) {
        //  cout<<"in main"<<endl;
        A.show();
        cout << y << ' ' << x << ' ' << team << endl;
        cout << "Iteration:" << iter << endl;
        A.setChip(y, x, team);
        iter++;
    }
    A.show();
    myfile.close();
    return 0;
}
/*,банда 4х ооп*/