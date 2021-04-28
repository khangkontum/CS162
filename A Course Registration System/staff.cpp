#include "staff.h"
#include <cstring>
#include <sstream>

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
    cout<<"7. View list of student in a course." << endl;
    cout<<"8. Export list of student in a course." << endl; //Not finished
    cout<<"9. Import scoreboard of a course." << endl;//Not finished
    cout<<"10. View scoreboard of a course." << endl;//Not finished
    cout<<"11. Update a student result." << endl; //Not finished
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
            viewListOfStudentInCourse();
            break;
        case 5:
            displayPersonalInfo(user);
            break;
        case 6:
            changePassword(user);
            break;
        case 7:
            viewListOfStudentInCourse(cout);
            break;
        case 8:
            exportListofStudentInCourse();
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

//Working
bool isInCourse(istream& str)
{
    string line;
    getline(str,line);

    stringstream lineStream(line);
    string cell;

    int i = 0;
    while(getline(lineStream,cell, ','))
    {
        i++;
        if(i == 3){

        }
    }
}

void exportListofStudentInCourse()
{
    ofstream fout;
    fout.open("student_list.csv");
    viewListOfStudentInCourse(fout);
    fout.close();
}

void displaySchoolYear()
{

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

//Working
void viewListOfStudentInCourse(ostream& fout){
    cout << "Choose school year.\n";
    ifstream fin;
    string Dir = "SchoolYear/SchoolYear.txt";
    fin.open(Dir);
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
            cout <<"School year not exist. Choose again.";
        }   
    }while(true);
    
    string c;
    do{
        cout << "Choose semester (1 - 3):";
        cin >> c;
        if((c[0] == '1' || c[0] == '2' || c[0] == '3') && c.size() == 1)
            break;
        else{
            clearScreen();
            cout << "Wrong statement. Please input again.";
        }
    }while(true);

    Dir = "SchoolYear/" + str + "/Semester " + c + "/CourseList.csv";

    cout << "Choose course";
    displayContent(Dir);
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
            cout <<"Course not exist. Choose again.";
    }while(true);

}