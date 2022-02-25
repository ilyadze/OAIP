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
Stack* searchMax(Stack*);
Stack* searchMin(Stack*);
Stack* DistanceBetweenMinMax(Stack*, Stack*, Stack*);


int main()
{
	srand(time(NULL));
	Stack* begin = NULL;
	cout << "Enter stack size" << endl;
	int stackSize;
	cin >> stackSize;
	cout << "Select stack fill option" << endl
		<< "1.By hand"<< endl
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
	Stack *maxElement, *minElement;
	maxElement = searchMax(begin);
	minElement = searchMin(begin);
	if (maxElement == minElement)
	{
		cout << "\nError, all elements are equals" << endl;
		return 0;
	}
	if (maxElement->next == minElement || minElement->next == maxElement)
	{
		cout << "\nMin and Max elements are next to each other" << endl;
		return 0;
	}
	cout << "Max element - " << maxElement->info << endl
		<< "Min element - " << minElement->info << endl;
	begin = DistanceBetweenMinMax(begin, minElement, maxElement);
	cout << "New Stack:";
	ViewR(begin);
	cout << "\nSize of new Stack - " << sizeOfStack;
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

Stack* searchMax(Stack* p)
{
	if (p == NULL)
	{
		return NULL;
	}
	Stack* maxElement,*t = p;
	maxElement = t;
	maxElement->info = t->info;
	while (t != NULL)
	{
		if (t->info > maxElement->info)
		{
			maxElement->info = t->info;
			maxElement = t;
		}
		t = t->next;
	}
	return maxElement;
}

Stack* searchMin(Stack* p)
{
	if (p == NULL)
	{
		return NULL;
	}
	Stack* minElement = NULL,*t=p;
	int indexOfMinimumElement = 0,i = 0,min;
	while (t != NULL)
	{
		if (t->info < minElement->info)
		{
			minElement = InStack(minElement, t->info);
			min = t->info;
			indexOfMinimumElement = i;
		}
		t = t->next;
		i++;
	}
	return minElement;
}

Stack* DistanceBetweenMinMax(Stack* p, Stack* min, Stack* max)
{
	Stack* newStack = NULL,*t = p;
	bool flag = false;
	while (p != NULL)
	{
		if (p != min && p != max && !flag)
		{
			newStack = InStack(newStack, p->info);
			p = p->next;
		}
		else
		{
			if (p == min || p == max)
			{
				flag = !flag;
			}
		}
		p = p->next;
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

//Stack* DistanceBetweenMinMax(Stack* p, Stack* min, Stack* max)
//{
//	Stack* newStack = NULL, * t = p;
//	bool flag = false;
//	while (p != NULL)
//	{
//		if (p == min || p == max)
//		{
//			flag = !flag;
//			p = p->next;
//			continue;
//		}
//		if (flag)
//		{
//			p = p->next;
//			continue;
//		}
//		newStack = InStack(newStack, p->info);
//		p = p->next;
//	}
//	Del_All(&t);
//	return newStack;
//}

//Stack* DistanceBetweenMinMax(Stack* p, Stack* min, Stack* max)
//{
//	Stack* newStack = NULL, * t = p->next,*b = p;
//	bool flag = false;
//	while (t != NULL)
//	{
//		if (t == min || t == max)
//		{
//			flag = !flag;
//			b->next = t->next;
//			delete t;
//			t = b->next;
//			continue;
//		}
//		if (flag)
//		{
//			b->next = t->next;
//			delete t;
//			t = b->next;
//			continue;
//		}
//		b = t;
//		t = t->next;
//	}
//	//Del_All(&t);
//	return p;
//}
//Stack* DistanceBetweenMinMax(Stack* p, Stack min, Stack max)
//{
//	Stack* newStack = NULL, * t = p;
//	bool flag = false;
//	while (p != NULL)
//	{
//		if (p == min.next || p == max.next)
//		{
//			flag = !flag;
//			
//		}
//		if (flag)
//		{
//			p = p->next;
//			continue;
//		}
//		newStack = InStack(newStack, p->info);
//		p = p->next;
//	}
//	Del_All(&t);
//	return newStack;
//}