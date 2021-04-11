#define _CRT_SECURE_NO_DEPRECATE
#ifndef _School_
#define _School_
#include<iostream>
#include <fstream>
#include<string.h>
#include<string>
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

    Student(): pPrev(nullptr), pNext(nullptr) {}

};
// struct Day{
//     Day *nextDay, *preDay;
// 	char* dayName;
// 	char* mor1;
// 	char* mor2;
// 	char* aft1;
// 	char* aft2;
// };
// struct Schedule{
//     Day *dateList;
//     char* className;
//      Schedule(): dateList(nullptr) {}
// };
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
// struct Score{
//     char* name;
//     char * studentID;
// 	float mid, fnal, lb, bnus;
// 	Score*nextScore= nullptr, *preScore = nullptr;
// };
// struct ScoreList{
//     Score *fScore = nullptr;

// };
// struct Course{
//     char *courseId;
//     char * courseName;
//     char* lecturer;
//     int noStudent;
//     int noCredits;
//     int dayOfWeek;
//     Course* courseNext, *coursePre;
//     ScoreList scoreList;
// };
// struct Semester{
//     char * start;
//     char * end;
//     int no;
//     Course * courseList;
//     Semester *nextSem,*preSem;
// };
struct SchoolYear{
	char * year = nullptr;
  //  Class* classList = nullptr;   
    SchoolYear* pNext, *pPrev;
   // Semester* semesterList = nullptr;
    SchoolYear() : pNext(nullptr), pPrev(nullptr) {}
   // SchoolYear(SchoolYear* prev_school_year, int x,int y) : pNext(nullptr), pPrev(prev_school_year), startYear(x), endYear(y) {}
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


#endif // _School_