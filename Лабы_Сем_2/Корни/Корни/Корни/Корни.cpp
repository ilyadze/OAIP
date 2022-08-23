#include <iostream>
#include <string>
#include <cmath>
#include <conio.h>
#include <Windows.h>
#include <iomanip>

using namespace std;

typedef double (*fun)(double);

double function1(double);
double function2(double);
double function3(double);
double function4(double);
double dFunction1(double);
double dFunction2(double);
double dFunction3(double);
double dFunction4(double);

double dF(fun, double, double);
double inputNumber();
bool isNumberNumeric();
double FindRootSecants(fun, double, double, double,int&);
double FindRootWerstein(fun F, double x0, double eps, double x1,int&);
double FindRootNewton(fun F, fun DF, double x0, double eps,int&);
double simpleIterationMethod(fun F, double x, double eps,int&);
double metodOfDivisionInHalf(fun f, double x0, double x1, double eps,int&);

int main() {
    fun f = function1,dF = dFunction1;
    do {
        system("cls");
        double a, b, h = 0.01, eps = 0.001;
        cout << "Select a function: " << endl
            << "1.4x - 7sin(x)" << endl
            << "2.x^2 - 10(sin(x))^2 + 2" << endl
            << "3.ln(x) - 5cosx" << endl
            << "4.(e^x)/(x^3) - (sin(x))^3 - 2" << endl
            << "Exit" << endl;
        switch (_getch()) {
        case '1': {
            f = function1;
            dF = dFunction1;
            a = -2;
            b = 2;
            break;
        }
        case '2': {
            f = function2;
            dF = dFunction2;
            a = -1;
            b = 3;
            break;
        }
        case '3': {
            f = function3;
            dF = dFunction3;
            a = 1;
            b = 8;
            break;
        }
        case '4': {
            f = function4;
            dF = dFunction4;
            a = 4;
            b = 7;
            break;
        }
        default: {
            cout << "If you want to exit press '1'" << endl;
            if (_getch() == '1') {
                return 0;
            }
            else {
                continue;
            }
        }
        }
        cout << "If you want to work with values from the manual, press '1'" << endl;
        if (_getch() != '1') {
            cout << "a = ";
            a = inputNumber();
            cout << "\nb = ";
            b = inputNumber();
            do {
                cout << "\neps = ";
                eps = inputNumber();
                if (eps <= 0) {
                    cout << "Error, eps if can be less than zero" << endl;
                    Sleep(3000);
                }
            } while (eps <= 0);
            do {
                cout << "\nh = ";
                h = inputNumber();
                if (h <= 0) {
                    cout << "Error, h if can be less than zero" << endl;
                    Sleep(3000);
                }
            } while (h <= 0);
        }
        int n = 0;
        system("cls");
        cout << "With the parametrs:\na = " << a << "\nb = " << b << "\nh = " << h << "\ne = " << eps << "\n\n";
        cout << "______________________________________________________________________________________________________________" << endl
            << setw(6) << "|" << setw(20) << left << " Metod of secants" << "|"
            << setw(20) << "Werstein method" << "|"
            << setw(20) << "Newton method" << "|"
            << setw(20) << "Simple iteration" << "|"
            << setw(20) << "Division in half" << "|" << endl;
        for (double x = a; x <= b; x += h)
        {

            if (f(x) * f(x + h) < 0) {
                n++;
                int iterationSecants = 0;
                double resultSecants = FindRootSecants(f, x, eps, h, iterationSecants);
                int iterationWerstein = 0;
                double resultWerstein = FindRootWerstein(f, x, eps, x + h, iterationWerstein);
                int iterationNewton = 0;
                double resultNewton = FindRootNewton(f, dF, x, eps,iterationNewton);
                int iterationSimpleIteration = 0;
                double simpleIteration = simpleIterationMethod(f, x, eps, iterationSimpleIteration);
                int iterationDivisonHalf = 0;
                double divisionInHalf = metodOfDivisionInHalf(f, x, x + h, eps, iterationDivisonHalf);
                cout << "-----+--------------------+--------------------+--------------------+--------------------+--------------------+" << endl
                    << setw(5) << "x" << "|"
                    << setw(20) << resultSecants << "|"
                    << setw(20) << resultWerstein << "|"
                    << setw(20) << resultNewton << "|"
                    << setw(20) << simpleIteration << "|"
                    << setw(20) << divisionInHalf << "|" << endl
                    << setw(5) << "Iter" << "|"
                    << setw(20) << iterationSecants << "|"
                    << setw(20) << iterationWerstein << "|"
                    << setw(20) << iterationNewton << "|"
                    << setw(20) << iterationSimpleIteration << "|"
                    << setw(20) << iterationDivisonHalf << "|" << endl
                    << setw(5) << "F(x)" << "|"
                    << setw(20) << f(resultSecants) << "|"
                    << setw(20) << f(resultWerstein) << "|"
                    << setw(20) << f(resultNewton) << "|"
                    << setw(20) << f(simpleIteration) << "|"
                    << setw(20) << f(divisionInHalf) << "|" << endl;

            }
            else {
                if (f(x) == 0) {
                    n++;
                    cout << "-----+--------------------+--------------------+--------------------+--------------------+--------------------+" << endl
                        << setw(5) << "x" << "|"
                        << setw(20) << x << "|"
                        << setw(20) << x << "|"
                        << setw(20) << x << "|"
                        << setw(20) << x << "|"
                        << setw(20) << x << "|" << endl
                        << setw(5) << "F(x)" << "|"
                        << setw(20) << f(x) << "|"
                        << setw(20) << f(x) << "|"
                        << setw(20) << f(x) << "|"
                        << setw(20) << f(x) << "|"
                        << setw(20) << f(x) << "|" << endl;
                }
            }
        }
        cout << "==============================================================================================================" << endl;
        if (n == 0) {
            cout << "There are no roots\n";
        }
        cout << "Press '1', if you want to continue" << endl;
        if (_getch() != '1') {
            break;
        }
    } while (true);
}



double FindRootSecants(fun F,double x0, double eps, double h,int& iteration) {
    double x1 = x0 - F(x0) * h / (F(x0) - F(x0 - h));
    iteration = 0;
    while (fabs(x1 - x0) > eps)
    {
        x0 = x1;
        x1 = x1 - F(x1) * h / (F(x1) - F(x1 - h));
        iteration++;
    }
    return x0;
}

double FindRootWerstein(fun F, double x0, double eps, double x1,int& iteration) {
    double x2 = x1 - (F(x1)*(x1 - x0))/(F(x1) - F(x0));
    while (fabs(x2 - x1) > eps)
    {
        x0 = x1;
        x1 = x2;
        x2 = x1 - F(x1) * (x1 - x0) / (F(x1) - F(x0));
        iteration++;
    }
    return x0;
}

double FindRootNewton(fun F, fun DF,double x0, double eps,int& iteration) {
    double x1 = x0 - F(x0)/DF(x0);
    while (fabs(x1 - x0) > eps) {
        x0 = x1;
        x1 = x1 - F(x1) / DF(x1);
        iteration++;
    }
    return x0;
}
double simpleIterationMethod(fun F, double x0, double eps, int& iteration) {
    double x1 = x0 + 0.000001*F(x0);
    while (fabs(x1 - x0) > eps) {
        x0 = x1;
        x1 = x0 + 0.000001 * F(x0);
        iteration++;
    }

    return x0;
}

double metodOfDivisionInHalf(fun f, double x0, double x1, double eps,int& iteration) {
    double x2 = (x0 + x1) / 2, y0, y2;
    y0 = f(x0);
    while (fabs(x1 - x0) > eps) {
        x2 = (x0 + x1) / 2;
        y2 = f(x2);
        if (y0 * y2 > 0) {
            x0 = x2; y0 = y2;
        }
        else x1 = x2;
        iteration++;
    }
    return (x0 + x1) / 2;
}

double inputNumber() {
    double number;
    while (true) {
        cin >> number;
        if (isNumberNumeric()) {
            return number;
        }

    }
}

bool isNumberNumeric() {
    if (cin.get() == '\n') {
        return true;
    }
    else {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "Error, incorrect input" << endl;
        Sleep(3000);
        cout << "Enter again" << endl;
        return false;
    }
}


double function1(double x) {
   return 4 * x - 7 * sin(x);
}
double function2(double x) {
    return pow(x, 2) - 10 * pow(sin(x), 2) + 2;
}
double function3(double x) {
    return log(x) - 5 * cos(x);
}
double function4(double x) {
    return exp(x) / pow(x, 3) - pow(sin(x),3) - 2;
}

double dFunction1(double x) {
    return 4 - 7 * cos(x);
}
double dFunction2(double x) {
    return 2 * x - 20 * sin(x) * cos(x);
}
double dFunction3(double x) {
    return 1 / x + 5 * sin(x);
}
double dFunction4(double x) {
    return (exp(x) * pow(x, 3) - 3 * pow(x, 2) * exp(x)) / pow(x, 6) - 3 * pow(sin(x), 2) * cos(x);
}

double dF(fun F,double x, double eps) {
    return (F(x + eps) - F(x - eps)) / (2 * eps);
}

