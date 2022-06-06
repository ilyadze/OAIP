#include <iostream>
#include <conio.h>

using namespace std;

int nod(int, int);
int Nod(int, int);
int nodThroughTheLoop(int, int);
int NumberOfDigits(int);
int NumberOfArmstrong(int, int);
int NumberOfArmstrong_2(int, int);
int inputNumber();
bool isNumberNumeric();

int main() {
	do {
		system("cls");
		cout << "Select task option" << endl
			<< "1.Nod" << endl
			<< "2.Number of Armstrong" << endl
			<< "Exit" << endl;
		switch (_getch()) {
		case '1': {
			system("cls");
			int numberOne, numberTwo;
			cout << "Enter first number" << endl;
			numberOne = inputNumber();
			cout << "Enter second number" << endl;
			numberTwo = inputNumber();
			cout << "nod = " << nod(numberOne,numberTwo) << endl;
			cout << "Nod = " << Nod(numberOne, numberTwo) << endl;
			cout << "Nod(through the loop) = " << nodThroughTheLoop(numberOne, numberTwo) << endl;
			_getch();
			break;
		}
		case '2': {
			system("cls");
			int number;
			cout << "Enter number" << endl;
			number = inputNumber();
			int numberOfDigits = NumberOfDigits(number);
			cout << "Number of digits - " << numberOfDigits << endl;
			cout << "Number of Armstrong - " << NumberOfArmstrong(number, numberOfDigits) << endl;
			cout << "Number of Armstrong(2) - " << NumberOfArmstrong_2(number, numberOfDigits) << endl;
			_getch();
			break;
		}
		default: {
			cout << "If you want to exit, press '1'" << endl;
			if (_getch() == '1') {
				return 0;
			}
		}
		}
	} while (true);
}

int Nod(int firstNumber, int secondNumber) {
	return firstNumber ? Nod(secondNumber % firstNumber, firstNumber) : secondNumber;
}

int nodThroughTheLoop(int firstNumber, int secondNumber) {
	while (secondNumber != 0) {
		firstNumber = Nod(secondNumber, firstNumber % secondNumber);
		secondNumber = firstNumber % secondNumber;
		
	}
	return firstNumber;
}

int NumberOfDigits(int number) {
	int numberOfDigits = 0;
	if (number >= 1) {
		numberOfDigits = NumberOfDigits(number / 10);
		numberOfDigits++;
	}
	return numberOfDigits;
}

int NumberOfArmstrong(int number, int numberOfDigits) {
	int numberOfArmstrong = 0;
	if (number >= 1) {
		numberOfArmstrong = NumberOfArmstrong(number / 10, numberOfDigits);
		numberOfArmstrong += pow(number % 10, numberOfDigits);
	}
	return numberOfArmstrong;
}

int NumberOfArmstrong_2(int number, int numberOfDigits) {
	int numberOfArmstrong = 0;
	while (number >= 1) {
		numberOfArmstrong += pow(number % 10, numberOfDigits);
		number /= 10;
	}
	return numberOfArmstrong;
}

int nod(int firstNumber, int secondNumber) {
	int max = firstNumber > secondNumber ? firstNumber : secondNumber;
	int i = 2;
	int result = 1;
	while (i < max / 2) {
		if (!(firstNumber % i) && !(secondNumber % i)) {
			int j = 2, H = 0;
			while (j < i/2) {
				if (!i % j) {
					H++;
				}
				j++;
			}
			if (H == 0) {
				while (firstNumber % i == 0 && secondNumber % i == 0) {
					result *= i;
					firstNumber /= i;
					secondNumber /= i;
				}
			}
		}
		i++;
	}
	return result;
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
		system("cls");
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error, incorrect input" << endl;
		system("pause");
		return false;
	}
}