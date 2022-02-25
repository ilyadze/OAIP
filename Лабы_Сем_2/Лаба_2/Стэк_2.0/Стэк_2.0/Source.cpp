#include <iostream>
#include <conio.h>

using namespace std;

struct Stack {
	int info;
	Stack* next;
};


void ViewR(Stack*);
void View(Stack*);
Stack* InStack(Stack*, int);
Stack* OutStack(Stack*, int*);
void Del_All(Stack**);
void Sort_info(Stack*);
int searchMax(Stack*);
int searchMin(Stack*);
Stack* DistanceBetweenMinMax(Stack*,int, int);
int sizeOfStack(Stack*);


int main()
{
	srand(time(NULL));
	Stack* begin = NULL;
	cout << "Enter stack size" << endl;
	int stackSize;
	cin >> stackSize;
	cout << "Select stack fill option" << endl
		<< "1.By hand" << endl
		<< "In other cases,the computer" << endl;
	if (_getch() == '1')
	{
		cout << "Fill stack" << endl;
		for (int i = 0; i < stackSize;i++)
		{
			int stackElement;
			cin >> stackElement;
			begin = InStack(begin, stackElement);
		}
	}
	else
	{
		for (int i = 0;i < stackSize;i++)
		{
			int stackElement;
			stackElement = rand() % 21 - 10;
			begin = InStack(begin, stackElement);
		}
	}
	View(begin);
	int maxElement, minElement;
	maxElement = searchMax(begin);
	minElement = searchMin(begin);
	if (maxElement == minElement)
	{
		cout << "\nError, all elements are equals" << endl;
		return 0;
	}
	if (abs(minElement - maxElement) == 1)
	{
		cout << "\nMin and Max elements are next to each other" << endl;
		return 0;
	}
	begin = DistanceBetweenMinMax(begin, minElement, maxElement);
	cout << "New Stack:";
	ViewR(begin);
	cout << "\nSize of new Stack - " << sizeOfStack(begin);
}


Stack* InStack(Stack* p, int in) {
	Stack* t = new Stack;
	t->info = in;
	t->next = p;
	return t;
}

void View(Stack* p) {
	Stack* t = p;
	cout << "\nStack: ";
	while (t != NULL) {
		cout << t->info << " ";
		t = t->next;
	}
	cout << endl;
}
void ViewR(Stack* p)
{
	if (p != NULL)
	{
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

void Del_All(Stack** p) {
	Stack* t;
	while (*p != NULL) {
		t = *p;
		*p = (*p)->next;
		delete t;
	}
}

void Sort_info(Stack* p) {
	Stack* t = NULL, * t1;
	int r;
	do {
		for (t1 = p; t1->next != t; t1 = t1->next)
			if (t1->info > t1->next->info) {
				r = t1->info;
				t1->info = t1->next->info;
				t1->next->info = r;
			}
		t = t1;
	} while (p->next != t);
}

int searchMax(Stack* p)
{
	if (p == NULL)
	{
		return NULL;
	}
	int indexOfMaxElement,maxElement = p->info,i = 0;
	while (p != NULL)
	{
		if (p->info > maxElement)
		{
			maxElement = p->info;
			indexOfMaxElement = i;
		}
		i++;
		p = p->next;
	}
	return indexOfMaxElement;
}

int searchMin(Stack* p)
{
	if (p == NULL)
	{
		return NULL;
	}
	int indexOfMinElement, minElement = p->info, i = 0;
	while (p != NULL)
	{
		if (p->info < minElement)
		{
			minElement = p->info;
			indexOfMinElement = i;
		}
		i++;
		p = p->next;
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
	Del_All(&t);
	return newStack;
}


int sizeOfStack(Stack* begin)
{
	int sizeOfStack = 0;
	while (begin != NULL)
	{
		sizeOfStack++;
		begin = begin->next;
	}
	return sizeOfStack;
}