#ifndef COMPANY_H
#define COMPANY_H

#include <cctype>
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
    ActionStack undoStack;
};

Company createCompany(string name) {
    Company c;
    c.name = name;
    c.screening = createQueue();
    c.interview = createQueue();
    c.offer = createQueue();
    c.held = createQueue();
    c.rejected = createQueue();
    c.undoStack = createStack();
    return c;
}

string toLower(string s) {
    for (int i = 0; i < (int)s.length(); i++) {
        s[i] = tolower(s[i]);
    }
    return s;
}

void addApplicant(Company &c, int id, string name) {
    Applicant* a = new Applicant;
    a->id = id;
    a->name = name;
    a->currentStage = "Screening";
    a->next = NULL;
    a->historyHead = NULL;

    addHistoryEvent(a->historyHead, "Applied");
    addHistoryEvent(a->historyHead, "Screening");
    enqueueNode(c.screening, a, "Screening");
    push(c.undoStack, id, name, "None", "Screening");
    cout << name << " added to " << c.name << "'s Screening queue." << endl;
}

void advanceApplicant(Company &c, int id) {
    Applicant* a = removeById(c.screening, id);
    if (a != NULL) {
        addHistoryEvent(a->historyHead, "Interview");
        push(c.undoStack, id, a->name, "Screening", "Interview");
        enqueueNode(c.interview, a, "Interview");
        cout << a->name << " moved to Interview." << endl;
        return;
    }

    a = removeById(c.interview, id);
    if (a != NULL) {
        addHistoryEvent(a->historyHead, "Offer");
        push(c.undoStack, id, a->name, "Interview", "Offer");
        enqueueNode(c.offer, a, "Offer");
        cout << a->name << " moved to Offer." << endl;
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
    if (a != NULL) { foundStage = "Hold"; return a; }

    a = removeById(c.rejected, id);
    if (a != NULL) { foundStage = "Rejected"; return a; }

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
    push(c.undoStack, id, a->name, sourceStage, "Hold");
    enqueueNode(c.held, a, "Hold");
    cout << a->name << " moved to Hold (was in " << sourceStage << ")." << endl;
}

void rejectApplicant(Company &c, int id) {
    string sourceStage;
    Applicant* a = findAndRemoveFromCurrentStage(c, id, sourceStage);

    if (a == NULL) {
        cout << "Applicant not found." << endl;
        return;
    }

    addHistoryEvent(a->historyHead, "Rejected");
    push(c.undoStack, id, a->name, sourceStage, "Rejected");
    enqueueNode(c.rejected, a, "Rejected");
    cout << a->name << " has been Rejected (was in " << sourceStage << ")." << endl;
}

void reconsiderApplicant(Company &c, int id, string targetStage) {
    string sourceStage;
    Applicant* a = findAndRemoveFromCurrentStage(c, id, sourceStage);

    if (a == NULL) {
        cout << "Applicant not found." << endl;
        return;
    }

    string targetLower = toLower(targetStage);

    if (targetLower == "screening") {
        addHistoryEvent(a->historyHead, "Screening");
        push(c.undoStack, id, a->name, sourceStage, "Screening");
        enqueueNode(c.screening, a, "Screening");
        cout << a->name << " reconsidered into Screening (was in " << sourceStage << ")." << endl;
    } else if (targetLower == "interview") {
        addHistoryEvent(a->historyHead, "Interview");
        push(c.undoStack, id, a->name, sourceStage, "Interview");
        enqueueNode(c.interview, a, "Interview");
        cout << a->name << " reconsidered into Interview (was in " << sourceStage << ")." << endl;
    } else {
        cout << "Invalid target stage." << endl;
        enqueueNode(c.held, a, sourceStage);
    }
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