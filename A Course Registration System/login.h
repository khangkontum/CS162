#ifndef _login_
#define _login_
#include "school.h"
#include "student.h"

using namespace std;

User* getUserList();
User createUser(Student u);
void displayUser(User u);
void updateUser(User &u);
User* findUser(string username);
void login(User* user);
void changePassword(User* user);
void clearScreen();
void displayPersonalInfo(User* user);


#endif // _login_
