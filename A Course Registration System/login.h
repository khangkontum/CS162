#ifndef _login_
#define _login_
#include "school.h"

using namespace std;

User createUser(Student u);
void displayUser(User u);
void updateUser(User &u);
User findUser(string username, string password);


#endif // _login_
