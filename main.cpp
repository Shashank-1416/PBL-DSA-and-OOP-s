#include"queue.h"

int main(){

enqueue(101,"Rahul");
enqueue(102,"Monu");
enqueue(103,"Bonu");

cout << "Before removal:" << endl;
    display();

applicant* removed = removeById(102);  
    if (removed != NULL) {
        cout << "Removed: " << removed->name << endl;
    }

    cout<<"After removal"<<endl;
    display();

    return 0;
}