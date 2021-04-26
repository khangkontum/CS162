#include "login.h"
#include "school.h"
#include "fstream"
#include "global.h"
#ifdef _WIN64
#include <windows.h>
#endif

using namespace std;


void clearScreen(){

	for(int i = 1; i <= 10; i++)
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    //system("clear");
}

User createUser(Student u){
    User a;
    a.username = u.studentID;
    a.password = "1";
    a.name = u.lastName + " " + u.firstName;
    return a;
}
void displayUser(User u){
    cout<<endl;
    cout<<"1. Username: "<<u.username<<endl;
    cout<<"2. Full name: "<<u.name<<endl;
    cout<<"3. Password: "<<u.password<<endl;
    cout<<"4. Mail: "<<u.email<<endl;
    cout<<"5. Phone: "<<u.phoneNumber<<endl;
    cout<<endl;
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
    int isStaff;
    fi.open("user/user.txt");
    fi>>n;
    for(int i=0;i<n;++i){
        fi>>username;
        fi>>password;
        fi.ignore();
        getline(fi,name);
        fi>>phonenumber;
        fi>>email;
        fi>>socialId;
        fi>>isStaff;

        User* tmp = new User;

        tmp->username = username;
        tmp->password = password;
        tmp->name = name;
        tmp->phoneNumber = phonenumber;
        tmp->email = email;
        tmp->socialId = socialId;
        tmp->isStaff = isStaff;

        tmp->uNext = uList;
        uList = tmp;
    }
    fi.close();
    return uList;
}

User* findUser(string username){
    User* cur = uList.fUser;
    while(cur!=nullptr){
        if (cur->username == username)
            break;
        cur = cur->uNext;
    }
    return cur;
}

void displayPersonalInfo(User* user){
    cout<<endl;
    cout<<"******Info*******"<<endl;
    cout<<"Username: "<<user->username<<endl;
    cout<<"Password: "<<user->password<<endl;
    cout<<"Email: "<<user->email<<endl;
    cout<<"Name: "<<user->name<<endl;
    cout<<"Social Id: "<<user->socialId<<endl;
    cout<<"Phone: "<<user->phoneNumber<<endl;
    cout<<endl;
}

void changePassword(User* user){
    cout<<endl;
    cout<<"******Change Password******"<<endl;
    string u, v;
    cout<<"Input your new password: ";
    cin>>u;
    cout<<"Input your new password again: ";
    cin>>v;
    if (u == v){
        user->password = u;
        saveUserList();
        cout<<"Change successfully !"<<endl;
    }else{
        cout<<"Wrong !"<<endl;
    }
    cout<<endl;
}

void loadUserList(){
    uList.fUser = getUserList();
}
void saveUserList(){
    ofstream fo;
    fo.open("user/user.txt");
    int n = 0;
    User* cur = uList.fUser;
    while(cur!=nullptr){
        ++n;
        cur = cur->uNext;
    }
    fo<<n<<endl;
    cur = uList.fUser;
    while(cur!=nullptr){
        fo<<cur->username<<endl;
        fo<<cur->password<<endl;
        fo<<cur->name<<endl;
        fo<<cur->phoneNumber<<endl;
        fo<<cur->email<<endl;
        fo<<cur->socialId<<endl;
        fo<<cur->isStaff<<endl;
        cur = cur->uNext;
    }
    fo.close();
}
