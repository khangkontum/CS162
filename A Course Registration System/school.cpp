#include "school.h"

void displayCommandMenu()
{
    int option =100;
    SchoolYearList schoolYearList;
	classList classList;
    loadSchoolYearList(schoolYearList);
	//loadClassList(classList);
	while (option != 0) {
		cout << "---------------------------------------" << endl;
		cout << "1. Create a school year." << endl;
		cout << "2. Create new class." << endl;
		cout << "3. ......" << endl;
		cin >> option;

		if(option== 1) {
			system("CLS");
			string path = "SchoolYear\\SchoolYear.txt";
			cout << "Create a new school year:" << endl;
			createSchoolYear(schoolYearList, path);
			displaySchoolYears(schoolYearList);
			Sleep(1000);
			system("CLS");
		} else if (option == 2) {
			system("CLS");
			string path = "Class\\Classes.txt";
			cout << "Create a new class:" << endl;
			Sleep(1000);
			system("CLS");
		}
		
		system("CLS");
		
	}
	

}

void loadClassList(classList &classList) {
	ifstream fin;
	string path = "Classes\\Classes.txt";
	fin.open(path);

	if (fin.is_open()) {

		char dummy[10000];
		while (!fin.eof()) {
			fin >> dummy;
			Class *newClass = new Class;
			newClass->className = new char[strlen(dummy) + 1];
			strcpy(newClass->className, dummy);
			int noStudent = loadStudent(newClass);
			
		}
	}
	else {
		cout << "Cannot open SchoolYear.txt" << endl;
		return;
	}
	fin.close();
}
int loadStudent(Class *&cl) {
	ifstream fin;
	string path = "Classes\\";
	path.append(cl->className);
	path += ".csv";
	int noStudent = 0;
	fin.open(path);
	if (fin.is_open()) {

	}
	else return noStudent;

}



void loadSchoolYearList(SchoolYearList &schoolYearList){
    ifstream fin;
	string path = "SchoolYear\\SchoolYear.txt";
    fin.open(path);
	
    if(fin.is_open()){
	
		char dummy[10000];
		while (!fin.eof()) {
			fin >> dummy;
			SchoolYear *newSchoolYear = new SchoolYear;
			newSchoolYear->year = new char[strlen(dummy) + 1];
			strcpy(newSchoolYear->year,dummy);
			
			newSchoolYear->pNext = schoolYearList.schoolyearL;
			if (schoolYearList.schoolyearL != nullptr) schoolYearList.schoolyearL->pPrev = newSchoolYear;
			schoolYearList.schoolyearL = newSchoolYear;
		}
    } else {
        cout<<"Cannot open SchoolYear.txt" <<endl;
        return;
    }
    fin.close();
}
void createSchoolYear(SchoolYearList &schoolYearList, string path) {
	
	ofstream fout;
	fout.open(path,std::ios_base::app);
	if (fout.is_open()) {
		cout << "Input the year following the format (Start-End and End minus Start must be 1): ";
		char input[1000];
		cin.width(1000);
		cin >> input;
		
		while (!validSchoolYear(input)) {
			cout << "Input the year following the format (Start-End and End minus Start must be 1): ";
			cin.width(1000);
			cin >> input;
		}

		if (findSchoolYear(schoolYearList, input) != nullptr) {
			cout << "School year existed, no need to create more..." << endl;
			Sleep(700);
			return;
		}
		
		SchoolYear *newSchoolYear = new SchoolYear;
		newSchoolYear->year = new char[strlen(input) + 1];
		strcpy(newSchoolYear->year, input);

		newSchoolYear->pNext = schoolYearList.schoolyearL;
		if (schoolYearList.schoolyearL != nullptr) schoolYearList.schoolyearL->pPrev = newSchoolYear;
		schoolYearList.schoolyearL = newSchoolYear;
		fout << newSchoolYear->year << endl;

		/*
		string path2 = "SchoolYear\\";
		path2.append(newSchoolYear->year);
		path2 += ".csv";
		ofstream fout2;
		fout2.open(path2);
		fout2.close();
		*/
		cout << "School Year Created !!!!" << endl;
		Sleep(500);
		return;
	}
	else {
		cout << "Cannot find or open SchoolYear.txt..." << endl;
		return;
	}
	fout.close();

	
}

bool validSchoolYear(char input[]) {
	if (strlen(input) != 9 && input[4] != '-') {
		return false;
	}
	int yearlen = 4;
	char *start = new char[yearlen], *end = new char[yearlen];
	for (int i = 0; input[i] != '-'; i++) {
		int j = i + yearlen +1;
		start[i] = input[i];
		end[i] = input[j];
	}
	if (atoi(end) - atoi(start) != 1) return false;
	return true;
}


SchoolYear *findSchoolYear(SchoolYearList schoolYearList, char year[]) {
	if (schoolYearList.schoolyearL == nullptr) return nullptr;
	else {
		SchoolYear *pCur = schoolYearList.schoolyearL;
		while (pCur != nullptr) {
			if (strcmp(pCur->year, year) == 0) return pCur;
			else pCur = pCur->pNext;
		}
		return nullptr;
	}
}
void displaySchoolYears(SchoolYearList schoolYearList) {
	if (schoolYearList.schoolyearL == nullptr) return;
	cout << "List of School Years: " << endl;
	SchoolYear *cur = schoolYearList.schoolyearL;
	while (cur != nullptr) {
		cout << cur->year<< endl;
		cur = cur->pNext;
	}
}