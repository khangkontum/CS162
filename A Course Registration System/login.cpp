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
    a.userName = u.studentID;
    a.passWord = u.socialID;
    a.name = u.lastName + " " + u.firstName;
    return a;
}
void displayUser(User u){
    cout<<"1. Username: "<<u.userName<<endl;
    cout<<"2. Full name: "<<u.name<<endl;
    cout<<"3. Password: "<<u.passWord<<endl;
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
    string userName, passWord;
    cout<<"Username: ";cin>>userName;
    cout<<"Password: ";cin>>passWord;
    User* tmp = findUser(userName);
    if (tmp == nullptr){
        clearScreen();
        cout<<"Wrong username !"<<endl;
        return;
    }
    if (tmp->passWord != passWord){
        clearScreen();
        cout<<"Wrong password !"<<endl;
        return;
    }
    user = tmp;
}

User* findUser(string username){

}

void displayPersonalInfo(User* user){

}

void changePassword(User* user){

}
