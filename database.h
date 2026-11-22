#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "company.h"
using namespace std;

string escapeCSV(const string &s) {
    string out = "\"";
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] == '"') out += "\"\"";
        else out += s[i];
    }
    out += "\"";
    return out;
}

vector<string> parseCSVLine(const string &line) {
    vector<string> fields;
    string current = "";
    bool inQuotes = false;

    for (int i = 0; i < (int)line.length(); i++) {
        char ch = line[i];
        if (ch == '"') {
            if (inQuotes && i + 1 < (int)line.length() && line[i + 1] == '"') {
                current += '"';
                i++;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (ch == ',' && !inQuotes) {
            fields.push_back(current);
            current = "";
        } else {
            current += ch;
        }
    }
    fields.push_back(current);
    return fields;
}

string serializeHistory(HistoryNode* head) {
    string out = "";
    HistoryNode* temp = head;
    while (temp != NULL) {
        out += temp->event;
        if (temp->next != NULL) out += "|";
        temp = temp->next;
    }
    return out;
}

void writeQueueToCSV(ofstream &out, const string &companyName, Queue &q, const string &stageName) {
    Applicant* temp = q.front;
    while (temp != NULL) {
        out << escapeCSV(companyName) << ","
            << temp->id << ","
            << escapeCSV(temp->name) << ","
            << escapeCSV(stageName) << ","
            << escapeCSV(serializeHistory(temp->historyHead)) << "\n";
        temp = temp->next;
    }
}

void writeStackToCSV(ofstream &out, const string &companyName, Action* node) {
    if (node == NULL) return;
    writeStackToCSV(out, companyName, node->next);
    out << escapeCSV(companyName) << ","
        << node->applicantId << ","
        << escapeCSV(node->applicantName) << ","
        << escapeCSV(node->sourceStage) << ","
        << escapeCSV(node->destStage) << "\n";
}

void saveDatabaseCSV(vector<Company> &companies) {
    ofstream compFile("companies.csv");
    ofstream appFile("applicants.csv");
    ofstream actFile("actions.csv");

    if (!compFile.is_open() || !appFile.is_open() || !actFile.is_open()) {
        cout << "Error opening CSV files for saving." << endl;
        return;
    }

    compFile << "companyName\n";
    appFile << "companyName,applicantId,applicantName,currentStage,history\n";
    actFile << "companyName,applicantId,applicantName,sourceStage,destStage\n";

    for (int i = 0; i < (int)companies.size(); i++) {
        compFile << escapeCSV(companies[i].name) << "\n";

        writeQueueToCSV(appFile, companies[i].name, companies[i].screening, "Screening");
        writeQueueToCSV(appFile, companies[i].name, companies[i].interview, "Interview");
        writeQueueToCSV(appFile, companies[i].name, companies[i].offer, "Offer");
        writeQueueToCSV(appFile, companies[i].name, companies[i].held, "Hold");
        writeQueueToCSV(appFile, companies[i].name, companies[i].rejected, "Rejected");

        writeStackToCSV(actFile, companies[i].name, companies[i].undoStack.top);
    }

    compFile.close();
    appFile.close();
    actFile.close();
    cout << "Saved database to companies.csv, applicants.csv, and actions.csv." << endl;
}

int findCompanyIndexByName(vector<Company> &companies, const string &name) {
    for (int i = 0; i < (int)companies.size(); i++) {
        if (companies[i].name == name) return i;
    }
    return -1;
}

void loadDatabaseCSV(vector<Company> &companies) {
    ifstream compFile("companies.csv");
    if (!compFile.is_open()) {
        return;
    }

    companies.clear();
    string line;
    bool isHeader = true;

    while (getline(compFile, line)) {
        if (line.empty()) continue;
        if (isHeader) { isHeader = false; continue; }
        vector<string> fields = parseCSVLine(line);
        if (fields.size() >= 1 && !fields[0].empty()) {
            companies.push_back(createCompany(fields[0]));
        }
    }
    compFile.close();

    ifstream appFile("applicants.csv");
    if (appFile.is_open()) {
        isHeader = true;
        while (getline(appFile, line)) {
            if (line.empty()) continue;
            if (isHeader) { isHeader = false; continue; }
            vector<string> f = parseCSVLine(line);
            if (f.size() >= 4) {
                int cIdx = findCompanyIndexByName(companies, f[0]);
                if (cIdx != -1) {
                    int id = stoi(f[1]);
                    string name = f[2];
                    string stage = f[3];
                    string histStr = (f.size() >= 5) ? f[4] : "";

                    Applicant* newApp = new Applicant;
                    newApp->id = id;
                    newApp->name = name;
                    newApp->currentStage = stage;
                    newApp->next = NULL;
                    newApp->historyHead = NULL;

                    if (!histStr.empty()) {
                        stringstream ss(histStr);
                        string ev;
                        while (getline(ss, ev, '|')) {
                            if (!ev.empty()) addHistoryEvent(newApp->historyHead, ev);
                        }
                    }

                    if (stage == "Screening") enqueueNode(companies[cIdx].screening, newApp, "Screening");
                    else if (stage == "Interview") enqueueNode(companies[cIdx].interview, newApp, "Interview");
                    else if (stage == "Offer") enqueueNode(companies[cIdx].offer, newApp, "Offer");
                    else if (stage == "Hold") enqueueNode(companies[cIdx].held, newApp, "Hold");
                    else if (stage == "Rejected") enqueueNode(companies[cIdx].rejected, newApp, "Rejected");
                    else enqueueNode(companies[cIdx].screening, newApp, "Screening");
                }
            }
        }
        appFile.close();
    }

    ifstream actFile("actions.csv");
    if (actFile.is_open()) {
        isHeader = true;
        while (getline(actFile, line)) {
            if (line.empty()) continue;
            if (isHeader) { isHeader = false; continue; }
            vector<string> f = parseCSVLine(line);
            if (f.size() >= 5) {
                int cIdx = findCompanyIndexByName(companies, f[0]);
                if (cIdx != -1) {
                    int id = stoi(f[1]);
                    push(companies[cIdx].undoStack, id, f[2], f[3], f[4]);
                }
            }
        }
        actFile.close();
    }

    if (!companies.empty()) {
        cout << "Loaded database from CSV files." << endl;
    }
}

#endif