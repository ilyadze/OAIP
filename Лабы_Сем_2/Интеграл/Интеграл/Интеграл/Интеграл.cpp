#include <iostream>
#include <cmath>
#include <Windows.h>
#include <conio.h>
#include <iomanip>

typedef double (*fun)(double);
typedef double (*funMethod)(fun, double, double, int);

using namespace std;



double Simps(fun,double, double, int);
double SimpsAccordingToTheSpecifiedAccuracy(fun,double, double, double);
double TrapezoidFormulaAccordingToTheSpecifiedAccuracy(fun,double, double, double);
double TrapezoidFormula(fun,double, double, int);
double MediumSizedFormulaAccordingToTheSpecifiedAccuracy(fun, double, double, double);
double MediumSizedFormula(fun, double, double, int);
double automaticMethod_2(fun, double, double, int);
double automaticMethod_2AccordingToTheSpecifiedAccuracy(fun, double, double, double);
double AccordingToTheSpecifiedAccuracy(fun f, funMethod method, double a, double b, double e);
//double GaussMethod_2(fun f, double a, double b, double n);
//double GaussMethod_2_AccordingToTheSpecifiedAccuracy(fun f, double a, double b, double eps);

double inputDoubleNumber();
int inputNumber();
bool isNumberNumeric();

double function1(double);
double function2(double);
double function3(double);
double function4(double);

int main(int argc, const char* argv[]) {
    fun f = function1;
    funMethod method[4] = {Simps, TrapezoidFormula, MediumSizedFormula, automaticMethod_2};
    do {
        system("cls");
        double a, b, n = 100, eps = 0.001;
        cout << "Select a function: " << endl
            << "1.4x - 7sin(x)" << endl
            << "2.x^2 - 10(sin(x))^2 + 2" << endl
            << "3.ln(x) - 5cosx" << endl
            << "4.(e^x)/(x^3) - (sin(x))^3 - 2" << endl
            << "Exit" << endl;
        switch (_getch()) {
        case '1': {
            f = function1;
            a = -2;
            b = 3;
            break;
        }
        case '2': {
            f = function2;
            a = 0;
            b = 3;
            break;
        }
        case '3': {
            f = function3;
            a = 1;
            b = 8;
            break;
        }
        case '4': {
            f = function4;
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
            cout << "Enter values:" << endl
                << "\na = ";
            a = inputNumber();
            cout << "\nb = ";
            b = inputNumber();
            cout << "\nn = ";
            n = inputNumber();
            cout << "\neps = ";
            eps = inputDoubleNumber();
        }
        system("cls");
        cout << "With the parametrs:\na = " << a << "\nb = " << b << "\nn = " << n << "\ne = " << eps << "\n\n";
        cout << "_________________________________________________________________________________________" << endl
            << setw(6) << "|" << setw(20) << left << " Simpons" << "|"
            << setw(20) << "Trapezoid" << "|"
            << setw(20) << "Medium sized" << "|"
            << setw(20) << "Automatic" << "|" << endl
        //<< setw(20) << "Gauss(2)" << "|" << endl;
            << "-----+--------------------+--------------------+--------------------+--------------------+" << endl
            << setw(5) << "N" << "|"
            << setw(20) << Simps(f, a, b, n) << "|"
            << setw(20) << TrapezoidFormula(f, a, b, n) << "|"
            << setw(20) << MediumSizedFormula(f, a, b, n) << "|"
            << setw(20) << automaticMethod_2(f, a, b, n) << "|" << endl
            // << setw(20) << GaussMethod_2(f, a, b, n) << "|" << endl
            << "-----+--------------------+--------------------+--------------------+--------------------+" << endl
            << setw(5) << "EPS" << "|"
            << setw(20) << AccordingToTheSpecifiedAccuracy(f, method[0], a, b, eps) << "|"
            << setw(20) << AccordingToTheSpecifiedAccuracy(f, method[1], a, b, eps) << "|"
            << setw(20) << AccordingToTheSpecifiedAccuracy(f, method[2], a, b, eps) << "|"
            << setw(20) << AccordingToTheSpecifiedAccuracy(f, method[3], a, b, eps) << "|" << endl
             //<< setw(20) << GaussMethod_2_AccordingToTheSpecifiedAccuracy(f,a,b,eps) << endl
            << "==========================================================================================" << endl;
        _getch();
    } while (true);
}




int inputNumber() {
    int number;
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


double inputDoubleNumber() {
    double number;
    while (true) {
        cin >> number;
        if (isNumberNumeric()) {
            return number;
        }

    }
}

double TrapezoidFormula(fun f,double a, double b, int n) {

    double sum = 0, h;
    if (0 == n) return sum;

    h = (b - a) / n;
    for (int i = 2; i < n; ++i) {
        sum += f(a + i * h);
    }
    sum += (f(a) + f(b)) / 2;
    sum *= h;
    return sum;
}
double TrapezoidFormulaAccordingToTheSpecifiedAccuracy(fun f,double a, double b, double e) {
    int n = 2;
    double I1;
    double I2 = TrapezoidFormula(f,a,b,n);
    do {
        n *= 2;
       
        I1 = I2;
        I2 = TrapezoidFormula(f, a, b, n);

       
    } while (fabs(I1 - I2) > e);
    return I2;
}

double Simps(fun f,double a, double b, int n) {
    double sum = 0, h;
    if (0 == n) return sum;
    h = (b - a) / n;
    for (int i = 1; i <= n; i++) {
        sum += f(a) + 4 * f(a + h / 2) + f(a + h);
        a += h;
    }
    return sum * h / 6;
}


double SimpsAccordingToTheSpecifiedAccuracy(fun f,double a, double b, double eps) {
    int n1 = 2, pogr;
    double Integral_1;
    double Integral_2 = Simps(f,a, b, n1);
    do {
        n1 *= 2;
        
       
        Integral_1 = Integral_2;
        Integral_2 = Simps(f,a, b, n1);
    } while (fabs(Integral_2 - Integral_1) > eps);
    return Integral_2;
}

double MediumSizedFormulaAccordingToTheSpecifiedAccuracy(fun f, double a, double b, double eps) {
    int n1 = 2;
    double Integral_1;
    double Integral_2 = MediumSizedFormula(f, a, b, n1);
    do {
        n1 *= 2;


        Integral_1 = Integral_2;
        Integral_2 = MediumSizedFormula(f, a, b, n1);
    } while (fabs(Integral_2 - Integral_1) > eps);
    return Integral_2;
}
double MediumSizedFormula(fun f, double a, double b, int n) {

    double sum = 0, h;
    if (0 == n) return sum;

    h = (b - a) / n;
    for (a;a < b;a+=h) {
        sum += f((a + a + h) / 2);
    }
    sum *= h;
    return sum;
}

double automaticMethod_2(fun f, double a, double b, int n) {
    double Integral_1 = TrapezoidFormula(f, a, b, n);
    double Integral_2 = MediumSizedFormula(f, a, b, n);
    return (Integral_1 + 2 * Integral_2) / 3;
}

double automaticMethod_2AccordingToTheSpecifiedAccuracy(fun f, double a, double b, double eps) {
    int n = 2;
    double Integral_1 = TrapezoidFormula(f,a,b,n);
    double Integral_2 = MediumSizedFormula(f, a, b, n);
    while (fabs(Integral_2 - Integral_1) > eps) {
        n *= 2;


        Integral_1 = Integral_2;
        Integral_2 = MediumSizedFormula(f, a, b, n);
    } 
    return (Integral_1 + 2 * Integral_2) / 3;
}

//double GaussMethod_2(fun f, double a, double b, double n) {
//    double numberGauss = 0.5773502592;
//    double h = (b - a) / n;
//    double x = a;
//    double x1 = x + 1 / 2. - (h / 2) * numberGauss;
//    double x2 = x + 1 / 2. + (h / 2) * numberGauss;
//    double result = 0;
//    for (int i = 1;i < n;i++) {
//        result += f(x1) + f(x2);
//        x += h;
//        x1 = x + 1. / 2. - (h / 2) * numberGauss;
//        x2 = x + 1. / 2. + (h / 2) * numberGauss;
//        
//    }
//    return (result * h / 2);
//}
//
//double GaussMethod_2_AccordingToTheSpecifiedAccuracy(fun f, double a, double b, double eps) {
//    int n = 2;
//    double Integral_1;
//    double Integral_2 = GaussMethod_2(f, a, b, n);
//    do {
//        n *= 2;
//
//
//        Integral_1 = Integral_2;
//        Integral_2 = GaussMethod_2(f, a, b, n);
//    } while (fabs(Integral_2 - Integral_1) > eps);
//    return Integral_2;
//}

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
    return exp(x) / pow(x, 3) - pow(sin(x), 3) - 2;
}



double AccordingToTheSpecifiedAccuracy(fun f, funMethod method, double a, double b, double e) {
    int n = 2;
    double I1;
    double I2 = method(f, a, b, n);
    do {
        n *= 2;

        I1 = I2;
        I2 = method(f, a, b, n);


    } while (fabs(I1 - I2) > e);
    return I2;
}