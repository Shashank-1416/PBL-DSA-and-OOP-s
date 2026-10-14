#include "company.h"

int main() {
    Company tcs = createCompany("TCS");

    addApplicant(tcs, 101, "Rahul");
    addApplicant(tcs, 102, "Priya");

    displayCompany(tcs);

    advanceApplicant(tcs, 101);   // Rahul: Screening -> Interview

    displayCompany(tcs);

    advanceApplicant(tcs, 101);   // Rahul: Interview -> Offer

    displayCompany(tcs);

    return 0;
}