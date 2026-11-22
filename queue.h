#ifndef QUEUE_H
#define QUEUE_H

#include "applicant.h"

struct Queue {
    Applicant* front;
    Applicant* rear;
};

Queue createQueue() {
    Queue q;
    q.front = NULL;
    q.rear = NULL;
    return q;
}

// Moves an existing Applicant node without losing its historyHead
void enqueueNode(Queue &q, Applicant* node, string stageName) {
    if (node == NULL) return;
    node->currentStage = stageName;
    node->next = NULL;

    if (q.rear == NULL) {
        q.front = node;
        q.rear = node;
    } else {
        q.rear->next = node;
        q.rear = node;
    }
}

void enqueue(Queue &q, int id, string name) {
    Applicant* newApplicant = new Applicant;
    newApplicant->id = id;
    newApplicant->name = name;
    newApplicant->currentStage = "Applied";
    newApplicant->next = NULL;
    newApplicant->historyHead = NULL;   

    if (q.rear == NULL) {
        q.front = newApplicant;
        q.rear = newApplicant;
    } else {
        q.rear->next = newApplicant;
        q.rear = newApplicant;
    }
}

Applicant* dequeue(Queue &q) {
    if (q.front == NULL) {
        cout << "Queue is empty!" << endl;
        return NULL;
    }
    Applicant* temp = q.front;
    q.front = q.front->next;
    if (q.front == NULL) {
        q.rear = NULL;
    }
    return temp;
}

Applicant* removeById(Queue &q, int id) {
    Applicant* current = q.front;
    Applicant* previous = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (previous == NULL) {
                q.front = current->next;
            } else {
                previous->next = current->next;
            }
            if (current == q.rear) {
                q.rear = previous;
            }
            current->next = NULL;
            return current;
        }
        previous = current;
        current = current->next;
    }

    return NULL;
}

void display(Queue &q) {
    Applicant* temp = q.front;
    if (temp == NULL) {
        cout << "Empty." << endl;
        return;
    }
    while (temp != NULL) {
        cout << temp->name << "(" << temp->id << ") -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

#endif