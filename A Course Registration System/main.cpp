#include "school.h"
#include "login.h"

using namespace std;

int main(){
    User* user;
    do{
        login(user);
    }while(user!=nullptr);

    if (user.isStaff)
        goStaff();
    else
        goStudent();

    return 0;
}
