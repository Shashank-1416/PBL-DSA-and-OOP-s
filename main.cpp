#include <iostream>
#include <vector>
#include "database.h"
using namespace std;

void showMenu(const string &activeCompanyName) {
    cout << "\n===== Recruitment Tracker (" << activeCompanyName << ") =====" << endl;
    cout << "1. Add Applicant" << endl;
    cout << "2. Advance Applicant" << endl;
    cout << "3. Hold Applicant" << endl;
    cout << "4. Reject Applicant" << endl;
    cout << "5. Reconsider Applicant" << endl;
    cout << "6. Undo Last Action" << endl;
    cout << "7. View All Stages" << endl;
    cout << "8. Add New Company" << endl;
    cout << "9. Switch Active Company" << endl;
    cout << "10. View All Companies" << endl;
    cout << "11. Save to CSV" << endl;
    cout << "12. Load from CSV" << endl;
    cout << "13. Exit" << endl;
    cout << "Enter choice: ";
}

int main() {
    vector<Company> companies;
    companies.push_back(createCompany("TCS"));
    loadDatabaseCSV(companies);

    int activeIdx = 0;
    int choice;

    do {
        showMenu(companies[activeIdx].name);
        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            cout << "Enter applicant ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            addApplicant(companies[activeIdx], id, name);
        } else if (choice == 2) {
            int id;
            cout << "Enter Applicant ID to advance: ";
            cin >> id;
            advanceApplicant(companies[activeIdx], id);
        } else if (choice == 3) {
            int id;
            cout << "Enter applicant ID to hold: ";
            cin >> id;
            holdApplicant(companies[activeIdx], id);
        } else if (choice == 4) {
            int id;
            cout << "Enter applicant ID to reject: ";
            cin >> id;
            rejectApplicant(companies[activeIdx], id);
        } else if (choice == 5) {
            int id;
            string stage;
            cout << "Enter applicant ID to reconsider: ";
            cin >> id;
            cout << "Enter target stage (Screening/Interview): ";
            cin >> stage;
            reconsiderApplicant(companies[activeIdx], id, stage);
        } else if (choice == 6) {
            Action* last = pop(companies[activeIdx].undoStack);
            if (last != NULL) {
                string dummy;
                Applicant* a = findAndRemoveFromCurrentStage(companies[activeIdx], last->applicantId, dummy);
                if (a != NULL) {
                    if (last->sourceStage == "None") {
                        cout << "Undid Add for " << a->name << endl;
                        delete a;
                    } else {
                        a->currentStage = last->sourceStage;
                        if (last->sourceStage == "Screening") enqueueNode(companies[activeIdx].screening, a, "Screening");
                        else if (last->sourceStage == "Interview") enqueueNode(companies[activeIdx].interview, a, "Interview");
                        else if (last->sourceStage == "Offer") enqueueNode(companies[activeIdx].offer, a, "Offer");
                        else if (last->sourceStage == "Hold") enqueueNode(companies[activeIdx].held, a, "Hold");
                        else if (last->sourceStage == "Rejected") enqueueNode(companies[activeIdx].rejected, a, "Rejected");
                        cout << a->name << " undone, moved back to " << last->sourceStage << endl;
                    }
                }
                delete last;
            }
        } else if (choice == 7) {
            displayCompany(companies[activeIdx]);
        } else if (choice == 8) {
            string cname;
            cout << "Enter new company name: ";
            cin >> cname;
            companies.push_back(createCompany(cname));
            activeIdx = (int)companies.size() - 1;
            cout << "Added and switched to " << cname << "." << endl;
        } else if (choice == 9) {
            cout << "\nCompanies:" << endl;
            for (int i = 0; i < (int)companies.size(); i++) {
                cout << (i + 1) << ". " << companies[i].name
                     << (i == activeIdx ? " [Active]" : "") << endl;
            }
            int sel;
            cout << "Select company number: ";
            cin >> sel;
            if (sel >= 1 && sel <= (int)companies.size()) {
                activeIdx = sel - 1;
                cout << "Switched to " << companies[activeIdx].name << "." << endl;
            } else {
                cout << "Invalid selection." << endl;
            }
        } else if (choice == 10) {
            for (int i = 0; i < (int)companies.size(); i++) {
                displayCompany(companies[i]);
            }
        } else if (choice == 11) {
            saveDatabaseCSV(companies);
        } else if (choice == 12) {
            loadDatabaseCSV(companies);
            activeIdx = 0;
        } else if (choice == 13) {
            saveDatabaseCSV(companies);
            cout << "Exiting..." << endl;
        } else {
            cout << "Invalid choice." << endl;
        }

    } while (choice != 13);

    return 0;
}