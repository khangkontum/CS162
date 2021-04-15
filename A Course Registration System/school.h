#define _CRT_SECURE_NO_DEPRECATE
#ifndef _School_
#define _School_
#include<iostream>
#include <fstream>
#include<string.h>
#include<string>
#include<ctime>
#include <Windows.h>

using namespace std;

struct User{
    string password;
	string username;
	string Name;
	string phoneNumber;
	string email;
    int flag =0 ;
    User*uNext, *uPre;
};
struct UserList{
    User* fUser;
    UserList(): fUser(nullptr){}
};
struct Date{
    int day, month, year;
};


struct Student{
    string firstName, lastName, studentID, Gender, socialID;
	int No;
    Date birth;
    Student* pNext, *pPrev;
    Student(): courseHead(nullptr),pPrev(nullptr), pNext(nullptr) {}

};
struct Class{
    char* className;
    int noStudent;
    Student* studentList = nullptr;  
    Class* pNext, *pPrev;
    Class(): pNext(nullptr), pPrev(nullptr) {}
};
struct classList {
	Class* classL = nullptr;
};
struct SchoolYear{
	char * year = nullptr;
  //  Class* classList = nullptr;   
    SchoolYear* pNext, *pPrev;
   // Semester* semesterList = nullptr;
    SchoolYear() : pNext(nullptr), pPrev(nullptr) {}
   // SchoolYear(SchoolYear* prev_school_year, int x,int y) : pNext(nullptr), pPrev(prev_school_year), startYear(x), endYear(y) {}

   // Phu Hung
   // Add Semester
   Semester* semesterHead=nullptr;
};

struct SchoolYearList{
    SchoolYear* schoolyearL = nullptr;
};

void displayCommandMenu();

//school Year
void loadSchoolYearList(SchoolYearList &schoolYearList);
void createSchoolYear(SchoolYearList &schoolYearList, string path);
void displaySchoolYears(SchoolYearList schoolYearList);
SchoolYear *findSchoolYear(SchoolYearList schoolYearList, char year[]);
bool validSchoolYear(char input[]);
void deleteSchoolYearList(SchoolYearList &schoolYearList);

// Class
void createClasses(classList &classList, string path);
void loadClassList(classList &classList);
Class* findClass(classList &classList, char className[]);
int loadStudent(Class *&cl);
void displayClasses(classList classList);
void dateCSVToInt(string s, Date &d);
void displayStudent(Class* cl);
void deleteClassList(classList &classList);
void deleteStudentList(Class *&cl);
void addStudentsToClass(classList &classList);





// Phu Hung

// SEMESTER

struct RegistrationSession{
    Date startDate,endDate;
    RegistrationSession(): startDate.day(0),endDate.day(0){}
};

struct Semester{
    Date startDate,endDate;
    int ordinalSemester;
    char* schoolYear;
    Course* courseHead;
    RegistrationSession registrationSession;
    Semester* semesterNext;
    Semester* semesterPrev;
    Semester(): courseHead(nullptr),semesterNext(nullptr),semesterPrev(nullptr){}
};


// COURSE

struct Session{
    char* dayOfWeek;
    int ordinalSession;
};

struct Course{
    char* courseID;
    char* courseName;
    char* teacherName;
    int numberOfCredits;
    int maximumNumberOfStudents;
    int numberOfStudents;
    Session session1,session2;
    Course* courseNext=nullptr;
    Course* coursePrev=nullptr;
    Course(): numberOfStudents(0),courseNext(nullptr),coursePrev(nullptr){}
};



// DATE

// input a date
void inputDate(Date& d);
// get the current date
Date currentDate();
// is the bigger day?
bool isBiggerDate(Date& d1,Date& d2);



// CREATE SEMESTER

// create a semester
void createSemester(SchoolYear*& schlY);



// CREATE A COURSE REGISTRATION SESSION

// choose a semester from school year list and create a course registration session
void createRegistrationSession_fromSchoolYearList(SchoolYearList& schlYL);
// create a registration session
void createRegistrationSession(Semester*& smt);



// LOAD COURSE LIST

// from FILE

// load a course list
void loadCourseList(Semester*& smt);
// load a course
void loadCourse(istream& fin,Course*& course);
// load a session
void loadSession(istream& fin,Session& session);

// from TERMINAL

// choose school year and semester to insert a course
void inputCourse_fromSchoolYearList(SchoolYearList& schlYL);
// input a course
void inputCourse(Course*& course);
// input a session
void inputSession(Session& session);



// DISPLAY A COURSE LIST

// choose a course list from school year list and display it
void viewCourseList_fromSchoolYearList(SchoolYearList& schlYL);
// display the course list
void viewCourseList(Course*& courseHead);
// display one course
void viewCourse(Course*& course);
// UPDATE THE INFORMATION OF A COURSE

// choose a course list from school year list and update it
void updateCourse_fromSchoolYearList(SchoolYearList& schlYL);
// update a course
void updateCourse(Course*& course);



// DELETE A COURSE

// choose a course list from school year list and delete it
void deleteCourse_fromSchoolYearList(SchoolYearList& schlYL);
// delete a course
void deleteCourse(Course*& courseHead,Course*& course);



// user chooses one course in a semester
Course* chooseCourse(Semester*& smt);
// user chooses one semester in a school year
Semester* chooseSemester(SchoolYear*& schlY);
// user chooses one school year in school year list
SchoolYear* chooseSchoolYear(SchoolYearList& schlYL);


void doSomethingWithCourse(SchoolYearList& schlYL);


#endif // _School_