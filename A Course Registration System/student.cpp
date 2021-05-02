#include "student.h"
#include "school.h"
#include "login.h"
#include "staff.h"
#include <sstream>

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
    string Dir = "Students/" + user->posStudent->studentID + ".csv";
    ifstream fin;
    fin.open(Dir);

    string line;
    cout << "Student-ID || Total mark  || Final mark || Midterm mark || Other mark\n";
    while(getline(fin, line))
    {
        stringstream lineStream(line);
        string cell;

        int i = 0;
        string* strArr = new string[10];
        while(getline(lineStream, cell, ','))
        {
            i++;
            strArr[i] = cell;
        }
        if(strArr[3] != "0")
            cout << strArr[2] << "    " << strArr[4] << "    " << strArr[5] << "    " << strArr[6] << "   " << strArr[7] << "\n";
        delete[] strArr;
    }
    fin.close();
}

void enrollInACourse(User* user){
    cout<<endl;
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
            Course* cou = getCourseFromCourseId(couId);
            ofstream fo;
            string path = "students/" + user->username + ".csv";
            cerr<<path<<endl;
            fo.open(path, ios_base::app);
            fo<<cou->courseID<<','<<cou->courseName<<','<<cou->status<<','<<"0,0,0,0,0,1"<<endl;
            fo.close();
            delete cou;
            cout<<"Enroll successful !"<<endl;
        }
    }else
        cout<<"Wrong ID !"<<endl;
    cout<<endl;

}
void viewListOfEnrolledCourses(User* user){
    cout<<endl;
    cout<<"***********List of enrolled courses***********"<<endl;
    Course* couList = getCourseListOfUser(user);
    Course* cur = couList;
    while(cur!=nullptr){
        if (cur->status == 1){
            Course* tmp = getCourseFromCourseId(cur->courseID);
            if (tmp != nullptr)
                viewCourse(tmp);
            delete tmp;
        }
        cur = cur->courseNext;
    }
    cout<<endl;
}
void removeACourseFromEnrolledList(User* user){
    viewListOfEnrolledCourses(user);

    cout<<"Input course Id you want to remove: ";
    string couId;
    cin>>couId;
    Course* couList = getCourseListOfUser(user);
    if (isAvailableCourse(couId, couList)){
        Course* cur = couList;
        while(cur != nullptr){
            if (cur->courseID == couId) break;
            cur = cur->courseNext;
        }
        if (cur != nullptr){
            if (cur == couList) couList = couList->courseNext;
            if (cur->courseNext != nullptr)
                cur->courseNext->coursePrev = cur->coursePrev;
            if (cur->coursePrev != nullptr)
                cur->coursePrev->courseNext = cur->courseNext;
            delete cur;
        }


        string path = "students/"+user->username+".csv";
        ofstream fo;
        fo.open(path);
        fo<<"ID,Name,Status,Total mark,Final mark,Midterm mark,Other mark,Time,Count"<<endl;
        while(couList != nullptr){
            fo<<couList->courseID<<','<<couList->courseName<<','<<couList->status<<','<<couList->totalMark<<
                ','<<couList->finalMark<<','<<couList->midTermMark<<','<<couList->otherMark<<','<<
                couList->startDay.day<<'/'<<couList->startDay.month<<'/'<<couList->startDay.year<<'-'<<
                couList->startDay.day<<'/'<<couList->startDay.month<<'/'<<couList->startDay.year<<','<<
                couList->count<<endl;
            couList = couList->courseNext;
        }
        fo.close();
        cout<<"Remove Sucessful !"<<endl;

    }else
        cout<<"Wrong Id !"<<endl;

}

void goStudent(User* user){
    checkStudentInfo(user);
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

void checkStudentInfo(User* user){
    ifstream fi;
    string path = "students/"+user->username+".csv";
    fi.open(path);
    bool k = !fi.is_open();
    fi.close();
    if (k){
        ofstream fo;
        fo.open(path);
        fo<<"ID,Name,Status,Total mark,Final mark,Midterm mark,Other mark,Time,Count"<<endl;
        fo.close();
    }
}
