#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "applicant.h"
using namespace std;

struct Action {
    int applicantId;
    string applicantName;
    string sourceStage;
    string destStage;
    Action* next;  
};

struct ActionStack {
    Action* top = NULL;
};

void push(ActionStack &s, int id, string name, string source, string dest) {
    Action* newAction = new Action;
    newAction->applicantId = id;
    newAction->applicantName = name;
    newAction->sourceStage = source;
    newAction->destStage = dest;
    newAction->next = s.top;    
    s.top = newAction;          
}

Action* pop(ActionStack &s) {
    if (s.top == NULL) {
        cout << "No actions to undo!" << endl;
        return NULL;
    }
    Action* temp = s.top;
    s.top = s.top->next;
    temp->next = NULL;
    return temp;
}

bool isStackEmpty(ActionStack &s) {
    return s.top == NULL;
}

void displayActions(ActionStack &s) {
    Action* temp = s.top;
    if (temp == NULL) {
        cout << "No actions recorded." << endl;
        return;
    }
    cout << "Action Stack (top to bottom):" << endl;
    int num = 1;
    while (temp != NULL) {
        cout << num << ". " << temp->applicantName << ": " 
             << temp->sourceStage << " -> " << temp->destStage << endl;
        temp = temp->next;
        num++;
    }
}

#endif