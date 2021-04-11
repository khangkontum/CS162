#include "school.h"

void displayCommandMenu()
{
    int option =100;
    SchoolYearList schoolYearList;
    loadSchoolYearList(schoolYearList);
	while (option != 0) {
		cout << "---------------------------------------" << endl;
		cout << "1. Create a school year." << endl;
		cout << "2. Modify School Year." << endl;
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
		}
		if(option ==2) {
			system("CLS");
			if (schoolYearList.schoolyearL == nullptr) {
				cout << "No school year was created" << endl;
				Sleep(1000);
			}
			else {
				if (schoolYearList.schoolyearL->pNext == nullptr) {
					adjustSchoolYear(schoolYearList.schoolyearL);
				}
				else {
					displaySchoolYears(schoolYearList);
					cout << "Input the year following the format (Start-End): ";
					char input[1000];
					cin.width(1000);
					cin >> input;
					while (strlen(input) != 9 && input[4] != '-') {
						cout << "Wrong format, please try again: ";
						cin.width(1000);
						cin >> input;
					}

					SchoolYear *adjust = findSchoolYear(schoolYearList, input);
					if (adjust == nullptr) {
						cout << "School year not existed, please create it first..." << endl;
						Sleep(1000);
					} else adjustSchoolYear(adjust);
				}

			}

		}
		system("CLS");
		
	}
	

}




void adjustSchoolYear(SchoolYear *&schoolYear) {
	int option = 100;
	
	while (option != 0) {
		cout << "ADJUSTMENT FOR SCHOOL YEAR " << schoolYear->year << endl;
		cout << "1. Add new class" << endl;
		cin >> option;
	}
	
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
			
			// load them class list 
			// load semester
		
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
		cout << "Input the year following the format (Start-End): ";
		char input[1000];
		cin.width(1000);
		cin >> input;
		while (strlen(input) != 9 && input[4] != '-') {
			cout << "Wrong format, please try again: ";
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
		
		string path2 = "SchoolYear\\";
		path2.append(newSchoolYear->year);
		path2 += ".csv";
		ofstream fout2;
		fout2.open(path2);
		fout2.close();

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