#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double coffee_model(double T_env, double T0, double r, double t) {
    return T_env + (T0 - T_env) * exp(-r * t);
}

void linear_regression(const vector<double>& x,
                       const vector<double>& y,
                       double& a,
                       double& b,
                       double& corr,
                       double& R2) {

    int n = x.size();

    double sum_x = 0;
    double sum_y = 0;
    double sum_xy = 0;
    double sum_x2 = 0;

    // Подсчёт сумм
    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    // Средние значения
    double mean_x = sum_x / n;
    double mean_y = sum_y / n;

    // Переменные для корреляции
    double numerator = 0;
    double denominator_x = 0;
    double denominator_y = 0;

    // Формула корреляции Пирсона
    for (int i = 0; i < n; i++) {

        numerator += (x[i] - mean_x) *
                     (y[i] - mean_y);

        denominator_x += pow(x[i] - mean_x, 2);

        denominator_y += pow(y[i] - mean_y, 2);
    }

    // Коэффициент корреляции
    corr = numerator /
           sqrt(denominator_x * denominator_y);

    // Коэффициенты прямой y = a*x + b
    a = (n * sum_xy - sum_x * sum_y) /
        (n * sum_x2 - sum_x * sum_x);

    b = (sum_y - a * sum_x) / n;

    // Коэффициент детерминации
    R2 = corr * corr;
}

int main() {

    double T_env;
    double T0;
    double r;

    int n;
    double dt;

    cout << "Температура среды: ";
    cin >> T_env;

    cout << "Начальная температура кофе: ";
    cin >> T0;

    cout << "Коэффициент остывания: ";
    cin >> r;

    cout << "Количество измерений: ";
    cin >> n;

    cout << "Шаг времени: ";
    cin >> dt;

    vector<double> times(n);
    vector<double> temps(n);

    for (int i = 0; i < n; i++) {
        times[i] = i * dt;
    }

    for (int i = 0; i < n; i++) {
        temps[i] = coffee_model(T_env, T0, r, times[i]);
    }

    double a, b, corr, R2;

    linear_regression(times, temps, a, b, corr, R2);

    cout << fixed << setprecision(4);

    cout << "\nТаблица значений:\n";
    cout << "t\t\tT\n";

    for (int i = 0; i < n; i++) {
        cout << times[i] << "\t" << temps[i] << endl;
    }

    cout << "\nЛинейная модель:\n";
    cout << "T = " << a << " * t + " << b << endl;

    cout << "\nКоэффициент корреляции r = " << corr << endl;
    cout << "Коэффициент детерминации R^2 = " << R2 << endl;

    return 0;
}