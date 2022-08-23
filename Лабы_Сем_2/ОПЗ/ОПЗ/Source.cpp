#include <iostream>
#include <conio.h>
#include <Windows.h>


using namespace std;

struct Stack
{
	char symbol;
	double info;
	Stack* Next;
};

int Prior(char);
Stack* InSymbol(Stack*, char);
Stack* OutSymbol(Stack*, char*);
char* creatingPolishEntry(char*);
Stack* getInfoForSymbol(char*);
double formulaCalculation(char*, Stack*,bool&);
char* enteringFormula();
bool symbolIsSuitable(char);
char* resizeArray(int, int, char*);
int inputNumber();
bool isNumberNumeric();
void Delete_All(Stack**);

int main()
{
	setlocale(LC_ALL, "ru");
	do {
		system("cls");
		bool IsExit = false;
		char *In;
		int i = 0, j = 0;
		
		while (true) {
			system("cls");
			cout << "Input formula: ";
			In = enteringFormula();
			if (In[0] == 27) {
				delete[] In;
				cout << "If you want to exit the program, press '1'" << endl;
				if (_getch() == '1') {
					return 0;
				}
				
				continue;
			}
			break;
		}
		char* PolishEntry = creatingPolishEntry(In);
		Stack* symbols = NULL;
		do {
			system("cls");
			cout << "Enter option to polish entry" << endl
				<< "1.View polish entry" << endl
				<< "2.Get info for symbols" << endl
				<< "3.Calculation formula" << endl
				<< "4.Create new polish entry" << endl
				<< "Exit the programm" << endl;
			switch (_getch()) {
			case '1': {
				cout << "Normal - " << In << endl
					<< "Polish - " << PolishEntry << endl;
				_getch();
				break;
			}
			case '2': {
				system("cls");
				if (symbols != NULL) {
					cout << "If you want to change, press 1" << endl;
					if (_getch() == '1') {
						Delete_All(&symbols);
						symbols = getInfoForSymbol(PolishEntry);
					}
				}
				else {
					symbols = getInfoForSymbol(PolishEntry);
				}
				break;
			}
			case '3': {
				system("cls");
				bool isDivisionByZero = false;
				if (symbols == NULL) {
					symbols = getInfoForSymbol(PolishEntry);
				}
				double result = formulaCalculation(PolishEntry, symbols, isDivisionByZero);
				cout << "Normal  - " << In << endl
					<< "Polish  - " << PolishEntry << endl;
				if (!isDivisionByZero) {
					cout << "Result of calculation = " << result;
				}
				else {
					cout << "Error,The expression is divided by zero" << endl;
				}
				_getch();
				break;
			}
			case '4': {
				IsExit = true;
				break;
			}
			default: {
				return 0;
			}
			}
		} while (!IsExit);
		Delete_All(&symbols);
		delete[] In;
		delete[] PolishEntry;
	} while (true);
}

int Prior(char symbol)
{
	switch (symbol)
	{
	case '*': case '/': return 3;
	case '-': case '+': return 2;
	case'(': return 1;
	}
}

Stack* InSymbol(Stack* begin, char symbol)
{
	Stack* t = new Stack;
	t->symbol = symbol;
	t->Next = begin;
	return t;
}

Stack* OutSymbol(Stack* begin, char* s)
{
	Stack* t = begin;
	*s = begin->symbol;
	begin = begin->Next;
	delete t;
	return begin;
}

char* creatingPolishEntry(char* formula) {
	int i = 0,j = 0;
	Stack* t, * begin = NULL;
	char symbol, *Out = new char[50];
	while (formula[i] != '\0')
	{
		if (formula[i] == ')')
		{
			while ((begin->symbol != '('))
			{
				begin = OutSymbol(begin, &symbol);
				if (!begin)
				{
					symbol == '\0';
				}
				Out[j++] = symbol;
			}
			t = begin;
			begin = begin->Next;
			delete t;
		}
		if ((formula[i] >= 'a' && formula[i] <= 'z') || (formula[i] >= 'A' && formula[i] <= 'Z'))
		{
			Out[j++] = formula[i];
		}
		if (formula[i] == '(')
		{
			begin = InSymbol(begin, formula[i]);
		}
		if (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/')
		{
			while (begin != NULL && Prior(begin->symbol) >= Prior(formula[i]))
			{
				begin = OutSymbol(begin, &symbol);
				Out[j++] = symbol;
			}
			begin = InSymbol(begin, formula[i]);
		}
		i++;
	}
	while (begin != NULL)
	{
		begin = OutSymbol(begin, &symbol);
		Out[j++] = symbol;
	}
	Out[j] = '\0';
	return Out;
}

Stack* getInfoForSymbol(char* entry) {
	Stack* symbols = NULL;
	cout << "Enter variable values" << endl;
	for (int i = 0;entry[i] != '\0';i++) {
		if (entry[i] > 64 && entry[i] < 91 || entry[i] > 96 && entry[i] < 123) {
			Stack* checkingSymbols = symbols;
			bool thereIsSymbol = false;
			while (checkingSymbols != NULL) {
				if (checkingSymbols->symbol == entry[i]) {
					thereIsSymbol = true;
					break;
				}
				checkingSymbols = checkingSymbols->Next;
			}
			if (!thereIsSymbol) {
				symbols = InSymbol(symbols, entry[i]);
				cout << entry[i] << " = ";
				symbols->info = inputNumber();
			}
		}
		
	}
	return symbols;
}

double formulaCalculation(char* polishEntry, Stack* symbols, bool& divisionByZero) {
	Stack* variables = NULL,*t;
	for (int i = 0;polishEntry[i] != '\0';i++) {
		t = symbols;
		if(polishEntry[i] == '*' || polishEntry[i] == '/' || polishEntry[i] == '+' || polishEntry[i] == '-') {
			char symbol;
			double firstSymbol = variables->info;
			variables = OutSymbol(variables, &symbol);
			double secondSymbol = variables->info;
			switch (polishEntry[i]) {
			case '*':
				variables->info = firstSymbol * secondSymbol;
				break;
			case '+':
				variables->info = firstSymbol + secondSymbol;
				break;
			case '-':
				variables->info = secondSymbol - firstSymbol;
				break;
			case '/':
				if (firstSymbol == 0) {
					divisionByZero = true;
					return 0;
				}
				else {
					variables->info = secondSymbol / firstSymbol;
				}
				break;
			}
		}
		else{
			variables = InSymbol(variables, polishEntry[i]);
			while(t->symbol != polishEntry[i]) {
				t = t->Next;
			}
			variables->info = t->info;
		}
		
	}
	return variables->info;
}


char* enteringFormula() {
	int size = 100;
	char* formula = new char[size];
	int i = 0, numberOfBracket = 0;
	bool isNotEnoughBracket = false;
	while (true) {
		formula[i] = _getch();
		if (symbolIsSuitable(formula[i])) {
			if (formula[i] == 13) {
				if (formula[i-1] == '+' || formula[i-1] == '-' || formula[i-1] == '*' || formula[i-1] == '/') {
					cout << "\nThe symbols '+','-','*','/' can't be the last" << endl;
					Sleep(3000);
					system("cls");
					cout << "Input formula: ";
					i = 0;
					continue;
				}
				if (numberOfBracket == 0) {
					if (i != 0) {
						break;
					}
					else {
						continue;
					}
				}
				else {
					cout << "\nError, is not enough bracket" << endl;
					Sleep(3000);
					system("cls");
					cout << "Input formula: ";
					i = 0;
					continue;
				}
			}
			if (formula[i] == 27) {
				cout << endl;
				formula[0] = 27;
				return formula;
			}
			if (formula[i] == 8) {
				if (i != 0) {
					cout << "\b \b";
					if (formula[i - 1] == '(') {
						numberOfBracket--;
					}
					if (formula[i - 1] == ')') {
						numberOfBracket++;
					}
					i--;

					continue;
				}
				else {
					continue;
				}
			}
			
			if (i != 0) {
				if (((formula[i] >= 'a' && formula[i] <= 'z') || (formula[i] >= 'A' && formula[i] <= 'Z')) && ((formula[i - 1] >= 'a' && formula[i - 1] <= 'z') || (formula[i - 1] >= 'A' && formula[i - 1] <= 'Z') || formula[i -1] == ')')) {
					continue;
				}
				else {
					if ((formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/') && (formula[i - 1] == '+' || formula[i - 1] == '-' || formula[i - 1] == '*' || formula[i - 1] == '/')) {
						continue;
					}
				}
			}
			if (formula[i] == '(' && (formula[i - 1] == '+' || formula[i - 1] == '-' || formula[i - 1] == '/' || formula[i - 1] == '*' || formula[i-1] == '(' || i == 0)) {
				if (!isNotEnoughBracket) {
					isNotEnoughBracket = true;
				}
				numberOfBracket++;
			}
			else {
				if (formula[i] == '(') {
					continue;
				}
				if (formula[i] == ')') {
					if (numberOfBracket != 0 && formula[i-1] != '(' && i!=0 && ((formula[i-1] >='a' && formula[i-1] <= 'z') || (formula[i-1] >='A' && formula[i-1] <= 'Z'))) {
						if (!isNotEnoughBracket) {
							continue;
						}
						else {
							numberOfBracket--;
						}
					}
					else {
						continue;
					}
				}
			}
			if (i == 0 && (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/')) {
				continue;
			}
			if (numberOfBracket == 0) {
				isNotEnoughBracket = true;
			}
			else {
				isNotEnoughBracket = true;
			}

			cout << formula[i];
			i++;
		}
	}
	formula[i] = '\0';
	formula = resizeArray(size, i + 1, formula);
	return formula;
}

bool symbolIsSuitable(char symbol) {
	if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') || symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '(' || symbol == ')' || symbol == 27 || symbol == 13 || symbol == 8) {
		return true;
	}
	else {
		return false;
	}
}

char* resizeArray(int oldSize, int newSize, char* oldArray) {
	if (oldSize == newSize)
	{
		return oldArray;
	}
	char* newArray = new char[newSize];
	newSize = newSize < oldSize ? newSize : oldSize;
	for (int i = 0;i < newSize;i++)
	{
		newArray[i] = oldArray[i];
	}
	delete[] oldArray;
	return newArray;
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


void Delete_All(Stack** p) {
	Stack* t;
	while (*p != NULL) {
		t = *p;
		*p = (*p)->Next;
		delete t;
	}
}