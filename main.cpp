#include "queue.h"
#include "stack.h"

int main() {
    enqueue(101, "Rahul");
    enqueue(102, "Priya");
    enqueue(103, "Karan");

    cout << "Initial Queue:" << endl;
    display();

   
    removeById(101);
    push(101, "Rahul", "Screening", "Interview");

    cout << "\nAfter advancing Rahul:" << endl;
    display();
    displayActions();

    // Now undo it
    cout << "\nUndoing last action..." << endl;
    Action* lastAction = pop();
    if (lastAction != NULL) {
        cout << "Reversing: " << lastAction->applicantName 
             << " back to " << lastAction->sourceStage << endl;
        enqueue(lastAction->applicantId, lastAction->applicantName);
    }

    cout << "\nAfter undo:" << endl;
    display();
    displayActions();

    return 0;
}