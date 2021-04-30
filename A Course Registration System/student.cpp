#include "student.h"
#include "school.h"
#include "login.h"
#include "staff.h"

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
    if (countCurrentCourse(user)>=5){
        cout<<"You have reached the maximum number of course this semester !"<<endl;
        return;
    }
    viewListOfCourse();
    cout<<"Input course Id you want to enroll: ";
    string couId;
    cin>>couId;
    Semester* curSem = getCurrentSemesterList();
    if (isAvailableCourse(couId, curSem->courseHead)){
        if (isConflictedCourse(couId, user))
            cout<<"Course is conflicted !"<<endl;
        else{
            /// Add course
        }
    }else
        cout<<"Wrong ID !"<<endl;

}
void viewListOfEnrolledCourses(User* user){
    Course* couList = getCourseListOfUser(user);
    Course* cur = couList;
    while(cur!=nullptr){
        if (cur->status == 1)
            viewCourse(cur);
        cur = cur->courseNext;
    }
}
void removeACourseFromEnrolledList(User* user){
    viewListOfEnrolledCourses(user);

    cout<<"Input course Id you want to remove: ";
    string couId;
    cin>>couId;
    Course* couList = getCourseListOfUser(user);
    if (isAvailableCourse(couId, couList)){
        /// Remove course
    }else
        cout<<"Wrong Id !"<<endl;

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
