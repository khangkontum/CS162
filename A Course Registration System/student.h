#ifndef _Student_
#define _Student_

#include "school.h"
#include "login.h"

using namespace std;

void displayStudentCommand();
void enrollInACourse(User* user);
void viewListOfEnrolledCourses(User* user);
void removeACourseFromEnrolledList(User* user);
void viewScoreBoard(User* user);
void goStudent(User* user);
void checkStudentInfo(User* user);


#endif // _Student_
