#include "company.h"

void showMenu(){

cout << "\n===== TCS Recruitment Tracker =====" << endl;
    cout << "1. Add Applicant" << endl;
    cout << "2. Advance Applicant" << endl;
    cout << "3. Hold Applicant" << endl;
    cout << "4. Reject Applicant" << endl;
    cout << "5. Reconsider Applicant" << endl;
    cout << "6. Undo Last Action" << endl;
    cout << "7. View All Stages" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter choice: ";
}

int main() {
 Company tcs = createCompany("TCS");
 int choice;

 do{
    showMenu();
    cin>>choice;

    if (choice == 1){
        int id;
        string name;
        cout<<"Enter applicant ID:";
        cin>> name;
        addApplicant(tcs, id, name);
}




 }


    return 0;
}