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
    cout<<"********************************************************"<<endl;
    cout<<endl;
}
void viewScoreBoard(User* user){

}

void enrollInACourse(User* user){
    if (countCurrentCourse(user)>=5){
        cout<<"You can't enroll more than 5 course at this semester"<<endl;
        return;
    }

    //Show course board
    Course* courseList = getSchoolYearFromUser(user)->semesterHead->courseHead;
    viewCourseList(courseList);

    cout<<"Input Id of a course you want to enroll: ";
    string courseId;
    cin>>courseId;
    if (isAvailableCourse(courseId, courseList)){
        if (!isConflictedCourse(courseId, user)){
            CourseList* newCourse = new CourseList;
            newCourse->courseId = courseId;
            newCourse->posCourse = getCourseFromCourseId(courseId, courseList);
            newCourse->Next = user->posStudent->courseList;
            user->posStudent->courseList = newCourse;
            cout<<"Enroll successful !"<<endl;
        }else
        cout<<"This course is conflicted with existing enrolled course sessions !"<<endl;
    }else cout<<"Wrong ID !"<<endl;
}
void viewListOfEnrolledCourses(User* user){
    CourseList* courList = user->posStudent->courseList;
    while(courList!=nullptr){
        viewCourse(courList->posCourse);
        courList = courList->Next;
    }
}
void removeACourseFromEnrolledList(User* user){
    //show enrolled list
    viewListOfEnrolledCourses(user);

    string courId;
    cout<<"Input Id of a course you want to remove: ";
    cin>>courId;
    CourseList*& courList = user->posStudent->courseList;
    if (courList!=nullptr){
        if (courList->courseId == courId){
            CourseList* tmp = courList;
            courList = courList->Next;
            delete tmp;
        }
        while(courList->Next != nullptr && courList->Next->courseId != courId)
            courList = courList->Next;
        if (courList->Next != nullptr){
            CourseList* tmp = courList->Next;
            courList->Next = courList->Next->Next;
            delete tmp;
        }
    }
    cout<<"Remove successful !"<<endl;
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
        default:
            cout<<"Wrong command !"<<endl;
        }
    }while(command);
}
