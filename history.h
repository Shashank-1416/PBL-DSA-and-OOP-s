#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <string>
#include "applicant.h"
using namespace std;

struct HistoryNode {
    string event;
    HistoryNode* next;

    HistoryNode(const string& ev, HistoryNode* nxt = NULL)
        : event(ev), next(nxt) {}
};

class HistoryList {
private:
    HistoryNode* head;
    HistoryNode* tail;

public:
    HistoryList() : head(NULL), tail(NULL) {}

    ~HistoryList() {
        clear();
    }

    HistoryNode* getHead() const {
        return head;
    }

    void addEvent(const string& event) {
        HistoryNode* newNode = new HistoryNode(event, NULL);
        if (tail == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void display() const {
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

    void clear() {
        HistoryNode* temp = head;
        while (temp != NULL) {
            HistoryNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = tail = NULL;
    }
};

// Applicant method definitions placed after HistoryList is complete
inline Applicant::Applicant(int id, string name, string stage)
    : id(id), name(name), currentStage(stage), next(NULL), history(new HistoryList()) {}

inline Applicant::~Applicant() {
    delete history;
    history = NULL;
}

inline int Applicant::getId() const { return id; }
inline string Applicant::getName() const { return name; }
inline string Applicant::getCurrentStage() const { return currentStage; }
inline Applicant* Applicant::getNext() const { return next; }
inline HistoryList* Applicant::getHistory() const { return history; }

inline void Applicant::setId(int newId) { id = newId; }
inline void Applicant::setName(string newName) { name = newName; }
inline void Applicant::setCurrentStage(string stage) { currentStage = stage; }
inline void Applicant::setNext(Applicant* nextPtr) { next = nextPtr; }
inline void Applicant::setHistory(HistoryList* histPtr) { history = histPtr; }

inline void Applicant::addEvent(const string& event) {
    if (history == NULL) {
        history = new HistoryList();
    }
    history->addEvent(event);
}

inline void Applicant::showHistory() const {
    if (history == NULL) {
        cout << "No history yet." << endl;
        return;
    }
    history->display();
}

#endif