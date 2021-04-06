#ifndef _School_
#define _School_

using namespace std;

struct DateOfBirth{
    int day, month, year;
};

struct Student{
    char* firstName,* lastName,* No,* studentID,* Gender,* socialID;
    DateOfBirth birth;

};

struct Class{
    char* className;
    Student* studentList;  // Dynamic array
};

struct SchoolYear{
    int year;
    Class* classList;   //Dynamic array
};

struct school{
    SchoolYear* yearList;   //Dynamic array
};

#endif // _School_
