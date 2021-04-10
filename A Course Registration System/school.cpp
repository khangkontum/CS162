#include "school.h"

void displayCommandMenu()
{
    int option =0;
	cout << "---------------------------------------" << endl;
    cout << "1. Create a school year." << endl;
    cout << "2. Create classes." <<endl;
    SchoolYearList schoolYearList;
    loadSchoolYearList(schoolYearList);
    cin >> option;
	system("CLS");
	switch (option) {
	case 1: {
		string path = "SchoolYear\\SchoolYear.csv";
		cout << "Create a new school year:" << endl;
		createSchoolYear(schoolYearList, path);
		displaySchoolYears(schoolYearList);
	}
	}

}

void loadSchoolYearList(SchoolYearList &schoolYearList){
    ifstream fin;
	string path = "SchoolYear\\SchoolYear.csv";
    fin.open(path);
	char dummy[10000];
    if(fin.is_open()){
		string dummy;
		while (getline(fin, dummy, ',')) {
			if (dummy == "") return;
			SchoolYear *newSchoolYear = new SchoolYear;
			newSchoolYear->startYear = dummy;
			// load them class list 
			// load semester
			getline(fin, newSchoolYear->endYear);
			newSchoolYear->pNext = schoolYearList.schoolyearL;
			if (schoolYearList.schoolyearL != nullptr) schoolYearList.schoolyearL->pPrev = newSchoolYear;
			schoolYearList.schoolyearL = newSchoolYear;
		}
    } else {
        cout<<"Cannot open SchoolYear.csv" <<endl;
        return;
    }
    fin.close();
}
void createSchoolYear(SchoolYearList &schoolYearList, string path) {
	string start, end;
	cout << "Input Start Year: ";
	getline(cin, start);
	cout << "Input End Year: ";
	getline(cin, end);
	ofstream fout;
	fout.open(path,std::ios_base::app);
	if (fout.is_open()) {
		SchoolYear *newSchoolYear = new SchoolYear;
		newSchoolYear->startYear = start;
		newSchoolYear->endYear = end;
		newSchoolYear->pNext = schoolYearList.schoolyearL;
		if (schoolYearList.schoolyearL != nullptr) schoolYearList.schoolyearL->pPrev = newSchoolYear;
		schoolYearList.schoolyearL = newSchoolYear;
		fout << newSchoolYear->startYear << ",";
		fout << newSchoolYear->startYear << endl;
	}
	else {
		cout << "Cannot find or open SchoolYear.csv..." << endl;
		return;
	}
	fout.close();

	
}
void displaySchoolYears(SchoolYearList schoolYearList) {
	if (schoolYearList.schoolyearL == nullptr) return;
	SchoolYear *cur = schoolYearList.schoolyearL;
	while (cur != nullptr) {
		cout << cur->startYear << "-" << cur->endYear << endl;
	}
}