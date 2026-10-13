#ifndef STACK_H
#define STACK_H

#include "applicant.h"

struct Action {
    int applicantId;
    string applicantName;
    string sourceStage;
    string destStage;
    Action* next;  
};

Action* top = NULL;

void push(int id, string name, string source, string dest) {
    Action* newAction = new Action;
    newAction->applicantId = id;
    newAction->applicantName = name;
    newAction->sourceStage = source;
    newAction->destStage = dest;
    newAction->next = top;    
    top = newAction;          
}


Action* pop() {
    if (top == NULL) {
        cout << "No actions to undo!" << endl;
        return NULL;
    }
    Action* temp = top;
    top = top->next;
    temp->next = NULL;
    return temp;
}


bool isStackEmpty() {
    return top == NULL;
}


