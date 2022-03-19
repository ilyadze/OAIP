#include <iostream>
#include <conio.h>

using namespace std;

struct Tree
{
	int info;
	Tree* Left, *Right;
};

Tree* Make(Tree*);
Tree* List(int);
void DeleteAll(Tree*);
Tree* Delete(Tree*, int);
void View(Tree*,int);
Tree* addElement(Tree*, int);



int main()
{
	do {
		system("cls");
		bool IsExit = false;
		Tree* root;
		cout << "Enter root:" << endl;
		int infoOfRoot;
		cin >> infoOfRoot;
		root = List(infoOfRoot);
		root = Make(root);
		View(root,0);
		_getch();
		do {
			system("cls");
			cout << "Enter the tree option" << endl
				<< "1.View" << endl
				<< "2.Add element" << endl
				<< "3.Delete element" << endl
				<< "4.Back to create new tree" << endl
				<< "Exit the progamm";
			switch (_getch()) {
			case '1': {
				system("cls");
				View(root,0);
				_getch();
				break;
			}
			case '2': {
				system("cls");
				cout << "Enter info" << endl;
				int info;
				cin >> info;
				root = addElement(root, info);
				break;
			}
			case '3': {
				system("cls");
				cout << "\nInput key: ";
				int key;
				cin >> key;
				root = Delete(root, key);
				View(root,0);
				_getch();
				break;
			}
			case '4': {
				IsExit = true;
				break;
			}
			default: {
				return NULL;
			}
			}
			

		} while (!IsExit);
		DeleteAll(root);
	} while (true);
}


Tree* Make(Tree* Root)
{
	Tree* Prev, * t;
	int b;
	bool find;
	if (Root == NULL)
	{
		cout << "Input root: ";
		cin >> b;
		Root = List(b);
	}
	while (true)
	{
		cout << "Input Info(if you want to finish filling, enter the nagative number): ";
		cin >> b;
		if (b < 0)
		{
			break;
		}
		t = Root;
		find = false;
		Prev = t;
		while (t && !find)
		{
			Prev = t;
			if (b == t->info)
			{
				find = true;
			}
			else
			{
				if (b < t->info)
				{
					t = t->Left;
				}
				else
				{
					t = t->Right;
				}
			}
		}
		if (!find)
		{
			t = List(b);
			if (b < Prev->info)
			{
				Prev->Left = t;
			}
			else
			{
				Prev->Right = t;
			}
		}
	}
	return Root;
}

Tree* addElement(Tree* Root, int info) {
	Tree* t = Root;
	bool find = false;
	Tree* Prev = t;
	while (t && !find)
	{
		Prev = t;
		if (info == t->info)
		{
			find = true;
		}
		else
		{
			if (info < t->info)
			{
				t = t->Left;
			}
			else
			{
				t = t->Right;
			}
		}
	}
	if (!find)
	{
		t = List(info);
		if (info < Prev->info)
		{
			Prev->Left = t;
		}
		else
		{
			Prev->Right = t;
		}
	}
	return Root;
}


Tree* List(int i)
{
	Tree* t = new Tree;
	t->info = i;
	t->Left = t->Right = NULL;
	return t;
}


Tree* Delete(Tree* Root, int key)
{
	Tree* Del, * Prev_Del, * R, * Prev_R;
	Del = Root;
	Prev_Del = NULL;
	while (Del != NULL && Del->info != key)
	{
		Prev_Del = Del;
		if (Del->info > key)
		{
			Del = Del->Left;
		}
		else
		{
			Del = Del->Right;
		}
	}
	if (Del == NULL)
	{
		cout << "Error,no key" << endl;
		return Root;
	}
	if (Del->Right == NULL)
	{
		R = Del->Left;
	}
	else
	{
		if (Del->Left == NULL)
		{
			R = Del->Right;
		}
		else
		{
			Prev_R = Del;
			R = Del->Left;
			while (R->Right != NULL)
			{
				Prev_R = R;
				R = R->Right;
			}
			if (Prev_R == Del)
			{
				R->Right = Del->Right;
			}
			else
			{
				R->Right = Del->Right;
				Prev_R->Right = R->Left;
				R->Left = Del->Left;
			}
		}
	}
	if (Del == Root)
	{
		Root = R;
	}
	else
	{
		if (Del->info < Prev_Del->info)
		{
			Prev_Del->Left = R;
		}
		else
		{
			Prev_Del->Right = R;
		}
	}
	cout << "\nDelete element - " << Del->info << endl;
	delete Del;
	return Root;
}

void View(Tree* t,int level)
{	
	if (t)
	{
		
		View(t->Right,level+1);
		for (int i = 0;i < level;i++) {
			cout << "   ";
		}
		cout << t->info << endl;
		View(t->Left, level+1);
	}
}

void DeleteAll(Tree* t)
{
	if (t != NULL)
	{
		DeleteAll(t->Left);
		DeleteAll(t->Right);
		delete t;
	}
}