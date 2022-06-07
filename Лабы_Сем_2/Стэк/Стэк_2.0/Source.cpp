#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

struct Stack {
	int info;
	Stack* next;
};


void ViewR(Stack*);
void View(Stack*);
Stack* InStack(Stack*, int);
Stack* OutStack(Stack*, int*);
void Delete_All(Stack**);
void SortInfoInAscendingOrder(Stack*);
void SortInfoInDescendingOrder(Stack*);
int* searchMax(Stack*, int&);
int* searchMin(Stack*, int&);
Stack* DistanceBetweenMinMax(Stack*,int, int);
int sizeOfStack(Stack*);
void copyInformationToNewStack(Stack*,Stack*&);
Stack* deleteNegativeNumber(Stack*);
int inputNumber();
bool isNumberNumeric();
Stack* reverseStack(Stack*);
void viewElements(Stack*, int*);
int* resizeArray(int, int, int*);

int main() {
	srand(time(NULL));
	Stack* begin = NULL;
	do {	
		system("cls");
		
		cout << "Enter stack size" << endl;
		int stackSize;
		stackSize = inputNumber();
		if (stackSize <= 0) {
			break;
		}
		bool isExitInProgram = false;
		system("cls");
		cout << "Select stack fill option" << endl
			<< "1.By hand" << endl
			<< "2.Computer" << endl
			<< "Exit the programm" << endl;
		switch (_getch()) {
		case '1': {
			cout << "Fill stack" << endl;
			for (int i = 0; i < stackSize;i++) {
				int stackElement;
				stackElement = inputNumber();
				begin = InStack(begin, stackElement);
			}
			break;
		}
		case '2': {
			for (int i = 0;i < stackSize;i++) {
				int stackElement;
				stackElement = rand() % 21 - 10;
				begin = InStack(begin, stackElement);
			}
			break;
		}
		default: {
			isExitInProgram = true;
			break;
		}
		}
		if (isExitInProgram) {
			break;
		}
		system("cls");
		View(begin);
		_getch();
		do {
			system("cls");
			bool isExit = false,isEdit = false;
			Stack* newBegin;
			copyInformationToNewStack(begin, newBegin);
			cout << "Select the option to work with stack:" << endl
				<< "1.Sort information" << endl
				<< "2.Add element to stack" << endl
				<< "3.Delete element with min max elements" << endl
				<< "4.Delete negative number" << endl
				<< "5.Back to create stack" << endl
				<< "Exit" << endl;
			switch (_getch()) {
			case '1': {
				system("cls");
				bool isBack = false;
				cout << "1.In descending order" << endl
					<< "2.In ascending order" << endl
					<< "Back" << endl;
				switch (_getch()) {
				case '1': {
					SortInfoInDescendingOrder(newBegin);
					break;
				}
				case '2': {
					SortInfoInAscendingOrder(newBegin);
					break;
				}
				default: {
					isBack = true;
				}
				}
				if (!isBack) {
					cout << "Old ";
					View(begin);
					cout << "\nNew ";
					View(newBegin);
					isEdit = true;
					_getch();
				}
				break;
			}
			case '2': {
				system("cls");
				cout << "Enter the number of elements" << endl;
				int number;
				number = inputNumber();
				for (int i = 0;i < number;i++) {
					cout << "Enter number" << endl;
					int info;
					info = inputNumber();
					begin = InStack(begin, info);
				}
				cout << "New ";
				View(begin);
				break;
			}
			case '3': {
				int* maxElement,* minElement;
				int numberOfMaxElements = 0, numberOfMinElements = 0;
				maxElement = searchMax(newBegin,numberOfMaxElements);
				minElement = searchMin(newBegin,numberOfMinElements);
				int indexOfMaxElement = 0, indexOfMinElement = 0;
				viewElements(begin, maxElement);
				if (numberOfMaxElements != 1) {
					system("cls");
					viewElements(begin, maxElement);
					cout << "Enter max element" << endl;
					indexOfMaxElement = inputNumber();
					if (indexOfMaxElement <= 0) {
						break;
					}
					indexOfMaxElement--;
				}
				if (numberOfMinElements != 1) {
					system("cls");
					viewElements(begin, minElement);
					cout << "Enter min element" << endl;
					indexOfMinElement = inputNumber();
					if (indexOfMinElement <= 0) {
						break;
					}
					indexOfMinElement--;
				}
				
				if (maxElement[indexOfMinElement] == minElement[indexOfMinElement]) {
					system("cls");
					cout << "Error, all elements are equals" << endl;
					_getch();
					break;
				}
				if (abs(minElement[indexOfMinElement] - maxElement[indexOfMaxElement]) == 1) {
					system("cls");
					cout << "Min and Max elements are next to each other" << endl;
					_getch();
					break;
				}
				newBegin = DistanceBetweenMinMax(newBegin, minElement[indexOfMinElement], maxElement[indexOfMaxElement]);
				newBegin = reverseStack(newBegin);
				system("cls");
				cout << "Old ";
				View(begin);
				cout << "New ";
				View(newBegin);
				cout << "\nSize of new Stack - " << sizeOfStack(newBegin) << endl;
				isEdit = true;
				_getch();
				break;
			}
			case '4': {
				system("cls");
				newBegin = deleteNegativeNumber(newBegin);
				newBegin = reverseStack(newBegin);
				cout << "Old";
				View(begin);
				cout << "New ";
				View(newBegin);
				isEdit = true;
				_getch();
				break;
			}
			case '5': {
				isExit = true;
				break;
			}
			default: {
				return 0;
			}
			}
			if (isExit) {
				Delete_All(&newBegin);
				break;
			}
			if (isEdit) {
				cout << "If you want to work with the new stack press 1" << endl;
				if (_getch() == '1') {
					Delete_All(&begin);
					copyInformationToNewStack(newBegin, begin);
				}
			}
			Delete_All(&newBegin);
			
		} while (true);
		Delete_All(&begin);
	} while (true);
	Delete_All(&begin);
}


Stack* InStack(Stack* p, int in) {
	Stack* t = new Stack;
	t->info = in;
	t->next = p;
	return t;
}

void View(Stack* p) {
	cout << "Stack: ";
	while (p != NULL) {
		cout << p->info << " ";
		p = p->next;
	}
	cout << endl;
}
void ViewR(Stack* p) {
	if (p != NULL) {
		ViewR(p->next);
		cout << p->info << " ";
	}
}

Stack* OutStack(Stack* p, int* out) {
	Stack* t = p;
	*out = p->info;
	p = p->next;
	delete t;
	return p;
}

void Delete_All(Stack** p) {
	Stack* t;
	while (*p != NULL) {
		t = *p;
		*p = (*p)->next;
		delete t;
	}
}

void SortInfoInAscendingOrder(Stack* p) {
	Stack* t = NULL, * t1;
	int r;
	do {
		for (t1 = p; t1->next != t; t1 = t1->next) {
			if (t1->info > t1->next->info) {
				r = t1->info;
				t1->info = t1->next->info;
				t1->next->info = r;
			}
		}
		t = t1;
	} while (p->next != t);
}

void SortInfoInDescendingOrder(Stack* p) {
	Stack* t = NULL, * t1;
	int r;
	do {
		for (t1 = p; t1->next != t; t1 = t1->next) {
			if (t1->info < t1->next->info) {
				r = t1->info;
				t1->info = t1->next->info;
				t1->next->info = r;
			}
		}
		t = t1;
	} while (p->next != t);
}

int* searchMax(Stack* begin,int& numberOfMaxElements) {
	if (begin == NULL) {
		return NULL;
	}
	int maxElement = begin->info;
	Stack* p = begin;
	while (begin != NULL) {
		if (begin->info > maxElement) {
			maxElement = begin->info;
		}
		begin = begin->next;
	}
	int size = sizeOfStack(p);
	int* indexOfMaxElement = new int[size];
	int i = 0, j = 0;
	while (p != NULL) {
		if (p->info == maxElement) {
			indexOfMaxElement[j++] = i;
		}
		i++;
		p = p->next;
	}
	numberOfMaxElements = j;
	if (numberOfMaxElements < size) {
		indexOfMaxElement = resizeArray(size, numberOfMaxElements, indexOfMaxElement);
	}
	return indexOfMaxElement;
}

int* searchMin(Stack* begin,int& numberOfMinElements)
{
	if (begin == NULL) {
		return NULL;
	}
	int minElement = begin->info;
	Stack* p = begin;
	while (begin != NULL) {
		if (begin->info < minElement) {
			minElement = begin->info;
		}
		begin = begin->next;
	}
	int size = sizeOfStack(p);
	int* indexOfMinElement = new int[size];
	int i = 0, j = 0;
	while (p != NULL) {
		if (p->info == minElement) {
			indexOfMinElement[j++] = i;
		}
		i++;
		p = p->next;
	}
	numberOfMinElements = j;
	if (numberOfMinElements < size) {
		indexOfMinElement = resizeArray(size, numberOfMinElements, indexOfMinElement);
	}
	
	return indexOfMinElement;
}

Stack* DistanceBetweenMinMax(Stack* p, int min, int max)
{
	Stack* newStack = NULL, * t = p;
	bool flag = false;
	int i = 0;
	while (p != NULL)
	{
		if (i != min && i != max && !flag)
		{
			newStack = InStack(newStack, p->info);
		}
		else
		{
			if (i == min || i == max)
			{
				flag = !flag;
			}
		}
		p = p->next;
		i++;
	}
	Delete_All(&t);
	return newStack;
}

Stack* reverseStack(Stack* begin) {
	Stack* newStack = NULL, *t = begin;
	while (begin != NULL) {
		newStack = InStack(newStack,begin->info);
		begin = begin->next;
	}
	Delete_All(&t);
	return newStack;
}

int sizeOfStack(Stack* begin) {
	int sizeOfStack = 0;
	while (begin != NULL)
	{
		sizeOfStack++;
		begin = begin->next;
	}
	return sizeOfStack;
}

void copyInformationToNewStack(Stack* begin, Stack*& newStack)
{
	if (begin != NULL) {
		copyInformationToNewStack(begin->next, newStack);
		newStack = InStack(newStack, begin->info);
	}
	else {
		newStack = NULL;
	}
}

Stack* deleteNegativeNumber(Stack* p)
{
	Stack* newStack = NULL, * z = p;
	while (z != NULL)
	{
		if (z->info < 0)
		{
			z = z->next;
			continue;
		}
		newStack = InStack(newStack, z->info);
		z = z->next;
	}
	Delete_All(&z);
	return newStack;
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



int* resizeArray(int oldSize, int newSize, int* array)
{
	if (oldSize == newSize)
	{
		return array;
	}
	int* newArray = new int[newSize];
	oldSize = newSize < oldSize ? newSize : oldSize;
	for (int i = 0;i < oldSize;i++)
	{
		newArray[i] = array[i];
	}
	delete[] array;
	return newArray;
}


void viewElements(Stack* begin, int* elements) {
	cout << "Stack: ";
	int i = 0,j = 0;
	while (begin != NULL) {
		
		if (i == elements[j]) {
			cout << "|" << begin->info << "| ";
			j++;
		}
		else {
			cout << begin->info << " ";
		}
		begin = begin->next;
		i++;
	}
	cout << endl;
}

