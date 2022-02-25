#include <iostream>
#include <conio.h>

using namespace std;

struct Stack {
	int info;
	Stack* next; 
};


void View(Stack*);
Stack* InStack(Stack*, int);
Stack* OutStack(Stack*, int*);
Stack* deleteNegativeNumber(Stack* );
void Del_All(Stack**);
void Sort_info(Stack*);

int main()
{
	Stack* begin = NULL;
	cout << "Enter stack size" << endl;
	int stackSize;
	cin >> stackSize;
	cout << "Fill stack" << endl;
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
	begin = deleteNegativeNumber(begin);
	cout << "\nNew ";
	View(begin);
	Del_All(&begin);
}


Stack* InStack(Stack* p, int in) {
	Stack* t = new Stack; 
	t->info = in; 
	t->next = p; 
	return t;
}

Stack* deleteNegativeNumber(Stack* p)
{
	Stack* newStack = NULL,*z = p;
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
	Del_All(&z);
	return newStack;
}

void View(Stack* p) {
	Stack* t = p;
	cout << "Stack: ";
	while (t != NULL) {
		cout << t -> info << " "; 
		t = t->next;
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




