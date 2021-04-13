#include "school.h"
#include <iostream>
#include <limits>

void PressEnterToContinue()
{
	system("read -p \"Press a key to continue...\" -n 1 -s\n");

}

void clearScreen()
{
	for(int i = 1; i <= 10; i++)
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void displayCommandMenu()
{
	int option = 100;
	SchoolYearList schoolYearList;
	classList classList;
	loadSchoolYearList(schoolYearList);
	loadClassList(classList);
	while (option != 0)
	{
		cout << "---------------------------------------" << endl;
		cout << "1. Create a school year." << endl;
		cout << "2. Create new class." << endl;
		cout << "3. import students from csv file to a class" << endl;
		cin >> option;

		if (option == 1)
		{
			clearScreen();
			string path = "SchoolYear/SchoolYear.txt";
			cout << "Create a new school year:" << endl;
			createSchoolYear(schoolYearList, path);
			displaySchoolYears(schoolYearList);
			PressEnterToContinue();
			clearScreen();
		}
		else if (option == 2)
		{
			clearScreen();
			string path = "Classes/Classes.txt";
			cout << "Create a new class:" << endl;
			createClasses(classList, path);
			displayClasses(classList);
			PressEnterToContinue();
		}
		else if (option == 3)
		{
			addStudentsToClass(classList);
			PressEnterToContinue();
		}

		clearScreen();
	}

	deleteClassList(classList);
	deleteSchoolYearList(schoolYearList);
}

void addStudentsToClass(classList &classList)
{
	char input[1000];
	cout << "Input the class name that you want to add student to: ";
	cin.width(1000);
	cin >> input;
	Class *addClass = findClass(classList, input);
	if (addClass == nullptr)
	{
		cout << "Class does not exist...." << endl;
	}
	else
	{
		int noStudent;
		if (addClass->studentList == nullptr)
		{
			noStudent = loadStudent(addClass);
			addClass->noStudent = noStudent;
		}
		else
		{
			deleteStudentList(addClass);
			noStudent = loadStudent(addClass);
			addClass->noStudent = noStudent;
		}
		if (noStudent == 0 || addClass->studentList == nullptr)
			cout << "File not exists or empty, add student to " << addClass->className << ".csv file..." << endl;
		else
			cout << "Students Added to class " << addClass->className << endl;
	}
}

void loadClassList(classList &classList)
{
	ifstream fin;
	string path = "Classes/Classes.txt";
	fin.open(path);

	if (fin.is_open())
	{
		char dummy[10000];
		while (!fin.eof())
		{
			fin >> dummy;
			if (strlen(dummy) == 0)
				return;
			Class *newClass = new Class;
			newClass->className = new char[strlen(dummy) + 1];
			strcpy(newClass->className, dummy);
			int noStudent = loadStudent(newClass);
			newClass->noStudent = noStudent;
			newClass->pNext = classList.classL;
			if (classList.classL != nullptr)
				classList.classL->pPrev = newClass;
			classList.classL = newClass;
		}
	}
	else
	{
		cout << "Cannot open Classes.txt" << endl;
		return;
	}
	fin.close();
}
int loadStudent(Class *&cl)
{
	ifstream fin;
	string path = "Classes/";
	path.append(cl->className);
	path += ".csv";
	int count = 1;
	fin.open(path);
	if (fin.is_open())
	{
		string dummy;
		Student *pCur = cl->studentList;
		while (getline(fin, dummy, ','))
		{
			Student *newStudent = new Student;
			newStudent->No = count;
			// first name
			newStudent->firstName = dummy;
			//last name
			getline(fin, newStudent->lastName, ',');
			//Student ID
			getline(fin, newStudent->studentID, ',');
			//Date of Birth
			getline(fin, dummy, ',');
			dateCSVToInt(dummy, newStudent->birth);
			//Social ID
			getline(fin, newStudent->socialID, ',');
			//Gender
			getline(fin, newStudent->Gender);

			if (cl->studentList == nullptr)
			{
				cl->studentList = newStudent;
				newStudent->pPrev = nullptr;
				pCur = cl->studentList;
			}
			else
			{
				newStudent->pPrev = pCur;
				pCur->pNext = newStudent;
				pCur = newStudent;
			}
			pCur->pNext = nullptr;
			count++;
		}
	}
	return count - 1;
}

void dateCSVToInt(string s, Date &d)
{
	int count = 0;
	string day, month, year;
	for (int i = 0; i < int(s.length()) + 1; i++)
	{
		if (s[i] == '/')
			count++;
		else if (count == 0)
			day += s[i];
		else if (count == 1)
			month += s[i];
		else
			year += s[i];
	}
	d.month = stoi(month);
	d.year = stoi(year);
	d.day = stoi(day);
}

void loadSchoolYearList(SchoolYearList &schoolYearList)
{
	ifstream fin;
	string path = "SchoolYear/SchoolYear.txt";
	fin.open(path);

	if (fin.is_open())
	{

		char dummy[10000];
		while (!fin.eof())
		{
			fin >> dummy;
			if (strlen(dummy) == 0)
				return;
			SchoolYear *newSchoolYear = new SchoolYear;
			newSchoolYear->year = new char[strlen(dummy) + 1];
			strcpy(newSchoolYear->year, dummy);

			newSchoolYear->pNext = schoolYearList.schoolyearL;
			if (schoolYearList.schoolyearL != nullptr)
				schoolYearList.schoolyearL->pPrev = newSchoolYear;
			schoolYearList.schoolyearL = newSchoolYear;
		}
	}
	else
	{
		cout << "Cannot open SchoolYear.txt" << endl;
		return;
	}
	fin.close();
}

void createClasses(classList &classList, string path)
{
	ofstream fout;
	fout.open(path, std::ios_base::app);
	if (fout.is_open())
	{
		cout << "Input the new class's name: ";
		char input[1000];
		cin.width(1000);
		cin >> input;
		if (findClass(classList, input) != nullptr)
		{
			cout << "Class existed, no need to create more..." << endl;
			return;
		}

		Class *newClass = new Class;
		newClass->className = new char[strlen(input) + 1];
		strcpy(newClass->className, input);

		int noStudent = 0;
		
		newClass->noStudent = noStudent;
		newClass->pNext = classList.classL;
		if (classList.classL != nullptr)
			classList.classL->pPrev = newClass;
		classList.classL = newClass;
		fout << newClass->className << endl;

		string path2 = "Classes/";
		path2.append(newClass->className);
		path2 += ".csv";

		ofstream fout2;
		fout2.open(path2);
		fout2.close();

		cout << "Class Created, please add student to" << newClass->className <<".csv that is newly created in folder Classes !!!!" << endl;
		return;
	}
}

void createSchoolYear(SchoolYearList &schoolYearList, string path)
{

	ofstream fout;
	fout.open(path, std::ios_base::app);
	if (fout.is_open())
	{
		cout << "Input the year following the format (Start-End and End minus Start must be 1): ";
		char input[1000];
		cin.width(1000);
		cin >> input;

		while (!validSchoolYear(input))
		{
			cout << "Input the year following the format (Start-End and End minus Start must be 1): ";
			cin.width(1000);
			cin >> input;
		}

		if (findSchoolYear(schoolYearList, input) != nullptr)
		{
			cout << "School year existed, no need to create more..." << endl;
			return;
		}

		SchoolYear *newSchoolYear = new SchoolYear;
		newSchoolYear->year = new char[strlen(input) + 1];
		strcpy(newSchoolYear->year, input);

		newSchoolYear->pNext = schoolYearList.schoolyearL;
		if (schoolYearList.schoolyearL != nullptr)
			schoolYearList.schoolyearL->pPrev = newSchoolYear;
		schoolYearList.schoolyearL = newSchoolYear;
		fout << newSchoolYear->year << endl;

		cout << "School Year Created !!!!" << endl;
		return;
	}
	else
	{
		cout << "Cannot find or open SchoolYear.txt..." << endl;
		return;
	}
	fout.close();
}

bool validSchoolYear(char input[])
{
	if (strlen(input) != 9 || input[4] != '-')
	{
		return false;
	}
	int yearlen = 4;
	char *start = new char[yearlen], *end = new char[yearlen];
	for (int i = 0; input[i] != '-'; i++)
	{
		int j = i + yearlen + 1;
		start[i] = input[i];
		end[i] = input[j];
	}
	if (atoi(end) - atoi(start) != 1)
		return false;
	return true;
}

SchoolYear *findSchoolYear(SchoolYearList schoolYearList, char year[])
{
	if (schoolYearList.schoolyearL == nullptr)
		return nullptr;
	else
	{
		SchoolYear *pCur = schoolYearList.schoolyearL;
		while (pCur != nullptr)
		{
			if (strcmp(pCur->year, year) == 0)
				return pCur;
			else
				pCur = pCur->pNext;
		}
		return nullptr;
	}
}

Class *findClass(classList &classList, char className[])
{
	if (classList.classL == nullptr)
		return nullptr;
	else
	{
		Class *pCur = classList.classL;
		while (pCur != nullptr)
		{
			if (strcmp(pCur->className, className) == 0)
				return pCur;
			else
				pCur = pCur->pNext;
		}
		return nullptr;
	}
}
void displaySchoolYears(SchoolYearList schoolYearList)
{
	if (schoolYearList.schoolyearL == nullptr)
		return;
	cout << "List of School Years: " << endl;
	SchoolYear *cur = schoolYearList.schoolyearL;
	while (cur != nullptr)
	{
		cout << cur->year << endl;
		cur = cur->pNext;
	}
}
void displayStudent(Class *cl)
{
	if (cl->studentList == nullptr)
		return;
	cout << "There are " << cl->noStudent << " students in class " << cl->className << " :" << endl;
	Student *cur = cl->studentList;
	while (cur != nullptr)
	{

		cout << cur->No << " " << cur->studentID << " " << cur->firstName << " " << cur->lastName
			 << " " << cur->birth.day << "/" << cur->birth.month << "/" << cur->birth.year << " " << cur->socialID << " " << cur->Gender << endl;
		cur = cur->pNext;
	}
	cout << endl;
}
void displayClasses(classList classList)
{
	if (classList.classL == nullptr)
		return;
	cout << "List of Classes: " << endl;
	Class *cur = classList.classL;
	while (cur != nullptr)
	{
		cout << cur->className << endl;
		;
		//displayStudent(cur);
		cur = cur->pNext;
	}
}
void deleteSchoolYearList(SchoolYearList &schoolYearList)
{
	if (schoolYearList.schoolyearL == nullptr)
		return;
	while (schoolYearList.schoolyearL != nullptr)
	{
		SchoolYear *tmp = schoolYearList.schoolyearL;
		schoolYearList.schoolyearL = schoolYearList.schoolyearL->pNext;
		delete tmp;
	}
}

void deleteClassList(classList &classList)
{
	if (classList.classL == nullptr)
		return;
	while (classList.classL != nullptr)
	{
		Class *tmp = classList.classL;
		classList.classL = classList.classL->pNext;
		deleteStudentList(tmp);
		delete tmp;
	}
}
void deleteStudentList(Class *&cl)
{
	if (cl->studentList == nullptr)
		return;
	while (cl->studentList != nullptr)
	{
		Student *tmp = cl->studentList;
		cl->studentList = cl->studentList->pNext;
		delete tmp;
	}
}
