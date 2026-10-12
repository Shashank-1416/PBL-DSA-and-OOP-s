#ifndef QUEUE_H
#define QUEUE_H

#include "applicant.h"

applicant* front =NULL;
applicant* rear =NULL;

void enqueue(int id , string name) {
applicant* newapplicant = new applicant;
newapplicant->id = id;
newapplicant->name = name;
newapplicant->currentStage = "Applied";
newapplicant->next=NULL;

if(rear==NULL){
front=rear=newapplicant;
}
else{
    rear->next= newapplicant;
}

}
