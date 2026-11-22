#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <sstream>
#include <vector>
#include "company.h"
using namespace std;

void saveQueueCSV(ofstream &file, string companyName, Queue &q, string stage) {
    Applicant* temp = q.front;
    while (temp != NULL) {
        string hist = "";
        HistoryNode* h = temp->historyHead;
        while (h != NULL) {
            hist += h->event;
            if (h->next != NULL) hist += "|";
            h = h->next;
        }
        file << companyName << "," << temp->id << "," << temp->name << "," << stage << "," << hist << "\n";
        temp = temp->next;
    }
}

void saveStackCSV(ofstream &file, string companyName, Action* node) {
    if (node == NULL) return;
    saveStackCSV(file, companyName, node->next);
    file << companyName << "," << node->applicantId << "," << node->applicantName
         << "," << node->sourceStage << "," << node->destStage << "\n";
}

void saveCSV(vector<Company> &companies) {
    ofstream cFile("companies.csv");
    ofstream aFile("applicants.csv");
    ofstream sFile("actions.csv");

    for (int i = 0; i < (int)companies.size(); i++) {
        cFile << companies[i].name << "\n";
        saveQueueCSV(aFile, companies[i].name, companies[i].screening, "Screening");
        saveQueueCSV(aFile, companies[i].name, companies[i].interview, "Interview");
        saveQueueCSV(aFile, companies[i].name, companies[i].offer, "Offer");
        saveQueueCSV(aFile, companies[i].name, companies[i].held, "Hold");
        saveQueueCSV(aFile, companies[i].name, companies[i].rejected, "Rejected");
        saveStackCSV(sFile, companies[i].name, companies[i].undoStack.top);
    }

    cFile.close();
    aFile.close();
    sFile.close();
    cout << "Data saved to CSV files." << endl;
}

int findCompany(vector<Company> &companies, string name) {
    for (int i = 0; i < (int)companies.size(); i++) {
        if (companies[i].name == name) return i;
    }
    return -1;
}

void loadCSV(vector<Company> &companies) {
    ifstream cFile("companies.csv");
    if (!cFile.is_open()) return;

    companies.clear();
    string cname;
    while (getline(cFile, cname)) {
        if (!cname.empty()) {
            companies.push_back(createCompany(cname));
        }
    }
    cFile.close();

    ifstream aFile("applicants.csv");
    if (aFile.is_open()) {
        string line;
        while (getline(aFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string compName, idStr, appName, stage, histStr;

            getline(ss, compName, ',');
            getline(ss, idStr, ',');
            getline(ss, appName, ',');
            getline(ss, stage, ',');
            getline(ss, histStr);

            int idx = findCompany(companies, compName);
            if (idx != -1) {
                Applicant* a = new Applicant;
                a->id = stoi(idStr);
                a->name = appName;
                a->currentStage = stage;
                a->next = NULL;
                a->historyHead = NULL;

                stringstream hss(histStr);
                string ev;
                while (getline(hss, ev, '|')) {
                    if (!ev.empty()) addHistoryEvent(a->historyHead, ev);
                }

                if (stage == "Screening") enqueueNode(companies[idx].screening, a, "Screening");
                else if (stage == "Interview") enqueueNode(companies[idx].interview, a, "Interview");
                else if (stage == "Offer") enqueueNode(companies[idx].offer, a, "Offer");
                else if (stage == "Hold") enqueueNode(companies[idx].held, a, "Hold");
                else if (stage == "Rejected") enqueueNode(companies[idx].rejected, a, "Rejected");
            }
        }
        aFile.close();
    }

    ifstream sFile("actions.csv");
    if (sFile.is_open()) {
        string line;
        while (getline(sFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string compName, idStr, appName, src, dst;

            getline(ss, compName, ',');
            getline(ss, idStr, ',');
            getline(ss, appName, ',');
            getline(ss, src, ',');
            getline(ss, dst);

            int idx = findCompany(companies, compName);
            if (idx != -1) {
                push(companies[idx].undoStack, stoi(idStr), appName, src, dst);
            }
        }
        sFile.close();
    }

    cout << "Data loaded from CSV files." << endl;
}

#endif