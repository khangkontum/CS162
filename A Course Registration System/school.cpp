#include "school.h"

void displayCommandMenu()
{
    int option =0;
    cout << "---------------------------------------";
    cout << "1. Create a school year.";
    cout << "2. Create classes.";
    SchoolYearList schoolYearList;
    loadSchoolYearList(schoolYearList);
    cin >> option;

}
void loadSchoolYearList(SchoolYearList &schoolYearList){
    ifstream fin;
    fin.open("SchoolYear\\SchoolYear.csv");
    if(fin.is_open()){
        cout<<"Opened"<<endl;
    } else {
        cout<<"Cannot open SchoolYear.csv" <<endl;
        return;
    }
    fin.close();
}