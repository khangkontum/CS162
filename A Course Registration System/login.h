#ifndef _login_
#define _login_
#include "school.h"
#include "student.h"

using namespace std;

void loadUserList();
void saveUserList();
User* getUserList();
void createUser(Student* u);
void displayUser(User u);
void updateUser(User* u);
User* findUser(string username);
void login(User*& user);
void changePassword(User* user);
void clearScreen();
void displayPersonalInfo(User* user);
Date getCurrentTime();
int readCommand();


#endif // _login_
