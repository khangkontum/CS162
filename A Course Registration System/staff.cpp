#include "staff.h"

using namespace std;

void displayStaffCommand(){
    cout<<"********************************************************"<<endl;
    cout<<"0. Exit."<<endl;
    cout<<"1. View list of classes."<<endl;
    cout<<"2. View list of students in a class."<<endl;
    cout<<"3. View list of courses."<<endl;
    cout<<"4. View list of students in a course."<<endl;
    cout<<"7. View command board again."<<endl;
    cout<<"********************************************************"<<endl;
}

void goStaff(User* user){
    int command;
    clearScreen();
    displayStaffCommand();
    do{
        cout<<"Input your command: ";
        cin>>command;
        switch (command){
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
        default:
            cout<<"Wrong command !"<<endl;
        }
    }while(command);
}
void viewListOfClass(){

}
void viewListOfStudentsInClass(){

}
void viewListOfCourse(){

}
void viewListOfStudentInCourse(){

}
