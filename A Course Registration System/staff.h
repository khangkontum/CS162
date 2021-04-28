#ifndef _staff_
#define _staff_

#include "login.h"
#include "student.h"

using namespace std;

void viewListOfClass();
void viewListOfStudentsInClass();
void viewListOfCourse();
void displayStaffCommand();
void goStaff(User* user);
void viewListOfStudentInCourse(ostream& fout);
void exportListofStudentInCourse();
void displayContent(string Dir);
bool isInCourse(string MSSV, string courseID);

#endif // _staff_
