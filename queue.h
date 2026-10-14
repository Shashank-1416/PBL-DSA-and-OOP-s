#ifndef QUEUE_H
#define QUEUE_H

#include "applicant.h"

Applicant* front =NULL;
Applicant* rear =NULL;

void enqueue(int id , string name) {
Applicant* newapplicant = new Applicant;
newapplicant->id = id;
newapplicant->name = name;
newapplicant->currentStage = "Applied";
newapplicant->next=NULL;

if(rear==NULL){
front=rear=newapplicant;
}
else{
    rear->next= newapplicant;
    rear = newapplicant;

}
}


Applicant* dequeue(){
    if (front==NULL){
        cout<<"Queue is empty"<<endl;
        return NULL;
    }

Applicant*temp = front;
front= front->next;
if(front==NULL){
    rear=NULL;
}
return temp;

}

Applicant* removeById(int id){
 Applicant* current = front;
Applicant* previous = NULL;

while (current != NULL) {
    if(current->id==id){


        if(previous==NULL){
            front=current->next;
        }
        else{
            previous->next=current->next;
        }

        if(current==rear){
            rear=previous;
        }
        current->next = NULL;  
        return current;
    }
    previous=current ;
    current=current->next;
}

cout << "Applicant with ID " << id << " not found in queue." << endl;
    return NULL;
}



void display() {
    Applicant* temp = front;
    if (temp == NULL) {
        cout << "No applicants in queue." << endl;
        return;
    }
    cout << "Current Queue: ";
    while (temp != NULL) {
        cout << temp->name << "(" << temp->id << ") -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

#endif
