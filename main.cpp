#include "company.h"

int main() {
    Company tcs = createCompany("TCS");

    addApplicant(tcs, 101, "Rahul");
    addApplicant(tcs, 102, "Priya");
    addApplicant(tcs, 103, "Karan");

    advanceApplicant(tcs, 101);   
    holdApplicant(tcs, 102);      
    rejectApplicant(tcs, 103);    

    displayCompany(tcs);

    return 0;
}