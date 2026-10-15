#ifndef COMPANY_H
#define COMPANY_H

#include "queue.h"
#include "stack.h"
#include "history.h"

struct Company {
    string name;
    Queue screening;
    Queue interview;
    Queue offer;
    Queue held;       
    Queue rejected;   
};

Company createCompany(string name) {
    Company c;
    c.name = name;
    c.screening = createQueue();
    c.interview = createQueue();
    c.offer = createQueue();
    c.held = createQueue();
    c.rejected = createQueue();
    return c;
}

void addApplicant(Company &c, int id, string name) {
    enqueue(c.screening, id, name);
    cout << name << " added to " << c.name << "'s Screening queue." << endl;
}

void advanceApplicant(Company &c, int id) {
    Applicant* a = removeById(c.screening, id);
    if (a != NULL) {
        addHistoryEvent(a->historyHead, "Interview");
        push(id, a->name, "Screening", "Interview");
        a->currentStage = "Interview";
        enqueue(c.interview, id, a->name);
        cout << a->name << " moved to Interview." << endl;
        delete a;
        return;
    }

    a = removeById(c.interview, id);
    if (a != NULL) {
        addHistoryEvent(a->historyHead, "Offer");
        push(id, a->name, "Interview", "Offer");
        a->currentStage = "Offer";
        enqueue(c.offer, id, a->name);
        cout << a->name << " moved to Offer." << endl;
        delete a;
        return;
    }

    cout << "Applicant not found in Screening or Interview." << endl;
}


Applicant* findAndRemoveFromCurrentStage(Company &c, int id, string &foundStage) {
    Applicant* a;

    a = removeById(c.screening, id);
    if (a != NULL) { foundStage = "Screening"; return a; }

    a = removeById(c.interview, id);
    if (a != NULL) { foundStage = "Interview"; return a; }

    a = removeById(c.offer, id);
    if (a != NULL) { foundStage = "Offer"; return a; }

    a = removeById(c.held, id);
    if (a != NULL) { foundStage = "Held"; return a; }

    foundStage = "";
    return NULL;
}


void holdApplicant(Company &c, int id) {
    string sourceStage;
    Applicant* a = findAndRemoveFromCurrentStage(c, id, sourceStage);

    if (a == NULL) {
        cout << "Applicant not found." << endl;
        return;
    }

    addHistoryEvent(a->historyHead, "Hold");
    push(id, a->name, sourceStage, "Hold");
    a->currentStage = "Hold";
    enqueue(c.held, id, a->name);
    cout << a->name << " moved to Hold (was in " << sourceStage << ")." << endl;
    delete a;
}


void rejectApplicant(Company &c, int id) {
    string sourceStage;
    Applicant* a = findAndRemoveFromCurrentStage(c, id, sourceStage);

    if (a == NULL) {
        cout << "Applicant not found." << endl;
        return;
    }

    addHistoryEvent(a->historyHead, "Rejected");
    push(id, a->name, sourceStage, "Rejected");
    a->currentStage = "Rejected";
    enqueue(c.rejected, id, a->name);
    cout << a->name << " has been Rejected (was in " << sourceStage << ")." << endl;
    delete a;
}

// Reconsider a held/rejected applicant back into a specific stage

void reconsiderApplicant(Company &c, int id, string targetStage) {
    string sourceStage;
    Applicant* a = findAndRemoveFromCurrentStage(c, id, sourceStage);

    if (a == NULL) {
        cout << "Applicant not found." << endl;
        return;
    }

    addHistoryEvent(a->historyHead, targetStage);
    push(id, a->name, sourceStage, targetStage);
    a->currentStage = targetStage;

    if (targetStage == "Screening") {
        enqueue(c.screening, id, a->name);
    } else if (targetStage == "Interview") {
        enqueue(c.interview, id, a->name);
    } else {
        cout << "Invalid target stage." << endl;
        delete a;
        return;
    }

    cout << a->name << " reconsidered into " << targetStage 
         << " (was in " << sourceStage << ")." << endl;
    delete a;
}


void displayCompany(Company &c) {
    cout << "\n--- " << c.name << " ---" << endl;
    cout << "Screening: "; display(c.screening);
    cout << "Interview: "; display(c.interview);
    cout << "Offer: ";     display(c.offer);
    cout << "Held: ";      display(c.held);
    cout << "Rejected: ";  display(c.rejected);
}

#endif