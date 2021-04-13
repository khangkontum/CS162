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
		cout << "3. Add a student to a class" << endl;
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
	string path = "Classe/";
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
	fin.close();
	return count - 1;
}

void dateCSVToInt(string s, Date &d)
{
	int count = 0;
	string day, month, year;
	for (int i = 0; i < s.length() + 1; i++)
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

		int noStudent = loadStudent(newClass);
		if (noStudent == 0 || newClass->studentList == nullptr)
		{
			cout << "Please add student to " << newClass->className << ".csv " << endl;
		}
		newClass->noStudent = noStudent;
		newClass->pNext = classList.classL;
		if (classList.classL != nullptr)
			classList.classL->pPrev = newClass;
		classList.classL = newClass;
		fout << newClass->className << endl;

		cout << "Class Created !!!!" << endl;
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





//PHU HUNG



// LOAD COURSE LIST

// load a course list from file
void loadCourseList(Semester*& smt){

	// Create path
	string path="";
	for(int i=0;i<strlen(smt->schoolYear);++i)path+=smt->schoolYear[i];	// path = "2020-2021"
	path+="_Semester"+to_string(smt->ordinal)+"_CourseList.csv";	// path = "2020-2021_Semester1_CourseList.csv"

	// load all courses from file 2020-2021_Semester1_CourseList.csv
	ifstream fin;
	fin.open(path);
	if(fin.is_open()){
		Course* curC=smt->courseHead;
		while(!fin.eof()){
			if(!smt->courseHead){
				smt->courseHead=new Course;
				curC=smt->courseHead;
			}
			else{
				curC->courseNext=new Course;
				curC->courseNext->coursePrev=curC;
				curC=curC->courseNext;
			}
			loadCourse(fin,curC);
		}
	}
	fin.close();
}

// load a course from file
void loadCourse(istream& fin,Course*& course){
	char tmp[101];

	// load course id

	fin.ignore();
	fin.get(tmp,101,',');
	course->couresID=new char[strlen(tmp)+1];
	for(int i=0;i<strlen(tmp);++i)
		course->courseID[i]=tmp[i];
	course->courseID[strlen(tmp)]='\0';

	// load course name

	fin.ignore();
	fin.get(tmp,101,',');
	course->couresName=new char[strlen(tmp)+1];
	for(int i=0;i<strlen(tmp);++i)
		course->courseName[i]=tmp[i];
	course->courseName[strlen(tmp)]='\0';

	// load teacher name

	fin.ignore();
	fin.get(tmp,101,',');
	course->teacherName=new char[strlen(tmp)+1];
	for(int i=0;i<strlen(tmp);++i)
		course->teacherName[i]=tmp[i];
	course->teacherName[strlen(tmp)]='\0';

	// load the number of credits and the maximum number of students

	fin>>course->numberOfCredits;
	fin>>course->maximumNumberOfStudents;

	// load 2 sessions

	loadSession(fin,course->session1);
	loadSession(fin,course->session2);

	course->courseNext=nullptr;
	course->coursePrev=nullptr;
}

// load a session from file
void loadSession(istream& fin,Session& session){
	session.dayOfWeek=new char[4];
	fin.ignore();
	fin.get(session.dayOfWeek,4,',');
	fin>>session.ordinalSession;
}



// DISPLAY A COURSE LIST
// user can input school year and semester

// display the course list of a semester of a school year 
void viewCourseListOfASemesterOfASchoolYear(SchoolYearList& schlYL){
	cout<<"School year:\n";
	int count=0;
	SchoolYear* schlY=schlYL.schoolyearL;
	while{schlY}{
		++count;
		cout<<count<<". "<<schlY->year<<endl;
		sclY=schY->pNext;
	}
	cout<<"Answer: ";
	int option;
	cin>>option;
	if(option<0||option>count){
		cout<<"Your choice is invalid!\nDoyou want to try again?\n";
		cout<<"1. Yes\n2. No\nAnswer: ";
		cin>>option;
		if(option==1){
			clearScreen();
			viewCourseListOfASemesterOfASchoolYear(schlYL);
		}
	}
	else{
		schlY=schlYL.schoolyearL;
		for(int i=0;i<option;++i)schlY=schlY->pNext;
		viewCourseListOfASemester(schlY);
	}
}

// display the course list of a semester
void viewCourseListOfASemester(SchoolYear* schlY){
	cout<<"Semester:\n";
	int count=0;
	Semester* smt=schlY->semesterHead;
	while(smt){
		++count;
		cout<<count<<". Semester "<<smt->ordinalSemester<<endl;
	}
	cout<<"Answer: ";
	int option;
	cin>>option;
	if(option<0||option>count){
		cout<<"Your choice is invalid!\nDoyou want to try again?\n";
		cout<<"1. Yes\n2. No\nAnswer: ";
		cin>>option;
		if(option==1){
			clearScreen();
			viewCourseListOfASemester(schlY);
		}
	}
	else{
		smt=schlY->semesterHead;
		for(int i=0;i<option;++i)smt=smt->semesterNext;
	}
	
	viewCourseList(->courseHead);
}

// display the course list
void viewCourseList(Course* courseHead){
	Course* curC=courseHead;
	while(curC){
		viewCourse(curC);
		curC=curC->courseNext;
	}
}

// display one course
void viewCourse(Course* course){
	cout<<"ID: "<<course->courseID;
	cout<<"\nName: "<<course->courseName;
	cout<<"\nTeacher name: "<<course->teacherName;
	cout<<"\nThe number of credits: "<<course->numberOfCredits;
	cout<<"\nThe maximum number of students: "<<course->maximumNumberOfStudents;

	// Session 1
	cout<<"\nSesson1: "<<course->session1.dayOfWeek<<", ";
	if(course->session1.ordinalSession==1)cout<<"7:30";
	else if(course->session1.ordinalSession==2)cout<<"9:30";
	else if(course->session1.ordinalSession==3)cout<<"13:30";
	else cout<<"15:30";

	// Session 2
	cout<<"\nSesson2: "<<course->session2.dayOfWeek<<", ";
	if(course->session2.ordinalSession==1)cout<<"7:30\n";
	else if(course->session2.ordinalSession==2)cout<<"9:30\n";
	else if(course->session2.ordinalSession==3)cout<<"13:30\n";
	else cout<<"15:30\n";
}



// UPDATE THE INFORMATION OF A COURSE

void updateCourse(Course*& course){
	int option=0;
	cout<<"What do want to update?\n";
	cout<<"1. Course ID\n2. Course name\n3. Teacher's name";
	cout<<"4. The number of credits\n5. The maximum number of students\n";
	cout<<"6. Session 1\n7. Session 2\n";
	cout<<"Answer: ";
	cin>>option;
	if(option==1){
		delete[]course->courseID;
		char tmp[101];
		cout<<"New course ID: ";
		cin.ignore();
		cin.get(tmp,101);
		course->couresID=new char[strlen(tmp)+1];
		for(int i=0;i<strlen(tmp);++i)
			course->courseID[i]=tmp[i];
		course->courseID[strlen(tmp)]='\0';
	}
	else if(option==2){
		delete[]course->courseName;
		char tmp[101];
		cout<<"New course name: ";
		cin.ignore();
		cin.get(tmp,101);
		course->couresName=new char[strlen(tmp)+1];
		for(int i=0;i<strlen(tmp);++i)
			course->courseName[i]=tmp[i];
		course->courseName[strlen(tmp)]='\0';
	}
	else if(option==3){
		delete[]course->teacherName;
		char tmp[101];
		cout<<"New teacher's name: ";
		cin.ignore();
		cin.get(tmp,101,',');
		course->teacherName=new char[strlen(tmp)+1];
		for(int i=0;i<strlen(tmp);++i)
			course->teacherName[i]=tmp[i];
		course->teacherName[strlen(tmp)]='\0';
	}
	else if(option==4){
		cout<<"New number of credits: ";
		cin>>course->numberOfCredits;
	}
	else if(option==5){
		cout<<"New maximum number of students: ";
		cin>>course->maximumNumberOfStudents;
	}
	else if(option==6){
		cout<<"What do you want to update in Session 1?\n";
		cout<<"1. Day of the week\n2. Ordinal session\nAnswer: ";
		cin>>option;
		if(option==1){
			delete[]course->session1.dayOfWeek;
			course->session1.dayOfWeek=new char[4];
			cout<<"New day of the week: ";
			cin.ignore();
			cin.get(course->session1.dayOfWeek,4);
		}
		else{
			cout<<"New ordinal session: ";
			cin>>course->session1.ordinalSession;
		}
	}
	else{
		cout<<"What do you want to update in Session 2?\n";
		cout<<"1. Day of the week\n2. Ordinal session\nAnswer: ";
		cin>>option;
		if(option==1){
			delete[]course->session2.dayOfWeek;
			course->session2.dayOfWeek=new char[4];
			cout<<"New day of the week: ";
			cin.ignore();
			cin.get(course->session2.dayOfWeek,4);
		}
		else{
			cout<<"New ordinal session: ";
			cin>>course->session2.ordinalSession;
		}
	}
	cout<<"Do you want to update anything else?\n";
	cout<<"1. Yes\n2. No\nAnswer: ";
	cin>>option;
	if(option==1)updateCourse(course);
}



// DELETE A COURSE

void deleteACourse(Course*& courseHead){

}


// CREATE SEMESTER

// create a semester
void creatSemester(SchoolYear*& schlY){
	Semester* curSmt=schlY->semesterHead;

	// if schlY had 3 semesters: return

	if(!schlY->semesterHead){	// if chlY doesn't have any semester
		schlY->semesterHead=new Semester;
		schlY->semesterHead->ordianlSemester=1;
		curSmt=schlY->semesterHead;
	}
	else{
		int count=1;
		while(curSmt->semesterNext){	// because semesterHead is not nullptr
			++count;
			curSmt=curSmt->semesterNext;
		}
		if(count==3){	// schY had 3 semesters?
			cout<<schlY->year<<" had 3 semesters!\n";
			return;
		}
		else{
			curSmt->semesterNext=new Semester;
			curSmt->semesterNext->ordinalSemester=curSmt->ordinalSemester+1;	// ordinal
			curSmt->semesterNext->semesterPrev=curSmt;	// Previous semester
			curSmt=curSmt->semesterNext;
		}
	}

	// schoolYear of semester
	curSmt->schoolYear=schlY->year;

	// Input start date
	cout<<"Start date:\n";
	cout<<"Day: ";
	cin>>curSmt->startDate.day;
	cout<<"Month: ";
	cin>>curSmt->startDate.month;
	cout<<"Year: ";
	cin>>curSmt->startDate.year;

	// Input end date
	cout<<"End date:\n";
	cout<<"Day: ";
	cin>>curSmt->endDate.day;
	cout<<"Month: ";
	cin>>curSmt->endDate.month;
	cout<<"Year: ";
	cin>>curSmt->endDate.year;

	// Load course list
	loadCourseList(curSmt);
}

// find a semester
Semester* findSemester(SchoolYear* schlY,int n){
	if(!schlY->semesterHead)return nullptr;
	Semester* curSmt=schlY->semesterHead;
	while(curSmt){
		if(curSmt->ordinalSemester==n)return curSmt;
		curSmt=curSmt->semesterNext;
	}
	return nullptr;
}