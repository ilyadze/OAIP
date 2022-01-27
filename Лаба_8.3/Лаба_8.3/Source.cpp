#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;

struct date
{
	int day;
	int month;
	int year;
};

struct list
{
	char Fio[21];
	date birthday;
	int numberOfGroup;
	int mark[4];
	double average_score;
};


const char nameOfFile[] = "nameOfFile.txt";
const int nameLength = 21;


bool fileCheck(char*);
bool openingCheck(char*);
list* fillingList(int);
list fillingList();
void fillingFile(char*, list*, int);
void addToFile(char*, list);
char** outNamesFiles();
list* outFile(char*);
list* resizeArray(int, int, list*);
char** resizeArray(int, int, char**);
int* resizeArray(int, int, int*);
void outList(list*, int);
void outList(list);
int numberOfStructures();
int numberOfStructures(char*);
int strLength(char*);
bool strCmp(char*, char*);
bool cmp(char*, char*);
int sizeOfFile(char*);
void conclusionName(char**);
void conclusionGroup(int*, int);
list* remevalFromTheList(char*, list*, int*, int);
void strCopy(char*, char*);
void addToFile(char*, list*, int);
double averageScoreAll(char*, list*, int);
int* groupNumber(list*, int, int&);
void input(char*);
void inputFIO(char*);
int inputNumber();
int inputNumber(int);
void sortList(char*, int);



int main()
{
	do
	{
		system("cls");
		cout << "Select actions " << endl
			<< "\n1.Create spisok "
			<< "\n2.List view "
			<< "\n3.Edit list "
			<< "\n4.Additional task "
			<< "\nExit" << endl;
		switch (_getch())
		{
		case '1':
		{
			system("cls");
			char fileName[nameLength];
			cout << "Enter name of file" << endl;
			input(fileName);
			if (fileCheck(fileName))
			{
				if (!openingCheck(fileName))
				{
					cout << "Error,file is not open" << endl;
					break;
				}
				system("cls");
				cout << "Enter the number of students" << endl;
				int size;
				size = inputNumber();
				fillingFile(fileName, fillingList(size), size);
			}
			else
			{
				system("cls");
				cout << "This file has already been created" << endl
					<< "Is the file is " << sizeOfFile(fileName) << " bytes" << endl
					<< "If you want to delete everything that was in this file and write again press 1" << endl
					<< "If not press any other button" << endl;
				if (_getch() == '1')
				{
					if (!openingCheck(fileName))
					{
						system("cls");
						cout << "Error,file is not open" << endl;
						_getch();
						break;
					}
					system("cls");
					int size;
					cout << "Enter the number of students" << endl;
					size = inputNumber();
					fillingFile(fileName, fillingList(size), size);
				}
				else
				{
					break;
				}
			}
			break;
		}
		case '2':
		{
			system("cls");
			cout << "What file do you want to view" << endl;
			char** fileNames = outNamesFiles();
			conclusionName(fileNames);
			cout << "Select the name of the file you want to watch" << endl;
			int nameNumber,size = numberOfStructures();
			nameNumber = inputNumber(size);
			nameNumber -= 1;
			if (!openingCheck(fileNames[nameNumber]))
			{
				system("cls");
				cout << "Error,file is not open" << endl;
				_getch();
				break;
			}
			system("cls");
			if (fileCheck(fileNames[nameNumber]))
			{
				cout << "File is empty" << endl;
				break;
			}
			outList(outFile(fileNames[nameNumber]), numberOfStructures(fileNames[nameNumber]));
			for (int i = 0; i < size;i++)
			{
				delete[] fileNames[i];
			}
			delete[] fileNames;
			_getch();
			break;
		}
		case '3':
		{
			system("cls");
			cout << "What file do you want to edit" << endl;
			char** fileNames = outNamesFiles();
			conclusionName(fileNames);
			cout << "Select the name of the file you want to edit" << endl;
			int nameNumber,nameNumbers = numberOfStructures();
			nameNumber = inputNumber(nameNumbers);
			nameNumber--;
			if (!openingCheck(fileNames[nameNumber]))
			{
				system("cls");
				cout << "Error,file is not open" << endl;
				_getch();
				break;
			}
			if (fileCheck(fileNames[nameNumber]))
			{
				cout << "File is empty" << endl;
				break;
			}
			cout << "\nYou want to see what is in the file" << endl
				<< "If yes then press 1" << endl
				<< "If not, then press any other button" << endl;
			if (_getch() == '1')
			{
				system("cls");
				outList(outFile(fileNames[nameNumber]), numberOfStructures(fileNames[nameNumber]));
				_getch();
			}
			system("cls");
			cout << "Select correction option:"
				<< "\n1.Delete"
				<< "\n2.Adding to the end"
				<< "\n3.The change"
				<< "\nCome back" << endl;
			switch (_getch())
			{
			case '1':
			{
				system("cls");
				cout << "Enter the number of students you want to remove" << endl;
				int size;
				size = inputNumber();
				cout << "Enter the numbers of the students you want to remove" << endl;
				int* numbers = new int[size];
				for (int i = 0;i < size;i++)
				{
					numbers[i] = inputNumber();
				}
				int sizeList = numberOfStructures(fileNames[nameNumber]);
				list* students = new list[sizeList];
				students = remevalFromTheList(fileNames[nameNumber], outFile(fileNames[nameNumber]), numbers, size);
				sizeList -= size;
				fillingFile(fileNames[nameNumber], students, sizeList);
				outList(students, sizeList);
				_getch();
				delete[] students;
				delete[] numbers;
				break;
			}

			case '2':
			{
				system("cls");
				cout << "Enter the number of students you want to add" << endl;
				int size;
				size = inputNumber();
				addToFile(fileNames[nameNumber], fillingList(size), size);
				break;
			}
			case '3':
			{
				system("cls");
				int sizeList = numberOfStructures(fileNames[nameNumber]);
				list* students = outFile(fileNames[nameNumber]);
				cout << "Enter the student you want to change" << endl;
				int studentNumber;
				studentNumber = inputNumber();
				studentNumber--;
				students[studentNumber] = fillingList();
				fillingFile(fileNames[nameNumber], students, sizeList);
				delete[] students;
				break;
			}
			default:
			{
				break;
			}
			}

			
			for (int i = 0; i < nameNumber;i++)
			{
				delete[] fileNames[i];
			}
			delete[] fileNames;
			break;
		}
		case '4':
		{
			system("cls");
			cout << "To which file do you want to apply additional tasks" << endl;
			char** fileNames = outNamesFiles();
			conclusionName(fileNames);
			cout << "Select the name of the file you want to edit" << endl;
			int nameNumber;
			nameNumber = inputNumber(numberOfStructures());
			nameNumber--;
			if (!openingCheck(fileNames[nameNumber]))
			{
				system("cls");
				cout << "Error,file is not open" << endl;
				break;
			}
			system("cls");
			char resultFileName[nameLength];
			cout << "Enter name of file" << endl;
			input(resultFileName);
			if (!fileCheck(resultFileName))
			{
				system("cls");
				cout << "This file has already been created" << endl
					<< "Is the file is " << sizeOfFile(resultFileName) << " bytes" << endl
					<< "If you do not want to delete everything that was in this file and write again press 1" << endl
					<< "If not press any other button" << endl;
				if (_getch() == '1')
				{
					break;
				}
			}
			system("cls");
			cout << "Enter number of group" << endl;
			list* students = outFile(fileNames[nameNumber]);
			int size = numberOfStructures(fileNames[nameNumber]), amount = 0;
			int* numberOfGroup = groupNumber(students, size, amount);
			conclusionGroup(numberOfGroup, amount);
			int number = inputNumber(amount);
			number--;
			double averageScore = averageScoreAll(fileNames[nameNumber], students, size);
			cout << "Average score - " << averageScore << endl;
			bool flag = false;
			for (int i = 0;i < size;i++)
			{
				if (students[i].average_score >= averageScore && students[i].numberOfGroup == numberOfGroup[number])
				{
					outList(students[i]);
					addToFile(resultFileName, students[i]);
					flag = true;
				}
			}
			if (!flag)
			{
				cout << "There are no students with a score above the average" << endl;
			}
			_getch();
			delete[]students;
			int nameNumbers = numberOfStructures();
			for (int i = 0;i < nameNumbers;i++)
			{
				delete[]fileNames[i];
			}
			delete[]fileNames;
			delete[]numberOfGroup;
			break;
		}
		/*case '5':
		{
			system("cls");
			cout << "To which file do you want to apply additional tasks" << endl;
			char** fileNames = outNamesFiles();
			conclusionName(fileNames);
			cout << "Select the name of the file you want to edit" << endl;
			int nameNumber;
			nameNumber = inputNumber(numberOfStructures());
			nameNumber--;
			if (!openingCheck(fileNames[nameNumber]))
			{
				system("cls");
				cout << "Error,file is not open" << endl;
				break;
			}
			system("cls");
			int size = numberOfStructures(fileNames[nameNumber]);
			sortList(fileNames[nameNumber], size);
			break;
		}*/
		default:
		{
			system("cls");
			cout << "Are you sure you want to exit,if so press 1" << endl;
			if (_getch() == '1')
			{
				return 0;
			}
		}
		}
	} while (1);
}





//void sortList(char* name, int size) 
//{
//	fstream file;
//	file.open(name, fstream:: in | fstream::out |fstream::app);
//	list student,studentCmp;
//	char str[1024];
//	for (int i = 0;i < size - 1;i++)
//	{
//		file >> student.Fio
//		>> student.numberOfGroup
//		>> student.birthday.day >> student.birthday.month >> student.birthday.year
//		>> student.mark[0] >> student.mark[1] >> student.mark[2] >> student.mark[3]
//		>> student.average_score;
//		for (int j = 0;j < size;j++)
//		{
//			file >> studentCmp.Fio
//				>> studentCmp.numberOfGroup
//				>> studentCmp.birthday.day >> studentCmp.birthday.month >> studentCmp.birthday.year
//				>> studentCmp.mark[0] >> studentCmp.mark[1] >> studentCmp.mark[2] >> studentCmp.mark[3]
//				>> studentCmp.average_score;
//			if (cmp(student.Fio,studentCmp.Fio))
//			{
//				file.seekg(0);
//				for (int k = 0;k < i;k++)
//				{
//					file.getline(str, 1024, '\n');
//				}
//				
//				file << studentCmp.Fio << ' '
//					<< studentCmp.numberOfGroup << ' '
//					<< studentCmp.birthday.day << ' ' << studentCmp.birthday.month << ' ' << studentCmp.birthday.year << ' '
//					<< studentCmp.mark[0] << ' ' << studentCmp.mark[1] << ' ' << studentCmp.mark[2] << ' ' << studentCmp.mark[3] << ' '
//					<< (studentCmp.mark[0] + studentCmp.mark[1] + studentCmp.mark[2] + studentCmp.mark[3]) / 4. << endl;
//				file.seekg(0);
//				for (int k = 0;k < j - 1;k++)
//				{
//					file.getline(str, 1024, '\n');
//				}
//
//				file << student.Fio << ' '
//					<< student.numberOfGroup << ' '
//					<< student.birthday.day << ' ' << student.birthday.month << ' ' << student.birthday.year << ' '
//					<< student.mark[0] << ' ' << student.mark[1] << ' ' << student.mark[2] << ' ' << student.mark[3] << ' '
//					<< (student.mark[0] + student.mark[1] + student.mark[2] + student.mark[3]) / 4. << endl;
//				
//			}
//			
//		}
//		file.seekg(0, 0);
//		for (int k = 0;k < i + 1;k++)
//		{
//			file.getline(str,30,'\n');
//		}
//		
//	}
//	file.close();
//}

//void sortList(char* name, int size)
//{
//	ifstream file;
//	ofstream fileResult;
//	fileResult.open("resultCmp.txt");
//	file.open(name);
//	list student, studentCmp;
//	char str[1024];
//	for (int i = 0;i < size - 1;i++)
//	{
//		file >> student.Fio
//			>> student.numberOfGroup
//			>> student.birthday.day >> student.birthday.month >> student.birthday.year
//			>> student.mark[0] >> student.mark[1] >> student.mark[2] >> student.mark[3]
//			>> student.average_score;
//		for (int j = 0;j < size;j++)
//		{
//			file >> studentCmp.Fio
//				>> studentCmp.numberOfGroup
//				>> studentCmp.birthday.day >> studentCmp.birthday.month >> studentCmp.birthday.year
//				>> studentCmp.mark[0] >> studentCmp.mark[1] >> studentCmp.mark[2] >> studentCmp.mark[3]
//				>> studentCmp.average_score;
//			if (cmp(student.Fio, studentCmp.Fio))
//			{
//				fileResult << studentCmp.Fio << ' '
//					<< studentCmp.numberOfGroup << ' '
//					<< studentCmp.birthday.day << ' ' << studentCmp.birthday.month << ' ' << studentCmp.birthday.year << ' '
//					<< studentCmp.mark[0] << ' ' << studentCmp.mark[1] << ' ' << studentCmp.mark[2] << ' ' << studentCmp.mark[3] << ' '
//					<< (studentCmp.mark[0] + studentCmp.mark[1] + studentCmp.mark[2] + studentCmp.mark[3]) / 4. << endl;
//			}
//
//		}
//
//	}
//	file.close();
//	fileResult.close();
//}

bool fileCheck(char* fileName)
{
	ifstream namesOfFile;
	namesOfFile.open(nameOfFile);
	char* generetedFile;
	generetedFile = new char[20];
	while (!namesOfFile.eof())
	{
		namesOfFile.getline(generetedFile, 20);
		if (strCmp(generetedFile, fileName))
		{
			if (sizeOfFile(fileName) > 0)
			{

				return 0;
			}
			else
			{
				if (sizeOfFile(fileName) == 0)
				{
					return 1;
				}
				else 
				{
					ofstream fileNames;
					fileNames.open(nameOfFile, fstream::app);
					fileNames << fileName << endl;
					fileNames.close();
					return 1;
				}
			}
		}
	}
	namesOfFile.close();
	ofstream fileNames;
	fileNames.open(nameOfFile, fstream::app);
	fileNames << fileName << endl;
	fileNames.close();
	delete[] generetedFile;
	return 1;
}


bool openingCheck(char* fileName)
{
	ifstream fileSpisok;
	fileSpisok.open(fileName, fstream::app);
	if (!fileSpisok.is_open())
	{
		fileSpisok.close();
		return 0;
	}
	fileSpisok.close();
	return 1;
}


list* fillingList(int size)
{
	list* students;
	students = new list[size];
	int i = 0;
	while (i < size)
	{
		cout << "\nEnter Fio" << endl;

		inputFIO(students[i].Fio);
		cout << "\nEnter number of group" << endl;
		students[i].numberOfGroup = inputNumber();

		cout << "\nEnter birthday date(day.month.year) " << endl;
		scanf_s("%d.%d.%d", &students[i].birthday.day, &students[i].birthday.month, &students[i].birthday.year);

		cout << "Enter four marks(mark fith,mark math,mark inform,mark chim)" << endl;
		scanf_s("%d,%d,%d,%d", &students[i].mark[0], &students[i].mark[1], &students[i].mark[2], &students[i].mark[3]);
		i++;
	}
	return students;
}
list fillingList()
{
	list student;

	cout << "Enter Fio" << endl;
	inputFIO(student.Fio);

	cout << "\nEnter number of group" << endl;
	student.numberOfGroup = inputNumber();

	cout << "\nEnter birthday date(day.month.year) " << endl;
	scanf_s("%d.%d.%d", &student.birthday.day, &student.birthday.month, &student.birthday.year);

	cout << "Enter four marks(mark fith, mark math, mark inform, mark chim)" << endl;
	scanf_s("%d,%d,%d,%d", &student.mark[0], &student.mark[1], &student.mark[2], &student.mark[3]);

	return student;
}



void fillingFile(char* fileName, list* students, int size)
{
	ofstream file;
	file.open(fileName);
	for (int i = 0;i < size;i++)
	{
		file << students[i].Fio << ' '
			<< students[i].numberOfGroup << ' '
			<< students[i].birthday.day << ' ' << students[i].birthday.month << ' ' << students[i].birthday.year << ' '
			<< students[i].mark[0] << ' ' << students[i].mark[1] << ' ' << students[i].mark[2] << ' ' << students[i].mark[3] << ' '
			<< (students[i].mark[0] + students[i].mark[1] + students[i].mark[2] + students[i].mark[3]) / 4. << endl;
	}
	file.close();
}


void addToFile(char* fileName, list* students, int size)
{
	ofstream file;
	file.open(fileName, fstream::app);
	for (int i = 0;i < size;i++)
	{
		file << students[i].Fio << ' '
			<< students[i].numberOfGroup << ' '
			<< students[i].birthday.day << ' ' << students[i].birthday.month << ' ' << students[i].birthday.year << ' '
			<< students[i].mark[0] << ' ' << students[i].mark[1] << ' ' << students[i].mark[2] << ' ' << students[i].mark[3] << ' '
			<< (students[i].mark[0] + students[i].mark[1] + students[i].mark[2] + students[i].mark[3]) / 4. << endl;
	}
	file.close();
}
void addToFile(char* fileName, list students)
{
	ofstream file;
	file.open(fileName, fstream::app);
	file << students.Fio << ' '
		<< students.numberOfGroup << ' '
		<< students.birthday.day << ' ' << students.birthday.month << ' ' << students.birthday.year << ' '
		<< students.mark[0] << ' ' << students.mark[1] << ' ' << students.mark[2] << ' ' << students.mark[3] << ' '
		<< (students.mark[0] + students.mark[1] + students.mark[2] + students.mark[3]) / 4. << endl;

	file.close();
}

char** outNamesFiles()
{
	ifstream file;
	file.open(nameOfFile);
	if (!file.is_open())
	{
		cout << "Error" << endl;
		return 0;
	}
	int size = 10;
	char** name = new char* [size];
	for (int i = 0;i < size;i++)
	{
		name[i] = new char[nameLength];
	}
	int i;
	for (i = 0;!file.eof();i++)
	{
		if (i == size)
		{
			name = resizeArray(size, size + 1, name);
		}
		file.getline(name[i], nameLength);
	}
	name = resizeArray(size, i - 1, name);
	file.close();
	return name;
}


void conclusionName(char** name)
{
	int size = numberOfStructures();
	for (int i = 0; i < size;i++)
	{
		cout << i + 1 << ". " << name[i] << endl;
	}
}


void conclusionGroup(int* groups, int size)
{
	for (int i = 0; i < size;i++)
	{
		cout << i + 1 << ". " << groups[i] << endl;
	}
}


list* outFile(char* fileName)
{
	ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		cout << "Error,file is not open" << endl;
		return 0;
	}
	list* students;
	int size = numberOfStructures(fileName);
	students = new list[size];
	int i;
	for (i = 0;i < size;i++)
	{
		file >> students[i].Fio
			>> students[i].numberOfGroup
			>> students[i].birthday.day >> students[i].birthday.month >> students[i].birthday.year
			>> students[i].mark[0] >> students[i].mark[1] >> students[i].mark[2] >> students[i].mark[3]
			>> students[i].average_score;
	}
	file.close();
	return students;
}


list* resizeArray(int oldSize, int newSize, list* exams)
{
	if (oldSize == newSize)
	{
		return exams;
	}
	list* newArray = new list[newSize];
	oldSize = newSize < oldSize ? newSize : oldSize;
	for (int i = 0;i < oldSize;i++)
	{
		newArray[i] = exams[i];
	}
	delete[] exams;
	return newArray;
}
char** resizeArray(int oldSize, int newSize, char** oldArray)
{
	if (oldSize == newSize)
	{
		return oldArray;
	}
	char** newArray = new char* [newSize];
	for (int i = 0;i < newSize;i++)
	{
		newArray[i] = new char[nameLength];
	}
	oldSize = newSize < oldSize ? newSize : oldSize;
	for (int i = 0;i < oldSize;i++)
	{
		strCopy(newArray[i], oldArray[i]);
	}
	oldSize = newSize;
	for (int i = 0;i < oldSize;i++)
	{
		delete[] oldArray[i];
	}
	delete[] oldArray;
	return newArray;
}
int* resizeArray(int oldSize, int newSize, int* exams)
{
	if (oldSize == newSize)
	{
		return exams;
	}
	int* newArray = new int[newSize];
	oldSize = newSize < oldSize ? newSize : oldSize;
	for (int i = 0;i < oldSize;i++)
	{
		newArray[i] = exams[i];
	}
	delete[] exams;
	return newArray;
}


void outList(list* students, int size)
{
	for (int i = 0;i < size;i++)
	{
		cout << i + 1 << "\nFio - " << students[i].Fio
			<< "\nNumber of group - " << students[i].numberOfGroup
			<< "\nBirthday date - " << students[i].birthday.day << "." << students[i].birthday.month << "." << students[i].birthday.year
			<< "\nMark:\nFith - " << students[i].mark[0]
			<< "\nMath - " << students[i].mark[1]
			<< "\nInform - " << students[i].mark[2]
			<< "\nChim - " << students[i].mark[3]
			<< "\nAverage score - " << students[i].average_score << endl;
	}
}
void outList(list students)
{
	cout << "\nFio - " << students.Fio
		<< "\nNumber of group - " << students.numberOfGroup
		<< "\nBirthday date - " << students.birthday.day << "." << students.birthday.month << "." << students.birthday.year
		<< "\nMark:\nFith - " << students.mark[0]
		<< "\nMath - " << students.mark[1]
		<< "\nInform - " << students.mark[2]
		<< "\nChim - " << students.mark[3]
		<< "\nAverage score - " << students.average_score << endl;

}


int numberOfStructures()
{
	ifstream file;
	file.open(nameOfFile);
	char sizeName[nameLength];
	int size = 0;
	while (!file.eof())
	{
		file.getline(sizeName, nameLength);
		size++;
	}
	size--;
	return size;
}
int numberOfStructures(char* fileName)
{
	ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		return 0;
	}
	char sizeName[1024];
	int size = 0;
	while (!file.eof())
	{
		file.getline(sizeName, 1024, '\n');
		size++;
	}
	size--;
	return size;
}


int strLength(char* a)
{
	int size;
	for (size = 0;a[size] != '\0';size++) {}
	return size;
}


bool strCmp(char* a, char* b)
{
	int j = 0;
	for (int i = 0; a[i] != '\0' && b[i] != '\0';i++)
	{
		if (a[i] == b[i])
		{
			j++;
		}
	}
	if (j == strLength(a))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool cmp(char* str1, char* str2)
{
	for (int i = 0;str1[i] != '\0' && str2[i] != '\0';i++)
	{
		if (str1[i] > str2[i])
		{
			return true;
		}
		else
		{
			if (str1[i] == str2[i])
			{
				i++;
				continue;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}


int sizeOfFile(char* nameOfFile)
{
	int sizeOfFile;
	ifstream file;
	file.open(nameOfFile);
	file.seekg(0, ios::end);
	sizeOfFile = file.tellg();
	file.close();
	return sizeOfFile;
}


list* remevalFromTheList(char* nameOfFile, list* students, int* numbers, int size)
{
	int sizeList = numberOfStructures(nameOfFile);
	for (int i = 0;i < size;i++)
	{
		for (int j = numbers[i] - 1;j < sizeList - 1;j++)
		{
			if (numbers[i - 1] < numbers[i] && i >= 1)
			{
				numbers[i]--;
			}
			strCopy(students[j].Fio, students[j + 1].Fio);
			students[j].numberOfGroup = students[j + 1].numberOfGroup;
			students[j].birthday.day = students[j + 1].birthday.day;
			students[j].birthday.month = students[j + 1].birthday.month;
			students[j].birthday.year = students[j + 1].birthday.year;
			students[j].mark[0] = students[j + 1].mark[0];
			students[j].mark[1] = students[j + 1].mark[1];
			students[j].mark[2] = students[j + 1].mark[2];
			students[j].mark[3] = students[j + 1].mark[3];
			students[j].average_score = students[j + 1].average_score;

		}
	}
	students = resizeArray(sizeList, sizeList - size, students);
	return students;
}


void strCopy(char* newStr, char* oldStr)
{
	for (int i = 0;i < nameLength;i++)
	{
		newStr[i] = oldStr[i];
	}
}


double averageScoreAll(char* nameFile, list* students, int size)
{
	double averageScore = 0;
	for (int i = 0;i < size;i++)
	{
		averageScore += students[i].average_score;
	}
	averageScore /= size;
	return averageScore;
}


int* groupNumber(list* students, int size, int& amount)
{
	int* groups = new int[size];
	groups[0] = students[0].numberOfGroup;
	amount = 1;
	for (int i = 1;i < size;i++)
	{
		int number = 0;
		for (int j = 0;j < amount;j++)
		{
			if (groups[j] == students[i].numberOfGroup)
			{
				number++;
			}
		}
		if (number == 0)
		{
			groups[amount] = students[i].numberOfGroup;
			amount++;
		}
	}
	groups = resizeArray(size, amount, groups);
	return groups;
}


void input(char* str)
{
	int i = 0;
	while (1)
	{
		str[i] = _getch();
		if (str[i] == 13 && i > 1)
		{
			break;
		}
		if (str[i] > 'z' || str[i] < 'A')
		{
			continue;
		}
		if (str[i] > 'Z' && str[i] < 'a')
		{
			continue;
		}
		cout << str[i];
		i++;
	}
	str[i] = '.';
	str[i + 1] = 't';
	str[i + 2] = 'x';
	str[i + 3] = 't';
	i+=4;
	
	str[i] = '\0';
}

void inputFIO(char* str)
{
	int i = 0;
	while (1)
	{
		str[i] = _getch();
		if (str[i] == 13 && i > 1)
		{
			break;
		}
		if (str[i] > 'z' || str[i] < 'A' && str[i] != '.')
		{
			continue;
		}
		if (str[i] > 'Z' && str[i] < 'a' && str[i] != '.')
		{
			continue;
		}
		cout << str[i];
		i++;
	}
	str[i] = '\0';
}


int inputNumber(int n)
{
	char str[20];
	int i = 0,number = 0;
	while (1)
	{
		str[i] = _getch();
		if (str[i] == 13 && i != 0)
		{
			break;
		}
		if (str[i] < '0' || str[i] > '9')
		{
			continue;
		}
		if (int(str[i]) - 48 > n)
		{
			continue;
		}
		cout << str[i];
		i++;
	}
	str[i] = '\0';
	i = 0;
	while (str[i] != '\0')
	{
		number *= 10;
		number += int(str[i]) - 48;
		i++;
	}
	return number;
}

int inputNumber()
{
	char str[20];
	int i = 0, number = 0;
	while (1)
	{
		str[i] = _getch();
		if (str[i] == 13 && i != 0)
		{
			break;
		}
		if (str[i] < '0' || str[i] > '9')
		{
			continue;
		}
		cout << str[i];
		i++;
	}
	str[i] = '\0';
	i = 0;
	while (str[i] != '\0')
	{
		number *= 10;
		number += int(str[i]) - 48;
		i++;
	}
	return number;
}

