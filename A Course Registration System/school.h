#ifndef _School_
#define _School_

using namespace std;

struct DateOfBirth{
    int day, month, year;
};

struct Student{
    char* firstName,* lastName,* No,* studentID,* Gender,* socialID;
    DateOfBirth birth;
    Student* pNext, *pPrev;

    Student(): pPrev(nullptr), pNext(nullptr) {}

};

struct Class{
    char* className;
    Student* studentList;  
    Class* pNext, *pPrev;

    Class(): pNext(nullptr), pPrev(nullptr) {}
};

struct SchoolYear{
    int year;
    Class* classList;   
    SchoolYear* pNext, *pPrev;

    SchoolYear() : pNext(nullptr), pPrev(nullptr) {}
    SchoolYear(SchoolYear* prev_school_year, int x) : pNext(nullptr), pPrev(prev_school_year), year(x) {}
};

#endif // _School_
