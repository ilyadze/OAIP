#include <iostream>
#include <conio.h>


using namespace std;

struct Spis
{
	int info;
	Spis* next, * prev;
};

Spis* createNewSpis(Spis*, Spis**);
Spis* InEnd(Spis*,int);
Spis* InBegin(Spis*, int);
int searchMax(Spis*);
int searchMin(Spis*);
void View(Spis*);
void ViewFromTheEnd(Spis*);
Spis* Delete_All(Spis*);
Spis* Delete(Spis*);
Spis* DistanceBetweenMinMax(Spis*, int, int);


int main()
{	
	srand(time(NULL));
	Spis* begin, *end;
	begin = end = NULL;
	begin = createNewSpis(begin, &end);
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
			end = InEnd(end, stackElement);
		}
	}
	else
	{
		for (int i = 0;i < stackSize;i++)
		{
			int stackElement;
			stackElement = rand() % 21 - 10;
			end = InEnd(end, stackElement);
		}
	}
	begin = Delete(begin);
	cout << "Stack: ";
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
	cout << "\nNew Stack:";
	View(begin);

}

Spis* createNewSpis(Spis* begin, Spis** end)
{
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
		cout << end->info << " " << endl;
		end = end->prev;
	}
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

int searchMax(Spis* begin)
{
	if (begin == NULL)
	{
		return NULL;
	}
	int maxElement = begin->info,indexOfMaxElement = 0, i = 0;
	while (begin != NULL)
	{
		if (begin->info > maxElement)
		{
			maxElement = begin->info;
			indexOfMaxElement = i;
		}
		begin = begin->next;
		i++;
	}
	return indexOfMaxElement;
}

int searchMin(Spis* begin)
{
	if (begin == NULL)
	{
		return NULL;
	}
	int minElement = begin->info, indexOfMinElement = 0, i = 0;
	while (begin != NULL)
	{
		if (begin->info < minElement)
		{
			minElement = begin->info;
			indexOfMinElement = i;
		}
		begin = begin->next;
		i++;
	}
	return indexOfMinElement;
}

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
