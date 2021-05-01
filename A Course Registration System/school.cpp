#include "school.h"
#include "login.h"
#include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef _WIN32
#include <windows.h>
#endif

classList globalClassList;

char* converToChar(string path){
    char* s = new char[path.size() +1];
    for (int i=0,ii=path.size();i<ii;++i)
        s[i] = path[i];
    s[path.size() + 1] = '\0';
    return s;
}

void PressEnterToContinue()
{
	system("read -p \"Press a key to continue...\" -n 1 -s\n");

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
		cout << "4. Add a Student to a Class" << endl;
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
		else if (option == 4) {
			addAStudentToClass(classList);
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
void addAStudentToClass(classList &classList) {
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
		string path = "Classes/";
		path.append(addClass->className);
		path += ".csv";
		ofstream fout;
		fout.open(path, std::ios_base::app);
		if (fout.is_open()) {
			Student *x = inputStudent();
			fout << x->firstName << ',';
			fout << x->lastName << ',';
			fout << x->studentID << ',';
			string date = to_string(x->birth.day) + '/' + to_string(x->birth.month) + '/' + to_string(x->birth.year);
			fout << date << ',';
			fout << x->socialID << ",";
			fout << x->Gender << endl;

			x->No = addClass->noStudent + 1;
			x->posClass = addClass;
			if (addClass->studentList == nullptr) {
				addClass->studentList = x;
				x->pPrev = nullptr;
				addClass->studentLast = addClass->studentList;
			}
			else {
				x->pPrev = addClass->studentLast;
				addClass->studentLast->pNext = x;
				addClass->studentLast = x;
			}
			addClass->noStudent++;
			addClass->studentLast->pNext = nullptr;
		}
		cout << "Successfully added new student...";
		displayStudent(addClass);
		system("pause");
	}
}
Student *inputStudent() {
	string firstName, lastName, studentID, Gender, socialID, date;
	cout << "Please input student's firstname: ";
	cin.get();
	getline(cin, firstName);
	cout << "Please input student's lastname: ";
	getline(cin, lastName);
	cout << "Please input Student ID (8 digits): ";
	getline(cin, studentID);
	while (studentID.length() != 8) {
		cout << "Wrong format, please input Student ID (6 digits): ";
		getline(cin, studentID);
	}
	cout << "Please input Student gender (male/female): ";
	getline(cin, Gender);
	while (Gender != "male" && Gender != "female") {
		cout << "Wrong format, please input Student gender (male/female): ";
		getline(cin, Gender);
	}
	cout << "Please input Student social ID : ";
	getline(cin, socialID);

	Date d;
	cout << "Please input Student Date of birth (dd/mm/yyyy): ";
	getline(cin, date);
	dateCSVToInt(date, d);

	while (d.day == 0 && d.month == 0 && d.year == -1) {
		cout << "Wrong format, please input Student Date of birth (dd/mm/yyyy): ";
		getline(cin, date);
		dateCSVToInt(date, d);
	}

	Student *x = new Student;

	x->firstName = firstName;
	x->lastName = lastName;
	x->Gender = Gender;
	x->socialID = socialID;
	x->studentID = studentID;
	x->birth = d;
    createUser(x);
	return x;
}
void loadClassList(classList &classList)
{
	ifstream fin;
	string path = "Classes/Classes.txt";
	fin.open(path);

	if (fin.is_open())
	{
		char dummy[10000];
		while (!fin.eof() && fin>>dummy)
		{
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

			newStudent->posClass = cl;

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
		cl->studentLast = pCur;
	}
	fin.close();
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
	if (day == "" || month == "" || year == "")
		return;


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

void createSchoolYear(SchoolYearList &schoolYearList, string path = "SchoolYear/SchoolYear.txt")
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
		//return;
	}
	else
	{
		cout << "Cannot find or open SchoolYear.txt..." << endl;
		//return;
	}
	fout.close();
	path = "SchoolYear/" + string(schoolYearList.schoolyearL->year);
	char* tPath = new char[path.size()+1];
	for (int i=0,ii=path.size(); i<ii; ++i)
        tPath[i] = path[i];
    tPath[path.size()] = '\0';
    //cerr<<tPath<<endl;
    mkdir(tPath);
    path = "SchoolYear/" + string(schoolYearList.schoolyearL->year)+"/currentSemester.txt";
    //cerr<<path<<endl;
    ofstream fo;
    fo.open(path);
    fo<<0;
    fo.close();


    path = "SchoolYear/" + string(schoolYearList.schoolyearL->year)+"/semesterList.txt";
    //cerr<<path<<endl;
    fo.open(path);
    fo.close();

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

		cout << cur->No << "  " << cur->studentID << "  " << cur->firstName << "  " << cur->lastName
			 << "  " << cur->birth.day << "/" << cur->birth.month << "/" << cur->birth.year << "  " << cur->socialID << "  " << cur->Gender << endl;
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


// DATE

// input a date
void inputDate(Date& d){
	cout<<"Day: ";
	cin>>d.day;
	cout<<"Month: ";
	cin>>d.month;
	cout<<"Year: ";
	cin>>d.year;
}

// get the current date
Date currentDate(){
	Date d;
	time_t now = time(0);
    tm *ltm = localtime(&now);

    d.year=1900 + ltm->tm_year;
    d.month=1 + ltm->tm_mon;
    d.day=ltm->tm_mday;
	return d;
}

// is the bigger day?
bool isBiggerDate(Date& d1,Date& d2){
	if(d1.year>d2.year)return true;
	if(d1.year<d2.year)return false;
	if(d1.month>d2.month)return true;
	if(d1.month<d2.month)return false;
	return d1.day>d2.day;
}



// CREATE SEMESTER

// load a semester
void loadSemester(SchoolYear*&schlY){
	ifstream fin;
	Semester*smt=schlY->semesterHead;
	for(int i=0;i<3;++i){
		string path="SchoolYear/";
		for(int j=0;j<strlen(schlY->year);++j)path+=schlY->year[j];
		path+="/Semester "+to_string(i+1);
		fin.open(path+"/Information.txt");
		if(fin.is_open()){
			if(!schlY->semesterHead){
				schlY->semesterHead=new Semester;
				smt=schlY->semesterHead;
			}
			else{
				smt->semesterNext=new Semester;
				smt->semesterNext->semesterPrev=smt;
				smt=smt->semesterNext;
			}
			smt->schoolYear=schlY->year;
			smt->ordinalSemester=i+1;
			fin>>smt->startDate.day
				>>smt->startDate.month
				>>smt->startDate.year;
			fin>>smt->endDate.day
				>>smt->endDate.month
				>>smt->endDate.year;
			fin>>smt->registrationSession.startDate.day
				>>smt->registrationSession.startDate.month
				>>smt->registrationSession.startDate.year;
			fin>>smt->registrationSession.endDate.day
				>>smt->registrationSession.endDate.month
				>>smt->registrationSession.endDate.year;
			loadCourseList(smt);
		}
		else return;
	}
}

// create a semester
void createSemester(SchoolYear*& schlY){
	Semester* curSmt=schlY->semesterHead;

	// if schlY had 3 semesters: return

	if(!schlY->semesterHead){	// if chlY doesn't have any semester
		schlY->semesterHead=new Semester;
		schlY->semesterHead->ordinalSemester=1;
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
	inputDate(curSmt->startDate);

	// Input end date
	cout<<"End date:\n";
	inputDate(curSmt->endDate);

	// Load course list
	//loadCourseList(curSmt);
	cout<<"Do you want to input a course?\n";
	cout<<"1. Yes\n2. No\nAnswer: ";
	int option;
	cin>>option;
	if(option)inputCourseList(curSmt);

	// create the course registration session
	cout<<"Do you want to create a course registration session?\n";
	cout<<"1. Yes\n2. Later\nAnswer: ";
	cin>>option;
	if(option)createRegistrationSession(curSmt);

	//	save Semester mới tạo vào file
	string path="";
	for(int j=0;j<strlen(schlY->year);++j)path+=schlY->year[j];
	path+="/Semester "+curSmt->ordinalSemester;
	mkdir(path,0777);
	saveSemester_toFile(curSmt);
}

// save a semester to file
void saveSemester_toFile(Semester*&s){
	string path="schoolyear/";
	for(int i=0;i<strlen(s->schoolYear);++i)path+=s->schoolYear[i];
	path+="/Semester "+to_string(s->ordinalSemester);
	//cerr<<path<<endl;
	mkdir(converToChar(path));/// tao folder
	path+="/Information.txt";
	ofstream fout;
	fout.open(path);
	if(fout.is_open()){
		fout<<s->startDate.day<<" "
			<<s->startDate.month<<" "
			<<s->startDate.year<<endl;
		fout<<s->endDate.day<<" "
			<<s->endDate.month<<" "
			<<s->endDate.year<<endl;
		fout<<s->registrationSession.startDate.day<<" "
			<<s->registrationSession.startDate.month<<" "
			<<s->registrationSession.startDate.year<<endl;
		fout<<s->registrationSession.endDate.day<<" "
			<<s->registrationSession.endDate.month<<" "
			<<s->registrationSession.endDate.year<<endl;
	}
	fout.close();
	path="";
	for(int i=0;i<strlen(s->schoolYear);++i)path+=s->schoolYear[i];
	path+="/Semester "+to_string(s->ordinalSemester)+"/CourseList.csv";
	saveCourseList_toFile(s->courseHead,path);
}

// delete a semester list
void deleteSemesterList(Semester*&semesterHead){
	Semester*s=semesterHead;
	while(s){
		Semester*tmp=s;
		s=s->semesterNext;
		deleteCourseList(tmp->courseHead);
		delete[]tmp->schoolYear;
		delete tmp;
	}
}



// CREATE A COURSE REGISTRATION SESSION

// choose a semester from school year list and create a course registration session
void createRegistrationSession_fromSchoolYearList(SchoolYearList& schlYL){
	SchoolYear* schlY=chooseSchoolYear(schlYL);
	if(!schlY)return;
	Semester* smt=chooseSemester(schlY);
	if(!smt)return;
	createRegistrationSession(smt);
}

// create a registration session
void createRegistrationSession(Semester*& smt){
	if(smt->registrationSession.startDate.day!=0){
		cout<<"Semester "<<smt->ordinalSemester<<" had a course registration session!\n";
		return;
	}
	inputDate(smt->registrationSession.startDate);
	inputDate(smt->registrationSession.endDate);
}



// LOAD COURSE LIST

// from FILE

// load a course list
void loadCourseList(Semester*& smt){

	// Create path
	string path="schoolyear/";
	for(int i=0;i<strlen(smt->schoolYear);++i)path+=smt->schoolYear[i];	// path = "2020-2021"
	path+="/Semester "+to_string(smt->ordinalSemester)+"/CourseList.csv";	// path = "2020-2021\Semester 1\CourseList.csv"
    // load all courses from file 2020-2021\Semester 1\CourseList.csv
	ifstream fin;
	fin.open(path);
	if(fin.is_open()){

		// create a new course
		Course* courseNew = new Course;
		while(!fin.eof() && loadCourse(fin, courseNew)){
			courseNew->courseNext=smt->courseHead;
			if(smt->courseHead)smt->courseHead->coursePrev=courseNew;
			smt->courseHead=courseNew;
			 courseNew = new Course;
		}
	}
	else cout<<path<<" is non-existent.\n";
	fin.close();
}

// load a course
bool loadCourse(istream& fin, Course*& course) {
	string dummy;
	getline(fin, dummy, ',');
	if (dummy == "") {
		delete course;
		return false;
	}
	course->courseID = dummy;

	getline(fin, dummy, ',');
	course->courseName = new char[dummy.length() + 1];
	strcpy(course->courseName, dummy.c_str());

	getline(fin, dummy, ',');
	course->teacherName = new char[dummy.length() + 1];
	strcpy(course->teacherName, dummy.c_str());

	getline(fin, dummy, ',');
	course->numberOfCredits = stoi(dummy);

	getline(fin, dummy, ',');
	course->maximumNumberOfStudents = stoi(dummy);

	getline(fin, dummy, ',');
	course->numberOfStudents = stoi(dummy);

	getline(fin, dummy, ',');
	course->session1.dayOfWeek = new char[dummy.length() + 1];
	for (int i = 0; i < dummy.length() + 1; i++) {
		course->session1.dayOfWeek[i] = dummy[i];
	}

	getline(fin, dummy, ',');
	course->session1.ordinalSession = stoi(dummy);

	getline(fin, dummy, ',');
	course->session2.dayOfWeek = new char[dummy.length() + 1];
	for (int i = 0; i < dummy.length() + 1; i++) {
		course->session2.dayOfWeek[i] = dummy[i];
	}

	getline(fin, dummy);
	course->session2.ordinalSession = stoi(dummy);

	return true;
	/*
	char tmp[101];
	// load course id
	fin.ignore();
	fin.get(tmp,101,',');
	course->courseID=new char[strlen(tmp)+1];
	for(int i=0;i<strlen(tmp);++i)
		course->courseID[i]=tmp[i];
	course->courseID[strlen(tmp)]='\0';
	cerr<<course->courseID<<endl;

	// load course name
	fin.ignore();
	fin.get(tmp,101,',');
	course->courseName=new char[strlen(tmp)+1];
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
	fin.get();	// đọc dấu phẩy
	fin>>course->numberOfCredits;
	fin.get();	// đọc dấu phẩy
	fin>>course->maximumNumberOfStudents;
	fin>>course->numberOfStudents;

	// load 2 sessions
	// this function is below
	loadSession(fin,course->session1);
	fin.get();	// đọc dấu phẩy
	loadSession(fin,course->session2);
	*/

}

// load a session
void loadSession(istream& fin,Session& session){
	session.dayOfWeek=new char[4];
	fin.ignore();
	fin.get(session.dayOfWeek,4,',');
	fin.get();	// đọc dấu phẩy
	fin>>session.ordinalSession;
}

// from TERMINAL

// choose school year and semester to insert a course
void inputCourse_fromSchoolYearList(SchoolYearList& schlYL){
	SchoolYear* schlY=chooseSchoolYear(schlYL);
	if(!schlY)return;
	Semester* smt=chooseSemester(schlY);
	if(!smt)return;
	Course* course=new Course;

	// this function is below
	inputCourse(course);

	// insert course at the beginning of course list
	smt->courseHead->coursePrev=course;
	course->courseNext=smt->courseHead;
	smt->courseHead=course;
}

// input a course
void inputCourse(Course*& course){
	char tmp[101];

	// input course id
	cout<<"Course ID: ";
	cin.ignore();
	cin.get(tmp,101);
	course->courseID=new char[strlen(tmp)+1];
	for(int i=0;i<strlen(tmp);++i)
		course->courseID[i]=tmp[i];
	course->courseID[strlen(tmp)]='\0';

	// input course name
	cout<<"Course name: ";
	cin.ignore();
	cin.get(tmp,101);
	course->courseName=new char[strlen(tmp)+1];
	for(int i=0;i<strlen(tmp);++i)
		course->courseName[i]=tmp[i];
	course->courseName[strlen(tmp)]='\0';

	// input teacher name
	cout<<"Teacher name: ";
	cin.ignore();
	cin.get(tmp,101);
	course->teacherName=new char[strlen(tmp)+1];
	for(int i=0;i<strlen(tmp);++i)
		course->teacherName[i]=tmp[i];
	course->teacherName[strlen(tmp)]='\0';

	// input the number of credits and the maximum number of students
	cout<<"The number of credits: ";
	cin>>course->numberOfCredits;
	cout<<"The maximum number of students: ";
	cin>>course->maximumNumberOfStudents;

	// input 2 sessions
	// this function is below
	cout<<"Session 1:\n";
	inputSession(course->session1);
	cout<<"Session 2:\n";
	inputSession(course->session2);
}

// input a session
void inputSession(Session& session){
	cout<<"Day of the week: ";
	session.dayOfWeek=new char[4];
	cin.ignore();
	cin.get(session.dayOfWeek,4,',');
	cout<<"Ordinal session: ";
	cin>>session.ordinalSession;
}

// input a course list of a semester
void inputCourseList(Semester*&smt){
	Course*c=new Course;
	inputCpurse(c);
	c->courseNext=smt->courseHead;
	smt->courseHead->coursePrev=c;
	c=smt->courseHead;
	cout<<"Do you want to input another course?\n";
	cout<<"1. Yes\n2. No\nAnswer: ";
	int option;
	cin>>option;
	if(option)inputCourseList(smt);
}


// DISPLAY A COURSE LIST

// choose a course list from school year list and display it
void viewCourseList_fromSchoolYearList(SchoolYearList& schlYL){
	SchoolYear* schlY=chooseSchoolYear(schlYL);
	if(!schlY)return;
	Semester* smt=chooseSemester(schlY);
	if(!smt)return;

	// this function is below
	viewCourseList(smt->courseHead);
}

// display the course list
void viewCourseList(Course*& courseHead){
	Course* curC=courseHead;
	while(curC){

		// this function is below
		viewCourse(curC);

		curC=curC->courseNext;
	}
}

// display one course
void viewCourse(Course*& course){
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
	cout<<endl;
}



// SAVE A COURSE LIST TO FILE

// save a course list to file
void saveCourseList_toFile(Course*&courseHead,string path){
	ofstream fout;
	fout.open(path);
	if(fout.is_open()){
		Course* curC=courseHead;
		while(curC){
			saveCourse_toFile(curC,fout);
			curC=curC->courseNext;
		}
	}
	fout.close();
}

// save a course to file
void saveCourse_toFile(Course*&c,ostream&fout){
	fout<<c->courseID<<","
		<<c->courseName<<","
		<<c->teacherName<<","
		<<c->numberOfCredits<<","
		<<c->maximumNumberOfStudents<<","
		<<c->numberOfStudents<<",";

	// session 1
	fout<<string(c->session1.dayOfWeek)<<","<<c->session1.ordinalSession<<",";

	// session 2
	fout<<string(c->session2.dayOfWeek)<<","<<c->session2.ordinalSession<<"\n";
}



// UPDATE THE INFORMATION OF A COURSE

// choose a course list from school year list and update it
void updateCourse_fromSchoolYearList(SchoolYearList& schlYL){
	SchoolYear* schlY=chooseSchoolYear(schlYL);
	if(!schlY)return;
	Semester* smt=chooseSemester(schlY);
	if(!smt)return;
	Course* course=chooseCourse(smt);
	if(!course)return;

	// this function is below
	updateCourse(course);
}

// update a course
void updateCourse(Course*& course){
	int option=0;
	cout<<"What do want to update?\n";
	cout<<"1. Course ID\n2. Course name\n3. Teacher's name";
	cout<<"4. The number of credits\n5. The maximum number of students\n";
	cout<<"6. Session 1\n7. Session 2\n";
	cout<<"Answer: ";
	cin>>option;
	if(option==1){
        /*
		delete[]course->courseID;
		char tmp[101];
		cout<<"New course ID: ";
		cin.ignore();
		cin.get(tmp,101);
		course->courseID=new char[strlen(tmp)+1];
		for(int i=0;i<strlen(tmp);++i)
			course->courseID[i]=tmp[i];
		course->courseID[strlen(tmp)]='\0';
		*/
		cout<<"New course ID: ";
        cin>>course->courseID;
	}
	else if(option==2){
		delete[]course->courseName;
		char tmp[101];
		cout<<"New course name: ";
		cin.ignore();
		cin.get(tmp,101);
		course->courseName=new char[strlen(tmp)+1];
		for(int i=0;i<strlen(tmp);++i)
			course->courseName[i]=tmp[i];
		course->courseName[strlen(tmp)]='\0';
	}
	else if(option==3){
		delete[]course->teacherName;
		char tmp[101];
		cout<<"New teacher's name: ";
		cin.ignore();
		cin.get(tmp,101);
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

// choose a course list from school year list and delete it
void deleteCourse_fromSchoolYearList(SchoolYearList& schlYL){
	SchoolYear* schlY=chooseSchoolYear(schlYL);
	if(!schlY)return;
	Semester* smt=chooseSemester(schlY);
	if(!smt)return;
	Course* course=chooseCourse(smt);
	if(!course)return;

	// this function is below
	deleteCourse(smt->courseHead,course);
}

// delete a course
void deleteCourse(Course*& courseHead,Course*& course){
	Course* curC=courseHead;
	while(curC&&curC!=course)curC=curC->courseNext;
	if(curC){
		if(curC->coursePrev)curC->coursePrev->courseNext=curC->courseNext;
		else courseHead=curC->courseNext;
		if(curC->courseNext)curC->courseNext->coursePrev=curC->coursePrev;
		delete curC;
	}
}

// delete a course list
void deleteCourseList(Course*&courseHead){
	Course*c=courseHead;
	while(c){
		Course*tmp=c;
		c=c->courseNext;
		delete[]tmp->courseName;
		delete[]tmp->teacherName;
		delete tmp;
	}
}



// user chooses one course in a semester
Course* chooseCourse(Semester*& smt){
	if(!smt->courseHead){
		cout<<"Semester "<<smt->ordinalSemester<<" has no course!\n";
		return nullptr;
	}
	Course* curC=smt->courseHead;
	int count=0;
	while(curC){
		++count;
		cout<<count<<". "<<curC->courseID<<endl;
	}
	cout<<"Answer: ";
	int option;
	cin>>option;
	if(option<1||option>count){
		cout<<"Your choice is invalid!\nDo you want to try again?\n";
		cout<<"1. Yes\n2. No\nAnswer : ";
		cin>>option;
		if(option==1)return chooseCourse(smt);
		return nullptr;
	}
	curC=smt->courseHead;
	for(int i=1;i<option;++i)curC=curC->courseNext;
	return curC;
}

// user chooses one semester in a school year
Semester* chooseSemester(SchoolYear*& schlY){
	if(!schlY->semesterHead){
		cout<<schlY->year<<" has no semester!\n";
		return nullptr;
	}
	cout<<"Semester:\n";
	int count=0;
	Semester* curSmt=schlY->semesterHead;
	while(curSmt){
		++count;
		cout<<count<<". Semester "<<curSmt->ordinalSemester<<endl;
		curSmt=curSmt->semesterNext;
	}
	cout<<"Answer: ";
	int option;
	cin>>option;
	if(option<1||option>count){
		cout<<"Your choice is invalid!\nDoyou want to try again?\n";
		cout<<"1. Yes\n2. No\nAnswer: ";
		cin>>option;
		if(option==1)return chooseSemester(schlY);
		return nullptr;
	}
	curSmt=schlY->semesterHead;
	for(int i=1;i<option;++i)curSmt=curSmt->semesterNext;
	return curSmt;
}

// user chooses one school year in school year list
SchoolYear* chooseSchoolYear(SchoolYearList& schlYL){
	cout<<"School year:\n";
	int count=0;
	SchoolYear* curSchlY=schlYL.schoolyearL;
	while(curSchlY){
		++count;
		cout<<count<<". "<<curSchlY->year<<endl;
		curSchlY=curSchlY->pNext;
	}
	cout<<"Answer: ";
	int option;
	cin>>option;
	if(option<1||option>count){
		cout<<"Your choice is invalid!\nDoyou want to try again?\n";
		cout<<"1. Yes\n2. No\nAnswer: ";
		cin>>option;
		if(option==1)return chooseSchoolYear(schlYL);
		return nullptr;
	}
	curSchlY=schlYL.schoolyearL;
	for(int i=1;i<option;++i)curSchlY=curSchlY->pNext;
	return curSchlY;
}


// VIEW COURSE LIST, UPDATE AND DELETE A COURSE
	// choose view a course list, update or delete 1 course
void doSomethingWithCourse(SchoolYearList& schlYL){

	// 3 options: view course list, update or delete a course
	cout<<"What do you want to do?\n";
	cout<<"1. View a course list\n";
	cout<<"2. Update a course\n";
	cout<<"3. Add a course\n";
	cout<<"4. Delete a course\n";
	cout<<"5. Create a course registration session\nAnswer: ";
	int option;
	cin>>option;
	if(option<1||option>5){
		cout<<"Your choice is invalid!\nDo you want to try again?\n";
		cout<<"1. Yes\n2. No\nAnswer : ";
		cin>>option;
		if(option==1)doSomethingWithCourse(schlYL);
		return;
	}
	if(option==1)viewCourseList_fromSchoolYearList(schlYL);
	else if(option==2)updateCourse_fromSchoolYearList(schlYL);
	else if(option==3)inputCourse_fromSchoolYearList(schlYL);
	else if(option==4)deleteCourse_fromSchoolYearList(schlYL);
	else createRegistrationSession_fromSchoolYearList(schlYL);
	cout<<"Do you want to do anything else?\n1. Yes\n2. No\nAnswer: ";
	cin>>option;
	if(option==1)doSomethingWithCourse(schlYL);
}

// Trace

Student* getStudentFromUser(User* user){
    if (user->posStudent != nullptr) return user->posStudent;
    classList cList;
    if (globalClassList.classL == nullptr)
        loadClassList(globalClassList);
    cList = globalClassList;
    Class* cur = cList.classL;
    while(cur != nullptr){
        Student* curStu = cur->studentList;
        while(curStu != nullptr){
            if (curStu->studentID == user->username){
                user->posStudent = curStu;
                break;
            }
            curStu = curStu->pNext;
        }
        if (user->posStudent != nullptr)
            break;
        cur = cur->pNext;
    }
    return user->posStudent;
}
Class* getClassFromUser(User* user){
    return user->posStudent->posClass;
}
SchoolYear* getSchoolYearFromUser(User* user){
    return user->posStudent->posClass->posSchoolYear;
}

int countCurrentCourse(User* user){
    Course* cou = getCourseListOfUser(user);
    int cnt = 0;
    while(cou != nullptr){
        if (cou->status == 1) ++cnt;
        cou = cou->courseNext;
    }
    while(cou != nullptr){
        Course* tmp = cou->coursePrev;
        delete cou;
        cou = tmp;
    }
    return cnt;
}
bool isAvailableCourse(string courseId, Course* couList){
    bool k = false;
    while(couList != nullptr){
        if (couList->courseID == courseId)
            k = true;
        couList = couList->courseNext;
    }
    return k;
}

Course* getCourseFromCourseId(string courseId){
    SchoolYearList schYearList;
    loadSchoolYearList(schYearList);
    Semester* sem = new Semester;
    sem->ordinalSemester = getCurrentSemester();
    sem->schoolYear = schYearList.schoolyearL->year;
    sem->courseHead = nullptr;
    loadCourseList(sem);

    Course* couList = sem->courseHead;
    delete sem;

    Course* cur = couList;
    while(cur != nullptr){
        if (cur->courseID == courseId) break;
        cur = cur->courseNext;
    }
    return cur;
}

bool isConflictedCourse(string courseId, User* user){

    Course* cou = getCourseListOfUser(user);
    Course* cur = getCourseFromCourseId(courseId);

    bool k = false;
    while(cou != nullptr){
        Course* tmp = cou->courseNext;
        Course* gg = getCourseFromCourseId(cou->courseID);
        if (!k && isConflictedSession(gg, cur))
            k = true;

        delete cou;
        cou = tmp;
    }
    delete cur;
    return k;

}

bool isSameSession(Session& s1,Session& s2){
	return strcmp(s1.dayOfWeek,s2.dayOfWeek)==0 && s1.ordinalSession==s2.ordinalSession;
}
bool isConflictedSession(Course* courseA, Course* courseB){
    if (courseA == nullptr || courseB == nullptr)
        return false;
    return isSameSession(courseA->session1,courseB->session1)||isSameSession(courseA->session2,courseB->session1)||
		isSameSession(courseA->session1,courseB->session2)||isSameSession(courseA->session2,courseB->session2);
}

int getCurrentSemester(){
    SchoolYearList schYearList;
    loadSchoolYearList(schYearList);
    string path="SchoolYear/"+string(schYearList.schoolyearL->year)+"/currentSemester.txt";

    int curSem;
    ifstream fi;
    fi.open(path);
    fi>>curSem;
    fi.close();

    return curSem;
}

string getCurrentPathSem(){
    SchoolYearList schYearList;
    loadSchoolYearList(schYearList);
    string path="SchoolYear/"+string(schYearList.schoolyearL->year)+"/Semester " + to_string(getCurrentSemester());
    return path;
}

Semester* getCurrentSemesterList(){
    SchoolYearList schYearList;
    loadSchoolYearList(schYearList);
    Semester* sem = new Semester;
    sem->ordinalSemester = getCurrentSemester();
    sem->schoolYear = schYearList.schoolyearL->year;
    sem->courseHead = nullptr;
    loadCourseList(sem);
    return sem;

}

Course* getCourseListOfUser(User* user){
    string path = "students/" + user->username + ".csv";
    ifstream fi;
    fi.open(path);
    string tmp;
    getline(fi,tmp);
    Course* cou = nullptr;
    while(getline(fi, tmp)){
        Course* cur = new Course;
        cur->courseNext = nullptr;
        cur->coursePrev = nullptr;
        ///course ID
        int i = 0, j = 0;
        while(j<tmp.size() && tmp[j] != ',') ++j;
        cur->courseID = tmp.substr(i, j-i);
        i = ++j;
        ///course Name
        while(j<tmp.size() && tmp[j] != ',') ++j;
        cur->courseName = converToChar(tmp.substr(i, j-i));
        i = ++j;
        ///Status
        while(j<tmp.size() && tmp[j] != ',') ++j;
        cur->status = stoi(tmp.substr(i, j-i));
        i = ++j;
        ///Total mark
        while(j<tmp.size() && tmp[j] != ',') ++j;
        cur->totalMark = stoi(tmp.substr(i, j-i));
        i = ++j;
        ///Final mark
        while(j<tmp.size() && tmp[j] != ',') ++j;
        cur->finalMark = stoi(tmp.substr(i, j-i));
        i = ++j;
        ///Midterm mark
        while(j<tmp.size() && tmp[j] != ',') ++j;
        cur->midTermMark = stoi(tmp.substr(i, j-i));
        i = ++j;
        ///other mark
        while(j<tmp.size() && tmp[j] != ',') ++j;
        cur->otherMark = stoi(tmp.substr(i, j-i));
        i = ++j;
        ///day start
        while(j<tmp.size() && tmp[j] != '/') ++j;
        cur->startDay.day = stoi(tmp.substr(i, j-i));
        i = ++j;
        ///month start
        while(j<tmp.size() && tmp[j] != '/') ++j;
        cur->startDay.month = stoi(tmp.substr(i, j-i));
        i = ++j;
        ///year start
        while(j<tmp.size() && tmp[j] != '-') ++j;
        cur->startDay.year = stoi(tmp.substr(i, j-i));
        i = ++j;
        ///end start
        while(j<tmp.size() && tmp[j] != '/') ++j;
        cur->startDay.day = stoi(tmp.substr(i, j-i));
        i = ++j;
        ///end start
        while(j<tmp.size() && tmp[j] != '/') ++j;
        cur->startDay.month = stoi(tmp.substr(i, j-i));
        i = ++j;
        ///end start
        while(j<tmp.size() && tmp[j] != ',') ++j;
        cur->startDay.year = stoi(tmp.substr(i, j-i));
        i = ++j;
        ///count
        while(j<tmp.size() && tmp[j] != ',') ++j;
        cur->count = stoi(tmp.substr(i, j-i));
        i = ++j;

        cur->courseNext = cou;
        if (cou != nullptr)
            cou->coursePrev = cur;
        cou = cur;

    }
    fi.close();

    return cou;
}
