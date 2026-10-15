#include "company.h"

int main() {
    Company tcs = createCompany("TCS");

    addApplicant(tcs, 101, "Rahul");
    holdApplicant(tcs, 101);                         
    reconsiderApplicant(tcs, 101, "Screening");        

    displayCompany(tcs);

    return 0;
}