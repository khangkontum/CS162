#include "login.h"

using namespace std;

User createUser(Student u){
    User a;
    a.username = u.studentID;
    a.password = u.socialID;
    a.Name = u.lastName + " " + u.firstName;
    return a;
}
void displayUser(User u){
    cout<<"1. Username: "<<u.username<<endl;
    cout<<"2. Full name: "<<u.Name<<endl;
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
