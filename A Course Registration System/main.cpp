#include "school.h"
#include "login.h"
#include "student.h"
#include "staff.h"

using namespace std;

int main(){
    SchoolYearList schoolYearList;
    loadSchoolYearList(schoolYearList);
    
    SchoolYear*schoolYear=schoolYearList.schoolyearL;
    while(schoolYear){
        loadSemester(schoolYear);
        schoolYear=schoolYear->pNext;
    }
    classList classList;
    loadClassList(classList);
    
    loadUserList();

    User* user = nullptr;
    do{
        user = nullptr;
        clearScreen();
        do{
            login(user);
        }while(user==nullptr);

        if (user->isStaff)
            goStaff(user);
        else
            goStudent(user);
    }while(true);

    return 0;
}
