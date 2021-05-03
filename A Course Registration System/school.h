#define _CRT_SECURE_NO_DEPRECATE
#ifndef _School_
#define _School_
#include<iostream>
#include<fstream>
#include<string.h>
#include<string>
#include<ctime>
#include<limits>

using namespace std;

struct Class;
struct classList;
struct SchoolYear;
struct SchoolYearList;
struct Date;
struct Student;
struct User;
struct UserList;
struct Course;
struct CourseList;
struct Session;
struct RegistrationSession;
struct Semester;

struct Date{
    int day, month , year;
};
struct SchoolYearList{

    SchoolYear* schoolyearL;
    SchoolYearList():schoolyearL(nullptr){}
};
struct Student{
    string firstName, lastName, studentID, Gender, socialID;
	int No;
    Date birth;
    Student* pNext, *pPrev;
    Class* posClass;// Trace
    //CourseList* courseList;// Trace
    Student(): pPrev(nullptr), pNext(nullptr) {}

};
struct Class{
    char* className;
    //string className;
    int noStudent;
    Student* studentList;
	Student* studentLast;
    Class* pNext, *pPrev;
	SchoolYear* posSchoolYear;// Trace
    Class(): pNext(nullptr), pPrev(nullptr),studentList(nullptr),studentLast(nullptr) {}
};
struct classList {
	Class* classL;
    classList():classL(nullptr){}
};
struct User{
	string username;
    string password;
	string name;
	string phoneNumber;
	string email;
	string socialId;
	Student* posStudent;// Trace
    bool isStaff;
    User*uNext, *uPre;
    User():isStaff(false),uNext(nullptr),uPre(nullptr){}
};
struct UserList{
    User* fUser;
    UserList(): fUser(nullptr){}
};

// COURSE

struct Session{
    char* dayOfWeek;
    int ordinalSession;
};

struct Course{
    string courseID;
    int status;
    char* courseName;
    char* teacherName;
    int numberOfCredits;
    int maximumNumberOfStudents;
    int numberOfStudents;
    int totalMark, finalMark, midTermMark, otherMark, count;
    Date startDay, endDay;
    Session session1,session2;
    Course* courseNext;
    Course* coursePrev;
    Course(): numberOfStudents(0),courseNext(nullptr),coursePrev(nullptr){}
};

struct CourseList{
    string courseId;
    Course* posCourse;
    CourseList* Next;
};

// SEMESTER

struct RegistrationSession{
    Date startDate,endDate;
    RegistrationSession(){
        startDate.day=0;
        endDate.day=0;
    }
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


struct SchoolYear{
	char * year ;
  //  Class* classList = nullptr;
    SchoolYear* pNext, *pPrev;
   // Semester* semesterList = nullptr;

    Semester* semesterHead;
    SchoolYear() : pNext(nullptr), pPrev(nullptr),semesterHead(nullptr),year(nullptr){}
   // SchoolYear(SchoolYear* prev_school_year, int x,int y) : pNext(nullptr), pPrev(prev_school_year), startYear(x), endYear(y) {}


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
void addAStudentToClass(classList &classList);
Student *inputStudent();



// DATE

// input a date
void inputDate(Date& d);
// get the current date
Date currentDate();
// is the bigger day?
bool isBiggerDate(Date& d1,Date& d2);



// CREATE SEMESTER

// load a semester
void loadSemester(SchoolYear*&schlY);
// create a semester
void createSemester(SchoolYear*& schlY);
// save a semester to file
void saveSemester_toFile(Semester*&s);
// delete a semester list
void deleteSemesterList(Semester*&semesterHead);
// current Semester


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
bool loadCourse(istream& fin,Course*& course);
// load a session
void loadSession(istream& fin,Session& session);

// from TERMINAL

// choose school year and semester to insert a course
void inputCourse_fromSchoolYearList(SchoolYearList& schlYL);
// input a course
void inputCourse(Course*& course);
// input a session
void inputSession(Session& session);
// input a course list of a semester
void inputCourseList(Semester*&smt);



// DISPLAY A COURSE LIST

// choose a course list from school year list and display it
void viewCourseList_fromSchoolYearList(SchoolYearList& schlYL);
// display the course list
void viewCourseList(Course*& courseHead);
// display one course
void viewCourse(Course*& course);

// SAVE A COURSE LIST TO FILE

// save a course list to file
void saveCourseList_toFile(Course*&courseHead,string path);
// save a course to file
void saveCourse_toFile(Course*&c,ostream&fout);



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
// delete a course list
void deleteCourseList(Course*&courseHead);


// user chooses one course in a semester
Course* chooseCourse(Semester*& smt);
// user chooses one semester in a school year
Semester* chooseSemester(SchoolYear*& schlY);
// user chooses one school year in school year list
SchoolYear* chooseSchoolYear(SchoolYearList& schlYL);


void doSomethingWithCourse(SchoolYearList& schlYL);

// Trace

Course* getCourseFromCourseId(string courseId);
Student* getStudentFromUser(User* user);
Class* getClassFromUser(User* user);
SchoolYear* getSchoolYearFromUser(User* user);
int countCurrentCourse(User* user);
bool isAvailableCourse(string courseId, Course* courseList);
bool isConflictedCourse(string courseId, User* user);
bool isSameSession(Session&s1,Session&s2);
bool isConflictedSession(Course* courseA, Course* courseB);
void PressEnterToContinue();

Semester* getCurrentSemesterList();
Course* getCourseListOfUser(User* user);

int getCurrentSemester();
char* converToChar(string path);
string getCurrentPathSem();

#endif // _School_
