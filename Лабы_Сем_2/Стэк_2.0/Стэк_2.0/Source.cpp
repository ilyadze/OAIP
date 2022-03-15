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
void Delete_All(Stack**);
void Sort_info(Stack*);
int searchMax(Stack*);
int searchMin(Stack*);
Stack* DistanceBetweenMinMax(Stack*,int, int);
int sizeOfStack(Stack*);
Stack* copyInformationToNewStack(Stack*);
Stack* deleteNegativeNumber(Stack*);


int main()
{
	srand(time(NULL));
	Stack* begin = NULL;
	do
	{	
		system("cls");
		
		cout << "Enter stack size" << endl;
		int stackSize;
		cin >> stackSize;
		bool isExitInProgram = false;
		system("cls");
		cout << "Select stack fill option" << endl
			<< "1.By hand" << endl
			<< "2.Computer" << endl
			<< "Exit the programm" << endl;
		switch (_getch())
		{
		case '1':
		{
			cout << "Fill stack" << endl;
			for (int i = 0; i < stackSize;i++)
			{
				int stackElement;
				cin >> stackElement;
				begin = InStack(begin, stackElement);
			}
			break;
		}
		case '2':
		{
			for (int i = 0;i < stackSize;i++)
			{
				int stackElement;
				stackElement = rand() % 21 - 10;
				begin = InStack(begin, stackElement);
			}
			break;
		}
		default:
		{
			isExitInProgram = true;
			break;
		}
		}
		if (isExitInProgram)
		{
			break;
		}
		system("cls");
		View(begin);
		_getch();
		do
		{
			system("cls");
			bool isExit = false;
			Stack* newBegin = copyInformationToNewStack(begin);
			cout << "Select the option to work with stack:" << endl
				<< "1.Sort information" << endl
				<< "2.Add element to stack" << endl
				<< "3. Delete element with min max elements" << endl
				<< "4.Delete negative number" << endl
				<< "Back to create stack" << endl;
			switch (_getch())
			{
			case '1':
			{
				system("cls");
				Sort_info(newBegin);
				cout << "Old ";
				View(begin);
				cout << "\nNew ";
				View(newBegin);
				_getch();
				break;
			}
			case '2':
			{
				system("cls");
				cout << "Enter the number of elements" << endl;
				int number;
				cin >> number;
				for (int i = 0;i < number;i++)
				{
					cout << "Enter info" << endl;
					int info;
					cin >> info;
					begin = InStack(begin, info);
				}
				cout << "New ";
				View(begin);
			}
			case '3':
			{
				int maxElement, minElement;
				maxElement = searchMax(newBegin);
				minElement = searchMin(newBegin);
				if (maxElement == minElement)
				{
					system("cls");
					cout << "Error, all elements are equals" << endl;
					return 0;
				}
				if (abs(minElement - maxElement) == 1)
				{
					system("cls");
					cout << "Min and Max elements are next to each other" << endl;
					return 0;
				}
				newBegin = DistanceBetweenMinMax(newBegin, minElement, maxElement);
				system("cls");
				cout << "Old ";
				View(begin);
				cout << "New ";
				ViewR(newBegin);
				cout << "\nSize of new Stack - " << sizeOfStack(newBegin) << endl;
				_getch();
				break;
			}
			case '4':
			{
				system("cls");
				newBegin = deleteNegativeNumber(newBegin);
				cout << "Old";
				View(begin);
				cout << "New ";
				View(newBegin);
				_getch();
				break;
			}
			default:
			{
				isExit = true;
			}
			}
			if (isExit)
			{
				Delete_All(&newBegin);
				break;
			}
			cout << "If you want to work with the new stack press 1" << endl;
			if (_getch() == '1')
			{
				Delete_All(&begin);
				begin = copyInformationToNewStack(newBegin);
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
	Stack* t = p;
	cout << "Stack: ";
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

void Delete_All(Stack** p) {
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
			if (t1->info > t1->next->info) 
			{
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
	int indexOfMaxElement = 0,maxElement = p->info,i = 0;
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
	int indexOfMinElement = 0, minElement = p->info, i = 0;
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
	Delete_All(&t);
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

Stack* copyInformationToNewStack(Stack* begin)
{
	Stack* newStack = NULL;
	while (begin != NULL)
	{
		newStack = InStack(newStack, begin->info);
		begin = begin->next;
	}
	return newStack;
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
