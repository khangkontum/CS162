#include "staff.h"
#include "school.h"
#include <bits/stdc++.h>
#include <cstring>
#include <sstream>
#include <filesystem>

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
    cout<<"8. Export list of student in a course." << endl;
    cout<<"9. Import scoreboard of a course." << endl;
    cout<<"10. View scoreboard of a course." << endl;//Not finished
    cout<<"11. Update a student result." << endl;
    cout<<"12. View the scoreboard of a class." << endl; //Not finished
    cout<<"13. View command board again."<<endl;
    cout<<"14. Update user."<<endl;
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
            viewListOfStudentInCourse(cout);
            break;
        case 5:
            displayPersonalInfo(user);
            break;
        case 6:
            changePassword(user);
            break;
        case 8:
            exportListofStudentInCourse();
            break;
        case 9:
            ImportScoreboard();
            break;
        case 13:
            displayStaffCommand();
            break;
        case 14:
            updateUser(user);
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

bool isInCourse(string MSSV, string courseID, string SemesterTime)
{
    string Dir = "Students/" + MSSV + ".csv";
    string line;

    ifstream fin;
    fin.open(Dir);

    string* strArr = new string[10];
    while(getline(fin, line))
    {
        stringstream lineStream(line);
        string cell;

        int i = 0;
        while(getline(lineStream,cell, ','))
        {
            i++;
            strArr[i] = cell;
        }
        if(strArr[1] == courseID && strArr[8] == SemesterTime)
            return true;
    }
    fin.close();
    return false;
}

void exportListofStudentInCourse()
{
    ofstream fout;
    fout.open("student_list.csv");
    viewListOfStudentInCourse(fout);
    fout.close();
}

void displayContent(string Dir)
{
    ifstream fin;
    string str;
    fin.open(Dir);
    while(getline(fin, str))
    {
        cout << str << "\n";
    }
    fin.close();
}

void viewListOfCourse(){
}

void viewListOfStudentInCourse(ostream& fout){
    cout << "Choose school year.\n";
    ifstream fin;
    string Dir = "SchoolYear/SchoolYear.txt";
    fin.open(Dir);
    displayContent(Dir);
    string str;
    
    do{
        cout << "Input: ";
        string tmp;
        bool ok = false;

        cin >> str;

        fin.close();
        fin.open(Dir);

        while(getline(fin, tmp))
        {
            if(tmp == str)
            {
                ok = true;
                break;
            }
        }

        if(ok)
            break;
        else
        {
            clearScreen();
            cout <<"School year not exist. Choose again.\n";
        }   
    }while(true);

    fin.close();
    
    string c;
    do{
        clearScreen();
        cout << "Choose semester (1 - 3): ";
        cin >> c;
        if((c[0] == '1' || c[0] == '2' || c[0] == '3') && c.size() == 1)
            break;
        else{
            clearScreen();
            cout << "Wrong statement. Please input again.\n";
        }
    }while(true);

    Dir = "SchoolYear/" + str + "/Semester " + c + "/CourseList.csv";

    //Input time of chosen semester
    fin.open("SchoolYear/" + str + "/Semester " + c +"/Information.txt");
    string SemesterTime;
    getline(fin, SemesterTime);
    fin.close();

    clearScreen();
    cout << "Choose course:\n";
    displayContent(Dir);
    do{
        cout << "Input: ";
        string line;
        bool ok = false;

        cin >> str;

        fin.open(Dir);

        while(getline(fin, line))
        {
            stringstream lineStream(line);
            string cell;

            int i = 0;
            while(getline(lineStream,cell, ','))
            {
                if(cell == str)
                {
                    ok = true;
                    break;
                }
                break;
            }
        }

        if(ok)
            break;
        else
            cout <<"Course not exist. Choose again.\n";
        fin.close();
    }while(true);
    if(fin.is_open())
        fin.close();
    
    string courseID = str;

    fin.open("Students/list.txt");
    string tmp;
    while(getline(fin, tmp))
    {
        if(isInCourse(tmp, courseID, SemesterTime))
            fout << tmp << "\n";
    }
    fin.close();
}

void updateStudentResult(string* updatedResult, string courseID)
{
    ifstream fin;
    ofstream fout;
    
    string Content;
    fin.open("Students/" + updatedResult[1] + ".csv");

    string line;
    string* strArr = new string[10];
    while(getline(fin, line))
    {
        stringstream lineStream(line);
        string cell;

        int i = 0;
        while(getline(lineStream, cell, ','))
        {
            i++;
            strArr[i] = cell;
        }
        if(strArr[1] == courseID)
        {
            for (int j = 3; j <= 6; j++)
                strArr[j] = updatedResult[j];
        }

        for(int j = 1; j < i; j++)
            Content = Content + strArr[j] + ",";
        Content = Content + strArr[i] + "\n";
    }
    fin.close();

    fout.open("Students/" + updatedResult[1] + ".csv");
    fout << Content;
    fout.close();
}

//WORKING
void updateStudentResultTmp()
{
    string* strArr = new string[10];
    string courseID;
    do{
        cout << "Input student ID: ";
        cin >> strArr[1];
        ifstream fin;;
        fin.open(strArr[1] + ".csv");
        if(fin.is_open() == false)
        {
            clearScreen();
            cout << "Student ID not found. Try again.\n";
        }
        else{
            fin.close();
            break;
        }
    }while(true);
    


    do{
        cout << "Input course ID: ";
        ifstream fin;
        fin.open(strArr[1] + ".csv");

        string line;
        bool ok = false;
        while(getline(fin, line))
        {
            stringstream lineStream(line);
            string cell;

            int i = 0;
            string* tmpArr = new string[10];
            while(getline(lineStream, cell, ','))
            {
                i++;
                tmpArr[i] = cell;
            }
            if(tmpArr[1] == courseID)
            {
                ok = (tmpArr[3][0] !='0');
                break;
            }
            fin.close();
        }
        if(ok == false)
        {
            clearScreen();
            cout << "Course not found or have not enrolled yet. Try again.\n";
        }
        else
            break;
    }while(true);

    cout << "Input total mark: ";
    cin >> strArr[3];
    cout << "Input mid term mark: ";
    cin >> strArr[4];
    cout << "Input final mark: ";
    cin >> strArr[5];
    cout << "Input other mark: ";
    cin >> strArr[6];
    updateStudentResult(strArr, courseID);

}

void ImportScoreboard()
{
    clearScreen();
    string courseID;
    ifstream fin;
    do{
        cout << "Input course ID: ";
        cin >> courseID;
        fin.open(courseID + ".csv");
        if(fin.is_open() == false)
        {
            clearScreen();
            cout << "File not found. Please try again.";
        }
        else{
            break;
        }
    }while(true);
    
    //Read csv file
    string line;
    getline(fin, line);
    while(getline(fin, line))
    {
        stringstream lineStream(line);
        string cell;

        int i = 0;
        string* strArr = new string[9];
        while(getline(lineStream,cell, ','))
        {
            i++;
            strArr[i - 1] = cell;
        }
        updateStudentResult(strArr, courseID);
    }
    fin.close();
}

void viewScoreBoardClass()
{
    string className;
    
    do{
        cout << "List of classes: ";
        displayContent("Classes/Classes.txt");
        cout << "\nInput class name: ";
        cin >> className;
        
        ifstream fin;
        string tmp;
        bool ok = false;
        fin.open("Classes/Classes.txt");

        while(getline(fin, tmp))
        {
            if(tmp == className)
            {
                ok = true;
                break;
            }
        }
    }while(true);


}

void viewScoreStudent(string MSSV)
{
    ifstream fin;
    fin.open("Students/" + MSSV + ".csv");

    string line;
    string* strArr = new string[10];
    while(getline(fin, line))
    {
        stringstream lineStream(line);
        string cell;

        int i = 0;
        while(getline(lineStream,cell, ','))
        {
            i++;
            strArr[i] = cell;
        }
        if(strArr[3][0] != '0')
            cout << MSSV << " " << strArr[2] << " " << strArr[5] << "\n";
    }
}