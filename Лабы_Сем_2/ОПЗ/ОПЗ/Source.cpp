#include <iostream>
#include <conio.h>

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
double formulaCalculation(char*, Stack*);

int main()
{
	do {
		system("cls");
		bool IsExit = false;
		char symbol, In[50], Out[50];
		int i = 0, j = 0;
		cout << "Input formula: ";
		gets_s(In);
		char* PolishEntry = creatingPolishEntry(In);
		do {
			system("cls");
			cout << "Enter option to polish entry" << endl
				<< "1.View polish entry" << endl
				<< "2.Calculation formula" << endl
				<< "3.Create new polish entry" << endl
				<< "Exit the programm" << endl;
			switch (_getch()) {
			case '1': {
				system("cls");
				cout << "Normal entry - " << In << endl
					<< "Polish entry - " << PolishEntry << endl;
				_getch();
				break;
			}
			case '2': {
				system("cls");
				Stack* symbols = getInfoForSymbol(PolishEntry);
				cout << "Result of calculation = " << formulaCalculation(PolishEntry, symbols);
				_getch();
				break;
			}
			case '3': {
				IsExit = true;
				break;
			}
			default: {
				return 0;
			}
			}
		} while (!IsExit);
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
		if (formula[i] >= 'a' && formula[i] < 'z')
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
			symbols = InSymbol(symbols, entry[i]);
			cout << entry[i] << " = ";
			cin >> symbols->info;
		}
	}
	return symbols;
}

double formulaCalculation(char* polishEntry, Stack* symbols) {
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
				variables->info = secondSymbol / firstSymbol;
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