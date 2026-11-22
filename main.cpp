#include <iostream>
#include <vector>
#include "database.h"
using namespace std;

void showMenu(string activeCompany) {
    cout << "\n===== Recruitment Tracker (" << activeCompany << ") =====" << endl;
    cout << "1. Add Applicant" << endl;
    cout << "2. Advance Applicant" << endl;
    cout << "3. Hold Applicant" << endl;
    cout << "4. Reject Applicant" << endl;
    cout << "5. Reconsider Applicant" << endl;
    cout << "6. Undo Last Action" << endl;
    cout << "7. View All Stages" << endl;
    cout << "8. Add Company" << endl;
    cout << "9. Switch Company" << endl;
    cout << "10. View All Companies" << endl;
    cout << "11. Save to CSV" << endl;
    cout << "12. Load from CSV" << endl;
    cout << "13. Exit" << endl;
    cout << "Enter choice: ";
}

int main() {
    vector<Company> companies;
    companies.push_back(createCompany("TCS"));
    loadCSV(companies);

    int active = 0;
    int choice;

    do {
        showMenu(companies[active].name);
        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            cout << "Enter applicant ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            addApplicant(companies[active], id, name);
        } else if (choice == 2) {
            int id;
            cout << "Enter Applicant ID to advance: ";
            cin >> id;
            advanceApplicant(companies[active], id);
        } else if (choice == 3) {
            int id;
            cout << "Enter applicant ID to hold: ";
            cin >> id;
            holdApplicant(companies[active], id);
        } else if (choice == 4) {
            int id;
            cout << "Enter applicant ID to reject: ";
            cin >> id;
            rejectApplicant(companies[active], id);
        } else if (choice == 5) {
            int id;
            string stage;
            cout << "Enter applicant ID to reconsider: ";
            cin >> id;
            cout << "Enter target stage (Screening/Interview): ";
            cin >> stage;
            reconsiderApplicant(companies[active], id, stage);
        } else if (choice == 6) {
            Action* last = pop(companies[active].undoStack);
            if (last != NULL) {
                string dummy;
                Applicant* a = findAndRemoveFromCurrentStage(companies[active], last->applicantId, dummy);
                if (a != NULL) {
                    if (last->sourceStage == "None") {
                        delete a;
                        cout << "Undid Add." << endl;
                    } else {
                        if (last->sourceStage == "Screening") enqueueNode(companies[active].screening, a, "Screening");
                        else if (last->sourceStage == "Interview") enqueueNode(companies[active].interview, a, "Interview");
                        else if (last->sourceStage == "Offer") enqueueNode(companies[active].offer, a, "Offer");
                        else if (last->sourceStage == "Hold") enqueueNode(companies[active].held, a, "Hold");
                        else if (last->sourceStage == "Rejected") enqueueNode(companies[active].rejected, a, "Rejected");
                        cout << a->name << " undone, moved back to " << last->sourceStage << endl;
                    }
                }
                delete last;
            }
        } else if (choice == 7) {
            displayCompany(companies[active]);
        } else if (choice == 8) {
            string cname;
            cout << "Enter new company name: ";
            cin >> cname;
            companies.push_back(createCompany(cname));
            active = (int)companies.size() - 1;
            cout << "Switched to " << cname << "." << endl;
        } else if (choice == 9) {
            for (int i = 0; i < (int)companies.size(); i++) {
                cout << (i + 1) << ". " << companies[i].name << endl;
            }
            int idx;
            cout << "Choose company: ";
            cin >> idx;
            if (idx >= 1 && idx <= (int)companies.size()) {
                active = idx - 1;
            } else {
                cout << "Invalid choice." << endl;
            }
        } else if (choice == 10) {
            for (int i = 0; i < (int)companies.size(); i++) {
                displayCompany(companies[i]);
            }
        } else if (choice == 11) {
            saveCSV(companies);
        } else if (choice == 12) {
            loadCSV(companies);
            active = 0;
        } else if (choice == 13) {
            saveCSV(companies);
            cout << "Exiting..." << endl;
        } else {
            cout << "Invalid choice." << endl;
        }
    } while (choice != 13);

    return 0;
}