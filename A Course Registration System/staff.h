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
void viewScoreStudent(string MSSV);
void viewScoreBoardClass();
void ImportScoreboard();
void viewScoreBoardCourse();
void updateStudentResultTmp();
void createASchoolYear();
void createASemester();
void addACourseToCurSem();
void getSemester(istream& fin, string& SemesterTime);


#endif // _staff_
