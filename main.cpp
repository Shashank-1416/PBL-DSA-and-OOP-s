#include "company.h"

int main() {
    Company tcs = createCompany("TCS");

    addApplicant(tcs, 101, "Rahul");
    advanceApplicant(tcs, 101);   // Screening -> Interview

    displayCompany(tcs);
    displayActions();

    // Now undo it
    cout << "\nUndoing last action..." << endl;
    Action* last = pop();
    if (last != NULL) {
        Applicant* a = removeById(tcs.interview, last->applicantId);
        if (a != NULL) {
            a->currentStage = last->sourceStage;
            enqueue(tcs.screening, a->id, a->name);
            cout << a->name << " moved back to " << last->sourceStage << endl;
            delete a;
        }
    }

    displayCompany(tcs);

    return 0;
}