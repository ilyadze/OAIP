#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

struct Spis
{
	int info;
	Spis* next, * prev;
};

Spis* createNewSpis(Spis*, Spis**);
Spis* InEnd(Spis*,int);
Spis* InBegin(Spis*, int);
int* searchMax(Spis*, int&);
int* searchMin(Spis*, int&);
void View(Spis*);
void ViewFromTheEnd(Spis*);
Spis* Delete_All(Spis*);
Spis* Delete(Spis*);
Spis* Delete(Spis*,int);
Spis* DistanceBetweenMinMax(Spis*, int, int);
void SortInfoInDescendingOrder(Spis*);
void SortInfoInAscendingOrder(Spis*);
bool isNumberNumeric();
int inputNumber();
Spis* copy(Spis*, Spis*&);
void viewElements(Spis*, int*);
int sizeOfSpis(Spis*);
int* resizeArray(int, int, int*);

int main() {	
	srand(time(NULL));
	do {
		bool IsExit = false;
		Spis* begin, * end;
		begin = end = NULL;
		begin = createNewSpis(begin, &end);
		cout << "Enter list size" << endl;
		int stackSize;
		stackSize = inputNumber();
		if (stackSize <= 0)	{
			break;
		}
		cout << "Select list fill option" << endl
			<< "1.By hand" << endl
			<< "2.The computer" << endl
			<< "Exit" << endl;
		switch (_getch()) {
		case '1': {
			cout << "Fill list" << endl;
			for (int i = 0; i < stackSize;i++) {
				int stackElement;
				stackElement = inputNumber();
				if (stackElement <= 0) {
					break;
				}
				end = InEnd(end, stackElement);
			}
			break;
		}
		case '2': {
			for (int i = 0;i < stackSize;i++) {
				int stackElement;
				stackElement = rand() % 21 - 10;
				end = InEnd(end, stackElement);
			}
			break;
		}
		default: {
			return NULL;
		}
		}
		begin = Delete(begin);
		cout << "List: ";
		View(begin);
		_getch();
		Spis* modifiedBegin = NULL,* modifiedEnd = NULL;
		modifiedBegin = copy(begin, modifiedEnd);
		do {
			system("cls");
			bool isEdit = false;
			cout << "Select array action ortion:" << endl
				<< "1.Add element" << endl
				<< "2.View" << endl
				<< "3.Sort" << endl
				<< "4.Remove one element" << endl
				<< "5.Individual task" << endl
				<< "6.Creating a new list" << endl
				<< "Exit" << endl;
			switch (_getch()) {
			case '1': {
				system("cls");
				int info;
				cout << "Enter info" << endl;
				info = inputNumber();
				if (info <= 0) {
					break;
				}
				cout << "Select add option" << endl
					<< "1.To the begging" << endl
					<< "2.To the end" << endl;
				switch (_getch()) {
				case '1': {
					modifiedBegin = InBegin(modifiedBegin, info);
					break;
				}
				case '2': {
					modifiedBegin = InEnd(modifiedBegin, info);
					break;
				}
				}
				isEdit = true;
				break;
			}
			case '2': {
				cout << "Select view option" << endl
					<< "1.From the begin" << endl
					<< "2.From the end" << endl;
				switch (_getch()) {
				case '1': {
					View(begin);
					break;
				}
				case '2': {
					ViewFromTheEnd(end);
					break;
				}
				}
				
				_getch();
				break;
			}
			case '3': {
				system("cls");
				cout << "1.In descending order" << endl
					<< "2.In ascending order" << endl
					<< "Back" << endl;
				switch (_getch()) {
				case '1': {
					SortInfoInDescendingOrder(modifiedBegin);
					isEdit = true;
					break;
				}
				case '2': {
					SortInfoInAscendingOrder(modifiedBegin);
					isEdit = true;
					break;
				}
				}

				break;
			}
			case '4': {
				cout << "Enter the number of the element to be removed" << endl;
				int numberOfDeletedElement;
				numberOfDeletedElement = inputNumber();
				if (numberOfDeletedElement <= 0) {
					break;
				}
				begin = Delete(begin, numberOfDeletedElement);
				isEdit = true;
				break;
			}
			case '5': {
				/*int maxElement, minElement;
				maxElement = searchMax(begin);
				minElement = searchMin(begin);
				if (maxElement == minElement)
				{
					cout << "\nError, all elements are equals" << endl;
					_getch();
					break;
				}
				if (abs(minElement - maxElement) == 1)
				{
					cout << "\nMin and Max elements are next to each other" << endl;
					_getch();
					break;
				}
				modifiedBegin = DistanceBetweenMinMax(modifiedBegin, minElement, maxElement);
				isEdit = true;
				break;*/

				int* maxElement, * minElement;
				int numberOfMaxElements = 0, numberOfMinElements = 0;
				maxElement = searchMax(begin, numberOfMaxElements);
				minElement = searchMin(begin, numberOfMinElements);
				int indexOfMaxElement = 0, indexOfMinElement = 0;
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
				modifiedBegin = DistanceBetweenMinMax(modifiedBegin, minElement[indexOfMinElement], maxElement[indexOfMaxElement]);
				system("cls");
				//cout << "Old ";
				//View(begin);
				//cout << "\nNew ";
				//View(modifiedBegin);
				cout << "\nSize of new Stack - " << sizeOfSpis(modifiedBegin) << endl;
				isEdit = true;
				break;
			}
			case '6': {
				IsExit = true;
				break;
			}
			default: {
				return NULL;
			}
			}
			if (isEdit) {
				cout << "\nOld: " << endl;
				View(begin);
				cout << "\nNew: " << endl;
				View(modifiedBegin);
				cout << "\nIf you want to work with new list, press '1'" << endl;
				if (_getch() == '1') {
					Delete_All(begin);
					begin = copy(modifiedBegin, end);
				}
				else {
					Delete_All(modifiedBegin);
					modifiedBegin = copy(begin, modifiedEnd);
				}
			}
		} while (!IsExit);
		begin = Delete_All(begin);
	} while (true);

}


Spis* createNewSpis(Spis* begin, Spis** end) {
	*end = new Spis;
	(*end)->info = 6;
	(*end)->prev = (*end)->next = NULL;
	return *end;
}

Spis* InEnd(Spis* end,int in)
{
	Spis* t = new Spis;
	t->info = in;
	t->next = NULL;
	t->prev = end;
	end->next = t;
	return t;
}

Spis* InBegin(Spis* begin,int in)
{
	Spis* t = new Spis;
	t->info = in;
	t->prev = NULL;
	t->next = begin;
	begin->prev = t;
	return t;
}

void View(Spis* begin)
{
	if (begin == NULL)
	{
		cout << "Error,list is clear!" << endl;
	}
	while (begin != NULL)
	{
		cout << begin->info << " ";
		begin = begin->next;
	}
}

void ViewFromTheEnd(Spis* end)
{
	while (end != NULL)
	{
		cout << end->info << " ";
		end = end->prev;
	}
	cout << endl;
}

Spis* Delete_All(Spis* begin)
{
	Spis* t;
	while (begin != NULL)
	{
		t = begin;
		begin = begin->next;
		delete t;
	}
	return begin;
}

Spis* Delete(Spis* begin)
{
	Spis* t = begin;
	(begin->next)->prev = begin->prev;
	begin = begin->next;
	delete t;
	return begin;
}

Spis* Delete(Spis* begin,int index)
{
	Spis* t = begin;
	for (int i = 1;i < index && t != NULL;i++) {
		t = t->next;
	}
	if (t != NULL) {
		if (t->next != NULL) {
			(t->next)->prev = t->prev;
		}
		if (t->prev != NULL) {
			(t->prev)->next = t->next;
		}
		delete t;
	}
	return begin;
}

//int searchMax(Spis* begin)
//{
//	if (begin == NULL)
//	{
//		return NULL;
//	}
//	int maxElement = begin->info,indexOfMaxElement = 0, i = 0;
//	while (begin != NULL)
//	{
//		if (begin->info > maxElement)
//		{
//			maxElement = begin->info;
//			indexOfMaxElement = i;
//		}
//		begin = begin->next;
//		i++;
//	}
//	return indexOfMaxElement;
//}
//
//int searchMin(Spis* begin)
//{
//	if (begin == NULL)
//	{
//		return NULL;
//	}
//	int minElement = begin->info, indexOfMinElement = 0, i = 0;
//	while (begin != NULL)
//	{
//		if (begin->info < minElement)
//		{
//			minElement = begin->info;
//			indexOfMinElement = i;
//		}
//		begin = begin->next;
//		i++;
//	}
//	return indexOfMinElement;
//}

Spis* DistanceBetweenMinMax(Spis* p, int min, int max)
{
	Spis* begin = p,*t;
	bool flag = false;
	int i = 0;
	if (max < min)
	{
		int maxNumber = min;
		min = max;
		max = maxNumber;
	}
	while (p != NULL)
	{
		if (i >= min && i <= max)
		{
			t = p;
			if (p->prev == NULL && p->next != NULL)
			{
				(p->next)->prev = NULL;
				begin = p->next;
			}
			else
			{
				if (p->next == NULL && p->prev != NULL)
				{
					(p->prev)->next = NULL;
				}
				else 
				{
					if (p->prev != NULL && p->next != NULL)
					{
						(p->prev)->next = p->next;
						(p->next)->prev = p->prev;
					}
					else
					{
						p = NULL;
						break;
					}
				}
				
			}
			p = p->next;
			delete t;
			i++;
			flag = true;
			continue;
		}
		if(flag)
		{
			break;
		}
		p = p->next;
		i++;
	}
	return begin;
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

void SortInfoInAscendingOrder(Spis* p) {
	Spis* t = NULL, * t1;
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

void SortInfoInDescendingOrder(Spis* p) {
	Spis* t = NULL, * t1;
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



Spis* copy(Spis* begin,Spis*& newEnd) {
	Spis* newBegin = NULL;
	newBegin = createNewSpis(newBegin, &newEnd);
	while (begin != NULL) {
		newEnd = InEnd(newEnd, begin->info);
		begin = begin->next;
	}
	newBegin = Delete(newBegin);
	return newBegin;
}

void viewElements(Spis* begin, int* elements) {
	cout << "Stack: ";
	int i = 0, j = 0;
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


int* searchMax(Spis* begin, int& numberOfMaxElements) {
	if (begin == NULL) {
		return NULL;
	}
	int maxElement = begin->info;
	Spis* p = begin;
	while (begin != NULL) {
		if (begin->info > maxElement) {
			maxElement = begin->info;
		}
		begin = begin->next;
	}
	int size = sizeOfSpis(p);
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

int* searchMin(Spis* begin, int& numberOfMinElements)
{
	if (begin == NULL) {
		return NULL;
	}
	int minElement = begin->info;
	Spis* p = begin;
	while (begin != NULL) {
		if (begin->info < minElement) {
			minElement = begin->info;
		}
		begin = begin->next;
	}
	int size = sizeOfSpis(p);
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


int sizeOfSpis(Spis* begin) {
	int sizeOfStack = 0;
	while (begin != NULL)
	{
		sizeOfStack++;
		begin = begin->next;
	}
	return sizeOfStack;
}

int* resizeArray(int oldSize, int newSize, int* array) {
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