#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

struct Action {
    int applicantId;
    string applicantName;
    string sourceStage;
    string destStage;
    Action* next;  
};

struct ActionStack {
    Action* top;
};

ActionStack createStack() {
    ActionStack s;
    s.top = NULL;
    return s;
}

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

#endif