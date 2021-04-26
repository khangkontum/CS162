#include "school.h"
#include "login.h"
#include "student.h"
#include "staff.h"

using namespace std;

int main(){

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
