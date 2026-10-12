#ifndef APPLICANT_H
#define APPLICANT_H
#include <iostream>
using namespace std;


struct applicant {
    int id;
    string name;
    string currentStage;
    applicant* next;
};
#endif