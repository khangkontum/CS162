#include "login.h"
#include "school.h"

using namespace std;

void clearScreen()
{
	for(int i = 1; i <= 10; i++)
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

User createUser(Student u){
    User a;
    a.username = u.studentID;
    a.password = u.socialID;
    a.name = u.lastName + " " + u.firstName;
    return a;
}
void displayUser(User u){
    cout<<"1. Username: "<<u.username<<endl;
    cout<<"2. Full name: "<<u.name<<endl;
    cout<<"3. Password: "<<u.password<<endl;
    cout<<"4. Mail: "<<u.email<<endl;
    cout<<"5. Phone: "<<u.phoneNumber<<endl;
}
void updateUser(User &u){
    displayUser(u);
    cout<<"Input the code you to update: ";
    int w;
    cin>>w;
    switch (w){
    default :
        cout<<"Can't change";
    }
}

void login(User* user){
    user = nullptr;
    cout<<"****LOGIN****"<<endl;
    string username, password;
    cout<<"Username: ";cin>>username;
    cout<<"Password: ";cin>>password;
    User* tmp = findUser(username);
    if (tmp == nullptr){
        clearScreen();
        cout<<"Wrong username !"<<endl;
        return;
    }
    if (tmp->password != password){
        clearScreen();
        cout<<"Wrong password !"<<endl;
        return;
    }
    user = tmp;
}

User* getUserList(){
    return nullptr;
}

User* findUser(string username){
    User* UserList = getUserList();
    while(UserList != nullptr){
        if (UserList->username == username)
            break;
        UserList = UserList->uNext;
    }
    return UserList;
}

void displayPersonalInfo(User* user){

}

void changePassword(User* user){

}
