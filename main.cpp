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
        cout<<"Enter applicant ID: ";
        cin>> name;
        addApplicant(tcs, id, name);
}

else if (choice==2){
    int id;
    cout<< "Enter Applicant ID to adavce: ";
    cin>> id;
    advanceApplicant(tcs, id);
}
else if(choice == 3){
    int id;
    cout<< "Enter applicant ID to hold: ";
    cin>> id;
    holdApplicant(tcs, id);
}
else if (choice==4){
    int id;
    cout<<"Enter applicant ID to reject: ";
    cin>>id;
    rejectApplicant(tcs, id);
}
else if(choice==5){
    int id;
    string stage;
    cout<<"Enter applicant ID to reconsider: ";
    cin>> id;
    cout<<"Enter target stage (Screening/Interview): ";
    cin >> stage;
    reconsiderApplicant(tcs, id, stage);
}
else if (choice==6){
    Action* last = pop();
    if(last!= NULL){
        string dummy;
        Applicant* a =findAndRemoveFromCurrentStage(tcs, last->applicantId, dummy);
        if (a != NULL) {
                    a->currentStage = last->sourceStage;
                    if (last->sourceStage == "Screening") enqueue(tcs.screening, a->id, a->name);
                    else if (last->sourceStage == "Interview") enqueue(tcs.interview, a->id, a->name);
                    else if (last->sourceStage == "Offer") enqueue(tcs.offer, a->id, a->name);
                    else if (last->sourceStage == "Hold") enqueue(tcs.held, a->id, a->name);
                    cout << a->name << " undone, moved back to " << last->sourceStage << endl;
                    delete a;
                }
                
