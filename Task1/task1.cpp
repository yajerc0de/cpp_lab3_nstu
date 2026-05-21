#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    double x, y, xn, xk, dx;

    cout << "Введите Xнач: ";
    cin >> xn;
    cout << "Введите Xкон: ";
    cin >> xk;
    cout << "Введите шаг dx: ";
    cin >> dx;

    cout << "\n----------------------\n";
    cout << "|    X    |    Y    |\n";
    cout << "----------------------\n";

    for (x = xn; x <= xk; x += dx)
    {
        if (x < -3)
            y = 0; // вне области определения
        else if (x >= -3 && x <= -2)
            y = -2 * x - 4;
        else if (x >= -2 && x < 0)
            y = sqrt(4 - (x + 2) * (x + 2));
        else if (x > 0 && x <= 2)
            y = log2(x) / 2;
        else // x >= 2
            y = 0.5;

        cout << "|" << setw(8) << fixed << setprecision(2) << x
             << "|" << setw(8) << y << " |\n";
    }
    cout << "----------------------\n";

    return 0;
}