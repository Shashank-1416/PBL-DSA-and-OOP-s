#ifndef APPLICANT_H
#define APPLICANT_H

#include <iostream>
#include <string>
using namespace std;

class HistoryList;

class Applicant {
private:
    int id;
    string name;
    string currentStage;
    Applicant* next;
    HistoryList* history;

public:
    Applicant(int id = 0, string name = "", string stage = "Applied");
    ~Applicant();

    int getId() const;
    string getName() const;
    string getCurrentStage() const;
    Applicant* getNext() const;
    HistoryList* getHistory() const;

    void setId(int newId);
    void setName(string newName);
    void setCurrentStage(string stage);
    void setNext(Applicant* nextPtr);
    void setHistory(HistoryList* histPtr);

    void addEvent(const string& event);
    void showHistory() const;
};

#endif