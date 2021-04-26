#include "staff.h"
#include <cstring>

using namespace std;

void displayStaffCommand(){
    cout<<endl;
    cout<<"********************************************************"<<endl;
    cout<<"0. Exit."<<endl;
    cout<<"1. View list of classes."<<endl;
    cout<<"2. View list of students in a class."<<endl;
    cout<<"3. View list of courses."<<endl;
    cout<<"4. View list of students in a course."<<endl;
    cout<<"5. view personal information."<<endl;
    cout<<"6. Change password."<<endl;
    cout<<"7. View command board again."<<endl;
    cout<<"********************************************************"<<endl;
    cout<<endl;
}

void goStaff(User* user){
    int command;
    clearScreen();
    displayStaffCommand();
    do{
        cout<<"Input your command: ";
        cin>>command;
        switch (command){
        case 0:
            break;
        case 1:
            viewListOfClass();
            break;
        case 2:
            viewListOfStudentsInClass();
            break;
        case 3:
            viewListOfCourse();
            break;
        case 4:
            viewListOfStudentInCourse();
            break;
        case 5:
            displayPersonalInfo(user);
            break;
        case 6:
            changePassword(user);
            break;
        case 7:
            displayStaffCommand();
            break;
        default:
            cout<<"Wrong command !"<<endl;
        }
    }while(command);
}
void viewListOfClass(){
    classList cList;
    loadClassList(cList);
    displayClasses(cList);
}
void viewListOfStudentsInClass(){
    cout<<"Input the name of class: ";
    char* cName = new char[1000];
    cin>>cName;
    char* className = new char[strlen(cName) + 1];
    strcpy(className, cName);
    className[strlen(cName)] = '\000';
    delete[] cName;
    classList cList;
    loadClassList(cList);
    Class* classL = cList.classL;
    while(classL != nullptr){
        if (strcmp(classL->className, className) == 0)
            break;
        classL = classL->pNext;
    }
    if (classL == nullptr){
        cout<<"Wrong class name !"<<endl;
    }else{
        displayStudent(classL);
    }
}
void viewListOfCourse(){

}
void viewListOfStudentInCourse(){

}
