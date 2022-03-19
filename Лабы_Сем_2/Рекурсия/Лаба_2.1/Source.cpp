#include <iostream>
#include <conio.h>

using namespace std;

int Nod_2(int, int);
int Nod(int, int);
int nodThroughTheLoop(int, int);
int NumberOfDigits(int);
int NumberOfArmstrong(int, int);
int NumberOfArmstrong_2(int, int);

int main()
{
	do
	{
		system("cls");
		cout << "Select task option" << endl
			<< "1.Nod" << endl
			<< "2.Number of Armstrong" << endl
			<< "Exit" << endl;
		switch (_getch())
		{
		case '1':
		{
			system("cls");
			int numberOne, numberTwo;
			cout << "Enter first number" << endl;
			cin >> numberOne;
			cout << "Enter second number" << endl;
			cin >> numberTwo;
			cout << "Nod = " << Nod(numberOne, numberTwo) << endl;
			cout << "Nod(2) = " << Nod_2(numberOne, numberTwo) << endl;
			cout << "Nod(through the loop) = " << nodThroughTheLoop(numberOne, numberTwo) << endl;
		}
		case '2':
		{
			system("cls");
			int number;
			cout << "Enter number" << endl;
			cin >> number;
			int numberOfDigits = NumberOfDigits(number);
			cout << "Number of digits - " << numberOfDigits << endl;
			cout << "Number of Armstrong - " << NumberOfArmstrong(number, numberOfDigits) << endl;
			cout << "Number of Armstrong(2) - " << NumberOfArmstrong_2(number, numberOfDigits) << endl;
		}
		default:
		{
			return 0;
		}
		}
	} while (true);
}

int Nod(int firstNumber, int secondNumber)
{
	return secondNumber ? Nod(secondNumber , firstNumber% secondNumber) : firstNumber;
}

int Nod_2(int firstNumber, int secondNumber)
{
	return firstNumber ? Nod(secondNumber % firstNumber, firstNumber) : firstNumber;
}

int nodThroughTheLoop(int firstNumber, int secondNumber)
{
	while (secondNumber != 0)
	{
		firstNumber = Nod(secondNumber, firstNumber % secondNumber);
		secondNumber = firstNumber % secondNumber;
		
	}
	return firstNumber;
}

int NumberOfDigits(int number)
{
	int numberOfDigits = 0;
	if (number >= 1)
	{
		numberOfDigits = NumberOfDigits(number / 10);
		numberOfDigits++;
	}
	return numberOfDigits;
}

int NumberOfArmstrong(int number, int numberOfDigits)
{
	int numberOfArmstrong = 0;
	if (number >= 1)
	{
		numberOfArmstrong = NumberOfArmstrong(number / 10, numberOfDigits);
		numberOfArmstrong += pow(number % 10, numberOfDigits);
	}
	return numberOfArmstrong;
}

int NumberOfArmstrong_2(int number, int numberOfDigits)
{
	int numberOfArmstrong = 0;
	while (number >= 1)
	{
		numberOfArmstrong += pow(number % 10, numberOfDigits);
		number /= 10;
	}
	return numberOfArmstrong;
}