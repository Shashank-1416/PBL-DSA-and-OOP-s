#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
using namespace std;


struct HistoryNode {
    string event;
    HistoryNode* next;
};

void addHistoryEvent(HistoryNode*& head, string event) {
    HistoryNode* newNode = new HistoryNode;
    newNode->event = event;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    HistoryNode* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}


void displayHistory(HistoryNode* head) {
    if (head == NULL) {
        cout << "No history yet." << endl;
        return;
    }
    HistoryNode* temp = head;
    cout << "History: ";
    while (temp != NULL) {
        cout << temp->event;
        if (temp->next != NULL) cout << " -> ";
        temp = temp->next;
    }
    cout << endl;
}

#endif