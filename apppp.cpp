#include <iostream>
using namespace std;

int main() {
    float h1, p1, p2, yf, total;

    cout << "Ingrese la altura menor (H1): ";
    cin >> h1;

    cout << "Ingrese la Presion a la altura menor (P1): ";
    cin >> p1;

    cout << "Ingrese la Presion a la altura mayor (P2): ";
    cin >> p2;

    cout << "Ingrese el peso del fluido (YF): ";
    cin >> yf;

    total = ((p1 - p2) / yf - h1);
    
    cout << "H2 = " << total << "M" << endl;

    return 0;
}
