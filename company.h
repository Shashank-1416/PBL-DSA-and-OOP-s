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
};

Company createCompany(string name) {
    Company c;
    c.name = name;
    c.screening = createQueue();
    c.interview = createQueue();
    c.offer = createQueue();
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

void displayCompany(Company &c) {
    cout << "\n--- " << c.name << " ---" << endl;
    cout << "Screening: ";
    display(c.screening);
    cout << "Interview: ";
    display(c.interview);
    cout << "Offer: ";
    display(c.offer);
}

#endif