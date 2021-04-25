#include "login.h"
#include "school.h"
#include "fstream"
#ifdef _WIN64
#include <windows.h>
#endif

using namespace std;

User* copyUser(User* u){
    if (u == nullptr)
        return nullptr;
    User* v = new User;
    v->email = u->email;
    v->name = v->name;
    v->username = u->username;
    v->isStaff = u->isStaff;
    v->password = u->password;
    v->phoneNumber = u->phoneNumber;
    v->posStudent = u->posStudent;
    v->uNext = v->uPre = nullptr;
    return v;
}

void clearScreen(){

	for(int i = 1; i <= 10; i++)
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    //system("clear");
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

void login(User*& user){
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
    User* uList = nullptr;
    ifstream fi;
    int n;
    string username, password, name, phonenumber, email, socialId;
    fi.open("user/staff.txt");
    fi>>n;
    for(int i=0;i<n;++i){
        fi>>username;
        fi>>password;
        fi.ignore();
        getline(fi,name);
        fi>>phonenumber;
        fi>>email;
        fi>>socialId;

        User* tmp = new User;

        tmp->username = username;
        tmp->password = password;
        tmp->name = name;
        tmp->phoneNumber = phonenumber;
        tmp->email = email;
        tmp->socialId = socialId;

        tmp->uNext = uList;
        tmp->isStaff = true;
        uList = tmp;
    }
    fi.close();
    fi.open("user/student.txt");
    fi>>n;
    for(int i=0;i<n;++i){
        fi>>username;
        fi>>password;
        fi.ignore();
        getline(fi,name);
        fi>>phonenumber;
        fi>>email;
        fi>>socialId;

        User* tmp = new User;

        tmp->username = username;
        tmp->password = password;
        tmp->name = name;
        tmp->phoneNumber = phonenumber;
        tmp->email = email;
        tmp->socialId = socialId;

        tmp->uNext = uList;
        tmp->isStaff = false;
        uList = tmp;
    }
    fi.close();
    return uList;
}

User* findUser(string username){
    User* UserList = getUserList();
    User* cur = UserList;
    while(cur != nullptr){
        if (cur->username == username)
            break;
        cur = cur->uNext;
    }
    cur = copyUser(cur);
    while(UserList != nullptr){
        User* tmp = UserList->uNext;
        delete UserList;
        UserList = tmp;
    }
    return cur;
}

void displayPersonalInfo(User* user){

}

void changePassword(User* user){

}
