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
    cout<<"10. View scoreboard of a course." << endl;
    cout<<"11. Update a student result." << endl;
    cout<<"12. View the scoreboard of a class." << endl; //Not finished
    cout<<"13. View command board again."<<endl;
    cout<<"14. Update user."<<endl;
    cout<<"15. Add a course to current semester."<<endl;
    cout<<"16. Create a school year."<<endl;
    cout<<"17. Create a semester."<<endl;
	cout<<"18. Create a new class." << endl;
	cout<<"19. Import students from csv file to a class." << endl;
	cout<<"20. Add a Student to a Class" << endl;
    cout<<"********************************************************"<<endl;
    cout<<endl;
}

void goStaff(User* user){
    SchoolYearList schoolYearList;
	classList classList;
	loadSchoolYearList(schoolYearList);
	loadClassList(classList);
    int command;
    clearScreen();
    displayStaffCommand();
    do{
        cout<<"Input your command: ";
        cin.ignore();
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
        case 10:
            viewScoreBoardCourse();
            break;
        case 11:
            updateStudentResultTmp();
            break;
        case 12:
            viewScoreBoardClass();
            break;
        case 13:
            displayStaffCommand();
            break;
        case 14:
            updateUser(user);
            break;
        case 15:
            addACourseToCurSem();
            break;
        case 16:
            createASchoolYear();
            break;
        case 17:
            createASemester();
            break;
        case 18:{
            clearScreen();
			string path = "Classes/Classes.txt";
			cout << "Create a new class:" << endl;
			createClasses(classList, path);
			PressEnterToContinue();
            break;
        }
        case 19:{
           	addAStudentToClass(classList);
			PressEnterToContinue();
            break;
        }
         case 20:{
             addStudentsToClass(classList);
			PressEnterToContinue();
            break;
        }
        default:
            cout<<"Wrong command !"<<endl;
        }
    }while(command);
}
void viewListOfClass(){
    classList cList;
    loadClassList(cList);
    displayClasses(cList);
	deleteClassList(cList);
}
void viewListOfStudentsInClass(){
    cout<<endl;
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
	deleteClassList(cList);
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
    SchoolYearList schYearList;
    loadSchoolYearList(schYearList);
    Semester* sem = new Semester;
    sem->ordinalSemester = getCurrentSemester();
    sem->schoolYear = schYearList.schoolyearL->year;
    sem->courseHead = nullptr;
    loadCourseList(sem);
    viewCourseList(sem->courseHead);

    delete sem;
	deleteSchoolYearList(schYearList);
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
            //clearScreen();
            cout<<endl;
            cout <<"School year not exist. Choose again.\n";
            cout<<endl;
        }
    }while(true);

    fin.close();

    string c;
    do{
        //clearScreen();
        cout<<endl;
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

    //clearScreen();
    cout<<endl;
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

double calGPAoverAll(string MSSV)
{
    double sum = 0;
    double count = 0;
    ifstream fin;
    fin.open("Students/" + MSSV + ".csv");
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
        if(strArr[3] != "0")
        {
            sum += atof(strArr[5].c_str());
            count += 1;
        }
    }
    delete[] strArr;
    if(count == double(0))
        return 0;
    else
        return (sum / count);
}

bool getMSSV(istream& fin, string& MSSV)
{
    string line;
    getline(fin, line);

    string cell;
    stringstream lineStream(line);
    string* strArr = new string[10];
    int i = 0;
    while(getline(lineStream, cell, ','))
    {
        i++;
        strArr[i] = cell;
    }
    if(strArr[1] == "" || strArr[1] == "\n")
        return false;
    else{
        MSSV = strArr[3];
        return true;
    }
}

void viewScoreBoardClass()
{
    string className;
    string SemesterTime;

    cout << "List of classes: ";
    displayContent("Classes/Classes.txt");
    do{
        cout << "\nInput class name: ";
        cin >> className;
        ifstream fin;
        fin.open("Classes/" + className + ".csv");
        if(fin.is_open() == false)
        {
            clearScreen();
            cout << "Class not found. Try again.\n";
        }
        else
        {
            fin.close();
            break;
        }
    }while(true);

    //input semester time
    string tmp;
    ifstream fin;
    fin.open("SchoolYear/SchoolYear.txt");
    while(getline(fin, tmp)) {}
    fin.close();
    string Dir = "SchoolYear/" + tmp + "/Semester ";

    int i = 0;
    do{
        i++;
        fin.open(Dir + to_string(i) + "/Information.txt");
        if(fin.is_open() == true);
            break;
    }while(true);
    getline(fin, SemesterTime);
    fin.close();

    //display score
    fin.open("Classes/" + className + ".csv");
    string MSSV;
    while(getMSSV(fin, MSSV))
    {
        Dir = "Students/" + MSSV + ".csv";
        ifstream fin2;
        fin2.open(Dir);
        if(fin2.is_open() == false)
            continue;

        bool ok = true;
        string line, cell;
        string* strArr = new string[10];

        double sum = 0;
        double count = 0;

        while(getline(fin2, line))
        {
            stringstream lineStream(line);
            int i = 0;
            while(getline(lineStream, cell, ','))
            {
                i++;
                strArr[i] = cell;
            }
            if(strArr[8] == SemesterTime)
            {
                if(ok == true)
                {
                    cout << "STUDENT-ID  ||  COURSE-NAME  ||  FINAL-MARK\n";
                    ok = false;
                }
                cout << MSSV << " " << strArr[2] << " " << strArr[5] << "\n";

                count += 1;
                sum += atof(strArr[5].c_str());
            }
        }
        fin2.close();
        delete[] strArr;

        cout << "STUDENT_ID  ||  GPA_this_semester  ||  GPA_overall\n";
        cout << MSSV << " "  << (count == double(0) ? 0 : sum/count) << " " << calGPAoverAll(MSSV) << "\n";

    }
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

void viewScoreBoardCourse()
{
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
            //clearScreen();
            cout<<endl;
            cout <<"School year not exist. Choose again.\n";
            cout<<endl;
        }
    }while(true);

    fin.close();

    string c;
    do{
        //clearScreen();
        cout<<endl;
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

    //clearScreen();
    cout<<endl;
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
    string MSSV;
    while(getline(fin, MSSV))
    {
        string Dir = "Students/" + MSSV + ".csv";
        string line;

        ifstream ffin;
        ffin.open(Dir);

        string* strArr = new string[10];
        while(getline(ffin, line))
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
            {
                cout << MSSV << " ";
                for(int j = 4; j <= 7; j++)
                    cout << strArr[j] << " ";
                cout << "\n";
            }
        }
        ffin.close();
    }
    fin.close();
}

void createASchoolYear(){
    SchoolYearList schYearList;
    createSchoolYear(schYearList, "SchoolYear/SchoolYear.txt");
}

void createASemester(){
    SchoolYearList schYearList;
    loadSchoolYearList(schYearList);
    /*
    while(schYearList.schoolyearL->pNext != nullptr)
        schYearList.schoolyearL = schYearList.schoolyearL->pNext;
    */
    cout<<"Current year: "<<schYearList.schoolyearL->year<<endl;
    string path="SchoolYear/"+string(schYearList.schoolyearL->year)+"/currentSemester.txt";
    int curSem;
    ifstream fi;
    fi.open(path);
    fi>>curSem;
    fi.close();

    curSem+=1;

    Semester* sem = new Semester;

    cout<<"New semester: "<<curSem<<endl;
    cout<<"Input start day (dd mm yyyy): ";
    cin >> sem->startDate.day >> sem->startDate.month >> sem->startDate.year;
    cout<<"Input end day (dd mm yyyy): ";
    cin >> sem->endDate.day >> sem->endDate.month >> sem->endDate.year;


    sem->ordinalSemester = curSem;
    sem->schoolYear = schYearList.schoolyearL->year;
    sem->courseHead = nullptr;

    saveSemester_toFile(sem);

    ofstream fo;
    path="SchoolYear/"+string(schYearList.schoolyearL->year)+"/currentSemester.txt";
    fo.open(path);
    fo<<curSem;
    fo.close();

    path="SchoolYear/"+string(schYearList.schoolyearL->year)+"/semesterList.txt";
    fo.open(path, ios_base::app);
    fo<<curSem<<endl;
    fo.close();
}

void addACourseToCurSem(){
    int curSem = getCurrentSemester();
    Course* cou = new Course;
    string tmp;
    cout<<"Course Id: ";cin>>cou->courseID;cin.ignore();
    cout<<"Course name: ";getline(cin,tmp);cou->courseName = converToChar(tmp);
    cout<<"Teacher name: ";getline(cin,tmp);cou->teacherName = converToChar(tmp);
    cout<<"Number Of Credits: ";cin>>cou->numberOfCredits;
    cout<<"Maximum number of student: ";cin>>cou->maximumNumberOfStudents;
    cout<<"Number of student: ";cin>>cou->numberOfStudents;cin.ignore();
    cout<<"Session 1 day of week: ";getline(cin,tmp);cou->session1.dayOfWeek = converToChar(tmp);
    cout<<"Session 1 ordinal session: ";cin>>cou->session1.ordinalSession;cin.ignore();
    cout<<"Session 2 day of week: ";getline(cin,tmp);cou->session2.dayOfWeek = converToChar(tmp);
    cout<<"Session 2 ordinal session: ";cin>>cou->session2.ordinalSession;

    ofstream fo;
    string path = getCurrentPathSem() + "/courseList.csv";
    cerr<<path<<endl;
    fo.open(path, ios_base::app);
    saveCourse_toFile(cou, fo);
    fo.close();
}
