#ifndef APPLICANT_H
#define APPLICANT_H

#include <iostream>
using namespace std;

struct HistoryNode;  

struct Applicant {
    int id;
    string name;
    string currentStage;
    Applicant* next;         
    HistoryNode* historyHead;  
};

#endif