#include "login.h"
#include "school.h"
#include "fstream"
#include <time.h>
#include "global.h"
#ifdef _WIN64
#include <windows.h>
#endif


using namespace std;


void clearScreen(){
    /*
	for(int i = 1; i <= 10; i++)
		cout << "\n\n\n\n\n";
    */
    cout<<endl;
    cout<<endl;
    cout<<endl;
    //system("clear");
}

void createUser(Student* u){
    User* a = new User;
    a->username = u->studentID;
    a->password = "1";
    a->name = u->lastName + " " + u->firstName;
    a->email = "*";
    a->phoneNumber = "*";
    a->socialId = "*";
    a->isStaff = false;
    a->posStudent = u;
    a->uPre = nullptr;
    a->uNext = uList.fUser;
    if (uList.fUser != nullptr)
        uList.fUser->uPre = a;
    uList.fUser = a;
    saveUserList();
}
void displayUser(User* u){
    cout<<endl;
    cout<<"1. Mail: "<<u->email<<endl;
    cout<<"2. Phone: "<<u->phoneNumber<<endl;
    cout<<"3. Social Id: "<<u->socialId<<endl;
    cout<<endl;
}
void updateUser(User* u){
    cout<<endl;
    displayUser(u);
    cout<<"0. Exit"<<endl;
    cout<<"Input the code you want to update: ";
    int w;
    cin>>w;
    string v;
    switch (w){
    case 0:
        break;
    case 1:
        cout<<"Input your Mail: ";
        cin.ignore();
        getline(cin, v);
        u->name = v;
        break;
    case 2:
        cout<<"Input your Phone: ";
        cin.ignore();
        getline(cin, v);
        u->phoneNumber = v;
        break;
    case 3:
        cout<<"Input your Social ID: ";
        cin.ignore();
        getline(cin, v);
        u->socialId = v;
        break;
    default:
        cout<<"Wrong !"<<endl;
    }
    cout<<"Done !!!"<<endl;
    cout<<endl;
    saveUserList();
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
    if (user->isStaff == false && user->posStudent == nullptr)
        user->posStudent = getStudentFromUser(user);
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
        tmp->posStudent = nullptr;

        tmp->uNext = uList;
        tmp->uPre = nullptr;
        if  (uList != nullptr)
            uList->uPre = tmp;
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

Date getCurrentTime(){
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    Date cur;
    cur.day = aTime->tm_mday;
    cur.month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
    cur.year = aTime->tm_year + 1900; // Year is # years since 1900
    return cur;
}

int readCommand(){
    string s;
    cin>>s;
    int u = 0;
    for (int i=0, ii = s.size(); i<ii; ++i)
    if (s[i] >= '0' && s[i] <= '9')
        u = u*10 + s[i]-'0';
    else
        return -1;
    return u;
}
