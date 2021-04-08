#ifndef _School_
#define _School_

using namespace std;
struct User{
    char * password;
    char * username;
    char * Name;
    char * phoneNumber;
     char * email;
    int flag =0 ;
    User*uNext, *uPre;
};
struct UserList{
    User* fUser;
    UserList(): fUser(nullptr){}
};
struct DateOfBirth{
    int day, month, year;
};

struct Student{
    char* firstName,* lastName,* No,* studentID,* Gender,* socialID;
    DateOfBirth birth;
    Student* pNext, *pPrev;

    Student(): pPrev(nullptr), pNext(nullptr) {}

};
struct Day{
    Day *nextDay, *preDay;
	char* dayName;
	char* mor1;
	char* mor2;
	char* aft1;
	char* aft2;
};
struct Schedule{
    Day *dateList;
    char* className;
     Schedule(): dateList(nullptr) {}
};
struct Class{
    char* className;
    int noStudent;
    Student* studentList;  
    Class* pNext, *pPrev;
    Class(): pNext(nullptr), pPrev(nullptr) {}
};
struct Score{
    char* name;
    char * studentID;
	float mid, fnal, lb, bnus;
	Score*nextScore= nullptr, *preScore = nullptr;
};
struct ScoreList{
    Score *fScore = nullptr;

};
struct Course{
    char *courseId;
    char * courseName;
    char* lecturer;
    int noStudent;
    int noCredits;
    int dayOfWeek;
    Course* courseNext, *coursePre;
    ScoreList scoreList;
};
struct Semester{
    char * start;
    char * end;
    int no;
    Semester *nextSem,*preSem;
};
struct SchoolYear{
    int year;
    Class* classList;   
    SchoolYear* pNext, *pPrev;
    Semester* semesterList = nullptr;
    SchoolYear() : pNext(nullptr), pPrev(nullptr) {}
    SchoolYear(SchoolYear* prev_school_year, int x) : pNext(nullptr), pPrev(prev_school_year), year(x) {}
};

#endif // _School_
