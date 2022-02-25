#include <iostream>

using namespace std;

void arrayInput(int*,int);
void arrayOut(int*, int);
void sumOfArrayElements(int*, int, int&, int*);

int main()
{
	cout << "Enter size of array" << endl;
	int size;
	cin >> size;
	int* array = new int[size];
	arrayInput(array, size);
	arrayOut(array, size);
	int lastNegativeNumber = 0;
	int sum = 0;
	sumOfArrayElements(array, size, sum, &lastNegativeNumber);
	if (lastNegativeNumber == -1 || lastNegativeNumber == size - 1)
	{
		cout << "Negative number the last,or missing" << endl;
		return 0;
	}
	cout << "Sum = " << sum << "\nNumber = " << size - lastNegativeNumber - 1 << endl;
}

void arrayInput(int* array,int size)
{
	for (int i = 0;i < size;i++)
	{
		cout << "a[" << i << "] = ";
		cin >> *(array + i);
	}
}

void arrayOut(int* array, int size)
{
	for (int i = 0;i < size; i++)
	{
		cout << *(array + i) << ' ';
	}
	cout << endl;
}

void sumOfArrayElements(int* array, int lastElement, int& sum, int *lastNegativeNumber)
{
	*lastNegativeNumber = -1;
	for (int i = 0;i < lastElement;i++)
	{
		if (*(array + i) < 0)
		{
			*lastNegativeNumber = i;
		}
	}
	for (int i = *lastNegativeNumber + 1;i < lastElement;i++)
	{
		sum += *(array + i);
	}
}