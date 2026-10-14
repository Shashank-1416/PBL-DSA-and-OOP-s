#include "queue.h"
#include "stack.h"
#include "history.h"

int main() {
    enqueue(101, "Rahul");
    enqueue(102, "Priya");

    // Find Rahul's node (front of queue, since he was added first)
    Applicant* rahul = front;
    rahul->historyHead = NULL;   // start with empty history

    addHistoryEvent(rahul->historyHead, "Applied");
    addHistoryEvent(rahul->historyHead, "Screening");
    addHistoryEvent(rahul->historyHead, "Interview");

    cout << "Rahul's history:" << endl;
    displayHistory(rahul->historyHead);

    return 0;
}