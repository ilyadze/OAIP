#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

struct chemicalElement
{
	int serialNumber;
	char elementName[21];
	int atomicWeight;
};

void elementsIn(chemicalElement*, int);
void elementsOut(chemicalElement*, int);
void elementsOut(chemicalElement);
void searchElements(chemicalElement*, int, char,int*);


int main()
{
	cout << "Enter amount of elements" << endl;
	int size;
	cin >> size;
	chemicalElement* elements = new chemicalElement[size];
	elementsIn(elements, size);
	cout << "Enter the letter of elements" << endl;
	char letter = _getch();
	cout << "Letter is " << letter << endl;
	int amountOfSearchElements;
	chemicalElement newElements;
	searchElements(elements, size, letter,&amountOfSearchElements);
	cout << "Amount of search elements is " << amountOfSearchElements << endl;
	delete[] elements;
}


void elementsIn(chemicalElement* elements, int size)
{
	for (int i = 0;i < size;i++)
	{
		cin.ignore();
		cin.clear();
		cout << "Element name - ";
		gets_s((elements + i)->elementName);
		cout << "Serial number - ";
		cin >> (elements + i)->serialNumber;
		cout << "Atomic weight - ";
		cin >> (elements + i)->atomicWeight;

	}
}

void elementsOut(chemicalElement* elements, int size)
{
	for (int i = 0;i < size;i++)
	{
		cout << "Name - " << (elements + i)->elementName << endl;
		cout << "Number - " << (elements + i)->serialNumber << endl;
		cout << "Weight - " << (elements + i)->atomicWeight << endl;
	}
}

void elementsOut(chemicalElement element)
{
	cout << "Name - " << (&element)->elementName << endl;
	cout << "Number - " << (&element)->serialNumber << endl;
	cout << "Weight - " << (&element)->atomicWeight << endl;
}

void searchElements(chemicalElement* elements, int size, char letter, int* amountOfSearchElements)
{
	*amountOfSearchElements = 0;
	for (int i = 0;i < size;i++)
	{
		if ((elements + i)->elementName[0] == letter)
		{
			elementsOut(*(elements + i));
			(*amountOfSearchElements)++;
		}
	}
}



