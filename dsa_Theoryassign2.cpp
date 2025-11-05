#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/* ---------------- PATIENT LINKED LIST NODE ---------------- */
class Patient {
public:
    int PatientID;
    string PatientName;
    string AdmissionDate;
    string TreatmentDetails;
    int Priority;
    Patient* next;

    Patient(int id, string name, string date, string details, int p) {
        PatientID = id;
        PatientName = name;
        AdmissionDate = date;
        TreatmentDetails = details;
        Priority = p;
        next = nullptr;
    }
};

/* ---------------- LINKED LIST ---------------- */
class LinkedList {
public:
    Patient* head;

    LinkedList() { head = nullptr; }

    void insertPatient(int id, string name, string date, string details, int p) {
        Patient* temp = new Patient(id, name, date, details, p);
        if (!head) { head = temp; return; }
        Patient* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = temp;
    }

    void deletePatient(int id) {
        if (!head) return;
        if (head->PatientID == id) {
            Patient* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Patient* curr = head;
        while (curr->next && curr->next->PatientID != id)
            curr = curr->next;

        if (curr->next) {
            Patient* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        }
    }

    void retrievePatient(int id) {
        Patient* curr = head;
        while (curr) {
            if (curr->PatientID == id) {
                cout << "\nPatient Found!";
                cout << "\nID: " << curr->PatientID;
                cout << "\nName: " << curr->PatientName;
                cout << "\nDate: " << curr->AdmissionDate;
                cout << "\nTreatment: " << curr->TreatmentDetails;
                cout << "\nPriority: " << curr->Priority << endl;
                return;
            }
            curr = curr->next;
        }
        cout << "\nPatient Not Found!";
    }

    void display() {
        cout << "\n--- Current Admissions ---\n";
        Patient* curr = head;
        while (curr) {
            cout << curr->PatientID << " | " << curr->PatientName << " | P:" << curr->Priority << endl;
            curr = curr->next;
        }
    }
};

/* ---------------- STACK USING ARRAY (UNDO) ---------------- */
class ArrayStack {
public:
    int top;
    int arr[100];

    ArrayStack() { top = -1; }

    void push(int x) {
        if (top == 99) return;
        arr[++top] = x;
    }

    int pop() {
        if (top == -1) return -1;
        return arr[top--];
    }

    bool isEmpty() { return top == -1; }
};

/* ---------------- CIRCULAR QUEUE USING ARRAY ---------------- */
class ArrayCircularQueue {
public:
    Patient* arr[100];
    int front, rear;

    ArrayCircularQueue() { front = rear = -1; }

    bool isEmpty() { return front == -1; }

    bool isFull() { return (rear + 1) % 100 == front; }

    void enqueue(Patient* p) {
        if (isFull()) return;
        if (front == -1) front = 0;
        rear = (rear + 1) % 100;
        arr[rear] = p;
    }

    Patient* dequeue() {
        if (isEmpty()) return nullptr;
        Patient* temp = arr[front];
        if (front == rear) front = rear = -1;
        else front = (front + 1) % 100;
        return temp;
    }
};

/* ---------------- PRIORITY QUEUE USING ARRAY ---------------- */
class ArrayPriorityQueue {
public:
    Patient* arr[100];
    int size;

    ArrayPriorityQueue() { size = 0; }

    void enqueue(Patient* p) {
        arr[size++] = p;
    }

    Patient* dequeue() {
        if (size == 0) return nullptr;
        int idx = 0;
        for (int i = 1; i < size; i++)
            if (arr[i]->Priority < arr[idx]->Priority)
                idx = i;

        Patient* t = arr[idx];
        for (int i = idx; i < size - 1; i++)
            arr[i] = arr[i + 1];
        size--;
        return t;
    }

    bool isEmpty() { return size == 0; }
};

/* ---------------- POLYNOMIAL LINKED LIST ---------------- */
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

    int evaluate(int x) {
        int sum = 0;
        PolyNode* curr = head;
        while (curr) {
            sum += curr->coeff * pow(x, curr->pow);
            curr = curr->next;
        }
        return sum;
    }
};

/* ---------------- POSTFIX EVALUATION ---------------- */
int evaluatePostfix(string exp) {
    int s[50], top = -1;

    for (char ch : exp) {
        if (isdigit(ch)) s[++top] = ch - '0';
        else {
            int b = s[top--];
            int a = s[top--];
            switch (ch) {
                case '+': s[++top] = a + b; break;
                case '-': s[++top] = a - b; break;
                case '*': s[++top] = a * b; break;
                case '/': s[++top] = a / b; break;
            }
        }
    }
    return s[top];
}

/* ---------------- MAIN MENU ---------------- */
int main() {
    LinkedList list;
    ArrayStack undo;
    ArrayCircularQueue cq;
    ArrayPriorityQueue pq;

    int choice = 0;

    while (choice != 8) {
        cout << "\n=========== HOSPITAL MENU ===========";
        cout << "\n1. Add Patient";
        cout << "\n2. Delete Patient";
        cout << "\n3. Retrieve Patient";
        cout << "\n4. Undo Admission";
        cout << "\n5. Emergency Handling";
        cout << "\n6. Billing Calculation";
        cout << "\n7. Inventory Calculation";
        cout << "\n8. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, p;
            string name, date, details;

            cout << "\nID: "; cin >> id;
            cout << "Name: "; cin >> name;
            cout << "Date(dd/mm/yyyy): "; cin >> date;
            cout << "Treatment: "; cin >> details;
            cout << "Priority (1=Emergency): "; cin >> p;

            list.insertPatient(id, name, date, details, p);
            undo.push(id);
            pq.enqueue(new Patient(id, name, date, details, p));
            cq.enqueue(new Patient(id, name, date, details, p));

            cout << "\nPatient Added!\n";
        }

        else if (choice == 2) {
            int id;
            cout << "\nEnter ID: ";
            cin >> id;
            list.deletePatient(id);
            cout << "\nPatient Removed!";
        }

        else if (choice == 3) {
            int id;
            cout << "\nEnter ID: ";
            cin >> id;
            list.retrievePatient(id);
        }

        else if (choice == 4) {
            if (!undo.isEmpty()) {
                int last = undo.pop();
                list.deletePatient(last);
                cout << "\nUndo Successful!";
            } else cout << "\nNothing to Undo!";
        }

        else if (choice == 5) {
            if (!pq.isEmpty()) {
                Patient* p = pq.dequeue();
                cout << "\nEmergency Patient Served: " << p->PatientName;
            }
        }

        else if (choice == 6) {
            Polynomial b;
            b.insert(3,2);
            b.insert(4,1);
            b.insert(2,0);

            int x;
            cout << "\nEnter Treatment Duration: ";
            cin >> x;
            cout << "\nBilling Total: " << b.evaluate(x);
        }

        else if (choice == 7) {
            string exp;
            cout << "\nEnter Postfix Expression: ";
            cin >> exp;
            cout << "\nInventory Output = " << evaluatePostfix(exp);
        }

        else if (choice == 8) {
            cout << "\nSystem Closed.\n";
        }
    }
    return 0;
}
