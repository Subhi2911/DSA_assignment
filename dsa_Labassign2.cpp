#include <iostream>
#include <string>
using namespace std;

/* ------------------ TICKET CLASS NODE (Linked List) ------------------ */

class Ticket {
public:
    int TicketID;
    string CustomerName, IssueDescription;
    int Priority;
    Ticket* next;

    Ticket(int id, string name, string issue, int p) {
        TicketID = id;
        CustomerName = name;
        IssueDescription = issue;
        Priority = p;
        next = nullptr;
    }
};

/* ------------------ Singly Linked List for Tickets ------------------ */

class TicketList {
public:
    Ticket* head;

    TicketList() { head = nullptr; }

    void insertTicket(int id, string name, string issue, int p) {
        Ticket* temp = new Ticket(id, name, issue, p);
        if (!head) {
            head = temp;
            return;
        }
        Ticket* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = temp;
    }

    void deleteTicket(int id) {
        if (!head) return;
        if (head->TicketID == id) {
            Ticket* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Ticket* curr = head;
        while (curr->next && curr->next->TicketID != id)
            curr = curr->next;
        if (curr->next) {
            Ticket* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        }
    }

    void retrieveTicket(int id) {
        Ticket* curr = head;
        while (curr) {
            if (curr->TicketID == id) {
                cout << "\nTicket Found:";
                cout << "\nID: " << curr->TicketID;
                cout << "\nCustomer: " << curr->CustomerName;
                cout << "\nIssue: " << curr->IssueDescription;
                cout << "\nPriority: " << curr->Priority << endl;
                return;
            }
            curr = curr->next;
        }
        cout << "\nTicket Not Found!\n";
    }

    void display() {
        Ticket* curr = head;
        cout << "\n--- Current Tickets ---\n";
        while (curr) {
            cout << curr->TicketID << " | " << curr->CustomerName << " | Priority: " << curr->Priority << endl;
            curr = curr->next;
        }
    }
};

/* ------------------ STACK FOR UNDO OPERATION ------------------ */

class UndoStack {
public:
    int top;
    int arr[100];

    UndoStack() { top = -1; }

    void push(int x) { arr[++top] = x; }

    int pop() {
        if (top == -1) return -1;
        return arr[top--];
    }

    bool isEmpty() { return top == -1; }
};

/* ------------------ PRIORITY QUEUE (URGENT FIRST) ------------------ */

class PriorityQueue {
public:
    Ticket* arr[100];
    int size;

    PriorityQueue() { size = 0; }

    void enqueue(Ticket* t) {
        int i = size++;
        while (i > 0 && arr[(i - 1) / 2]->Priority > t->Priority) {
            arr[i] = arr[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        arr[i] = t;
    }

    Ticket* dequeue() {
        if (size == 0) return nullptr;
        Ticket* root = arr[0];
        arr[0] = arr[--size];

        int i = 0;
        while (2 * i + 1 < size) {
            int c = 2 * i + 1;
            if (c + 1 < size && arr[c + 1]->Priority < arr[c]->Priority) c++;
            if (arr[i]->Priority < arr[c]->Priority) break;
            swap(arr[i], arr[c]);
            i = c;
        }
        return root;
    }

    bool isEmpty() { return size == 0; }
};

/* ------------------ CIRCULAR QUEUE FOR ROUND ROBIN ------------------ */

class CircularQueue {
public:
    Ticket* arr[100];
    int front, rear;

    CircularQueue() { front = rear = -1; }

    bool isEmpty() { return front == -1; }

    void enqueue(Ticket* t) {
        if ((rear + 1) % 100 == front) return;
        if (front == -1) front = 0;
        rear = (rear + 1) % 100;
        arr[rear] = t;
    }

    Ticket* dequeue() {
        if (isEmpty()) return nullptr;
        Ticket* t = arr[front];
        if (front == rear) front = rear = -1;
        else front = (front + 1) % 100;
        return t;
    }
};

/* ---------------- POLYNOMIAL LINKED LIST FOR BILLING ---------------- */

class PolyNode {
public:
    int coeff, pow;
    PolyNode* next;

    PolyNode(int c, int p) { coeff = c; pow = p; next = nullptr; }
};

class Polynomial {
public:
    PolyNode* head;

    Polynomial() { head = nullptr; }

    void insert(int c, int p) {
        PolyNode* temp = new PolyNode(c, p);
        if (!head) { head = temp; return; }
        PolyNode* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = temp;
    }

    void compareBilling(Polynomial p2) {
        PolyNode *a = head, *b = p2.head;
        while (a && b) {
            if (a->coeff != b->coeff || a->pow != b->pow) {
                cout << "\nBilling mismatch detected!";
                return;
            }
            a = a->next; b = b->next;
        }
        cout << "\nBilling records match successfully.";
    }
};

/* ---------------- CUSTOMER SUPPORT SYSTEM (MAIN MENU) ---------------- */

int main() {
    TicketList list;
    UndoStack undo;
    PriorityQueue pq;
    CircularQueue cq;

    int choice = 0;
    while (choice != 8) {
        cout << "\n\n----- CUSTOMER SUPPORT SYSTEM MENU -----";
        cout << "\n1. Add Ticket";
        cout << "\n2. Delete Ticket";
        cout << "\n3. Retrieve Ticket";
        cout << "\n4. Undo Last Operation";
        cout << "\n5. Process Priority Ticket";
        cout << "\n6. Round Robin Ticket";
        cout << "\n7. Display Tickets";
        cout << "\n8. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, priority;
            string name, issue;
            cout << "\nEnter Ticket ID: "; cin >> id;
            cout << "Enter Customer Name: "; cin >> name;
            cout << "Enter Issue: "; cin >> issue;
            cout << "Enter Priority (1=Urgent): "; cin >> priority;
            list.insertTicket(id, name, issue, priority);
            undo.push(id);
            cout << "\nTicket Added!";
        }

        else if (choice == 2) {
            int id;
            cout << "\nEnter Ticket ID to Delete: ";
            cin >> id;
            list.deleteTicket(id);
            cout << "\nTicket Deleted!";
        }

        else if (choice == 3) {
            int id;
            cout << "\nEnter Ticket ID to Retrieve: ";
            cin >> id;
            list.retrieveTicket(id);
        }

        else if (choice == 4) {
            if (!undo.isEmpty()) {
                int last = undo.pop();
                list.deleteTicket(last);
                cout << "\nUndo Successful!";
            } else {
                cout << "\nNothing to Undo!";
            }
        }

        else if (choice == 5) {
            if (!pq.isEmpty()) {
                cout << "\nPriority Ticket Processed: " << pq.dequeue()->CustomerName;
            } else {
                cout << "\nNo tickets in priority queue!";
            }
        }

        else if (choice == 6) {
            if (!cq.isEmpty()) {
                cout << "\nRound Robin Ticket: " << cq.dequeue()->CustomerName;
            } else {
                cout << "\nRound robin queue empty!";
            }
        }

        else if (choice == 7) {
            list.display();
        }

        else if (choice == 8) {
            cout << "\nExiting system...";
        }

        else {
            cout << "\nInvalid choice!";
        }
    }
    return 0;
}
