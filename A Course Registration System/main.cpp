#include "school.h"
#include "login.h"
#include "student.h"
#include "staff.h"

using namespace std;

int main(){
    User* user = nullptr;
    do{
        login(user);
    }while(user==nullptr);

    if (user->isStaff)
        goStaff(user);
    else
        goStudent(user);

    return 0;
}
