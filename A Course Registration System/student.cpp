#include "student.h"
#include "school.h"
#include "login.h"

using namespace std;

void displayStudentCommand(){
    cout<<endl;
    cout<<"********************************************************"<<endl;
    cout<<"0. Exit."<<endl;
    cout<<"1. View personal information."<<endl;
    cout<<"2. Change password."<<endl;
    cout<<"3. View list of enrolled courses."<<endl;
    cout<<"4. Remove a course from the enrolled list."<<endl;
    cout<<"5. View scoreboard."<<endl;
    cout<<"6. Enroll in a course."<<endl;
    cout<<"7. View command board again."<<endl;
    cout<<"8. Update user."<<endl;
    cout<<"********************************************************"<<endl;
    cout<<endl;
}
void viewScoreBoard(User* user){

}

void enrollInACourse(User* user){


}
void viewListOfEnrolledCourses(User* user){

}
void removeACourseFromEnrolledList(User* user){


}

void goStudent(User* user){
    int command;
    clearScreen();
    displayStudentCommand();
    do{
        cout<<"Input your command: ";
        cin>>command;
        switch (command){
        case 0:
            break;
        case 1:
            displayPersonalInfo(user);
            break;
        case 2:
            changePassword(user);
            break;
        case 3:
            viewListOfEnrolledCourses(user);
            break;
        case 4:
            removeACourseFromEnrolledList(user);
            break;
        case 5:
            viewScoreBoard(user);
            break;
        case 6:
            enrollInACourse(user);
            break;
        case 7:
            displayStudentCommand();
            break;
        case 8:
            updateUser(user);
            break;
        default:
            cout<<"Wrong command !"<<endl;
        }
    }while(command);
}
