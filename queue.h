#ifndef QUEUE_H
#define QUEUE_H

#include "applicant.h"

// making Queue structure ,for having multiple queue 
struct Queue {
    Applicant* front;
    Applicant* rear;
};

// creating a new empty queue
Queue createQueue() {
    Queue q;
    q.front = NULL;
    q.rear = NULL;
    return q;
}

// Adding new applicant to the back of a SPECIFIC queue
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

// Remove and return the applicant from the front of a SPECIFIC queue
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

// Remove a SPECIFIC applicant by ID, from a SPECIFIC queue
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

    cout << "Applicant with ID " << id << " not found in queue." << endl;
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