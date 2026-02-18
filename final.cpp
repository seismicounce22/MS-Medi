#include <iostream>
#include <string>
using namespace std;

class Medicine {
public:
    int id;
    string name;
    int quantity;
    float price;
    Medicine* next;

    Medicine(int i, string n, int q, float p) {
        id = i;
		name = n;
		quantity = q;
		price = p;
		 next = NULL;
    }
};

class Inventory {
private:
    Medicine* head;
public:
    Inventory() {
	 head = NULL;
	 }

    void addMedicine() {
        int id, qty;
        string name;
        float price;

        cout << "Enter ID of medicine: "<<endl;
		cin >> id;
        cout << "Enter Name: "<<endl;
		 cin >> name;
        cout << "Enter Quantity: "<<endl;
		 cin >> qty;
        cout << "Enter Price: "<<endl;
		 cin >> price;

        Medicine* newMed = new Medicine(id, name, qty, price);
        newMed->next = head;
        head = newMed;

        sortInventory();
        cout << "Medicine added successfully."<<endl;
    }

    Medicine* searchMedicine(int id) {
        Medicine* temp = head;
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->next;
        }
        return NULL;
    }

    void sortInventory() {
        if (!head || !head->next) return;

        Medicine* sorted = NULL;
        Medicine* curr = head;

        while (curr) {
            Medicine* nextNode = curr->next;
            if (!sorted || curr->id < sorted->id) {
                curr->next = sorted;
                sorted = curr;
            } else {
                Medicine* temp = sorted;
                while (temp->next && temp->next->id < curr->id)
                    temp = temp->next;
                curr->next = temp->next;
                temp->next = curr;
            }
            curr = nextNode;
        }
        head = sorted;
    }

    void displayInventory() {
        if (!head) {
            cout << "Inventory empty!"<<endl;
            return;
        }
        cout << "following is the Inventory of MS MEDI "<<endl;
        Medicine* temp = head;
        while (temp) {
            cout << "ID: " << temp->id<<endl;
               cout  << ", Name: " << temp->name<<endl;
               cout  << ", Qty: " << temp->quantity<<endl;
                cout<< ", Price: " << temp->price << endl;
            temp = temp->next;
        }
    }

    void updateMedicine() {
        int id;
        cout << "Enter ID to update the medicine: "; cin >> id;
        Medicine* med = searchMedicine(id);
        if (!med) {
            cout << "Medicine not found!"<<endl;
            return;
        }
        cout << "Enter new Name: "<<endl;
		 cin >> med->name;
        cout << "Enter new Quantity: "<<endl;
		 cin >> med->quantity;
        cout << "Enter new Price: "<<endl;
		 cin >> med->price;

        sortInventory();
        cout << "Medicine updated successfully."<<endl;
    }

    void deleteMedicine() {
        int id;
        cout << "Enter ID to delete: "<<endl;
		 cin >> id;
        Medicine* temp = head;
        Medicine* prev = NULL;

        while (temp && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            cout << "Medicine not found!"<<endl;
            return;
        }

        if (!prev) head = temp->next;
        else prev->next = temp->next;

        delete temp;
        cout << "Medicine deleted successfully."<<endl;
    }

    bool reduceStock(int id, int qty) {
        Medicine* med = searchMedicine(id);
        if (!med) return false;
        if (med->quantity < qty) return false;

        med->quantity -= qty;
        return true;
    }
};

class SalesStack {
private:
    class Node {
    public:
        int id;
        int qty;
        float price;
        Node* next;
        Node(int i, int q, float p) {
            id = i;
            qty = q;
            price = p;
            next = NULL;
        }
    };

    Node* top;

public:
    SalesStack() { top = NULL; }

    void push(int id, int qty, float price) {
        Node* newNode = new Node(id, qty, price);
        newNode->next = top;
        top = newNode;
    }

    void display() {
        if (top == NULL) {
            cout << "No sales yet! Try after some sales." << endl;
            return;
        }
        cout << "Recent Sales of MS MEDI are as follows:" << endl;
        Node* temp = top;
        while (temp != NULL) {
            cout << "ID: " << temp->id << endl;
            cout << "Qty: " << temp->qty << endl;
            cout << "Price: " << temp->price << endl;
            temp = temp->next;
        }
    }

    int pop() { 
        if (top == NULL) return -1;
        Node* temp = top;
        int val = top->id;
        top = top->next;
        delete temp;
        return val;
    }
};



class Queue {
private:
    class Node {
    public:
        int data;
        Node* next;
        Node(int val) { data = val; next = NULL; }
    };

    Node* front;
    Node* rear;

public:
    Queue() { front = rear = NULL; }

    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (rear == NULL) {
		// empty queue
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    int dequeue() {
        if (front == NULL) return -1;
		 // empty queue
        int val = front->data;
        Node* temp = front;
        front = front->next;
        if (front == NULL) rear = NULL;
        delete temp;
        return val;
    }

    void display() {
        if (front == NULL) {
            cout << "Queue is empty!"<<endl;
            return;
        }
        Node* temp = front;
        cout << "Queue Contents (FIFO) "<<endl;
        while (temp != NULL) {
            cout << temp->data << " "<<endl;
            temp = temp->next;
        }
        cout << endl;
    }
};



//   MAIN — CLI SYSTEM//
  
int main() {
    Inventory inventory;
    SalesStack sales;
    Queue issue;

    int choice;
    do {
        cout << "\n====================================\n";
        cout << "   PHARMACY INVENTORY SYSTEM"<<endl;
        cout << "====================================\n";
        cout<<"WELCOME to MS MEDI Pharmacy.Please Choose the Choice you want to perform"<<endl;

       cout << "1. Add Medicine" << endl;
       cout << "2. Search Medicine" << endl;
       cout<<"3. Display Medicine"<<endl;
        cout << "4. Sell Medicine" << endl;
        cout << "5. Update Medicine" << endl;
        cout << "6. Delete Medicine" << endl;
        cout << "7. View Recent Sales" << endl;
        cout << "8. View Issue Queue" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter Choice: "<<endl;
        cin >> choice;

        switch(choice) {
            case 1: inventory.addMedicine(); break;
            case 2: {
                int id; cout << "Enter ID to search: "<<endl;
				 cin >> id;
                Medicine* med = inventory.searchMedicine(id);
                if (med) cout << "Medicine Found: " << med->name << endl;
                else cout << "Medicine not found!"<<endl;
                break;
            }
            case 3: inventory.displayInventory(); break;
            case 4: {
                int id, qty;
                cout << "Enter Medicine ID to sell: "<<endl;
				 cin >> id;
                cout << "Enter Quantity: "<<endl;;
				 cin >> qty;
                Medicine* med = inventory.searchMedicine(id);
                if (!med) {
				cout << "Medicine not found!"<<endl;
				 break;
				  }
                if (!inventory.reduceStock(id, qty)) {
                    cout << "Not enough stock!"<<endl;
					 break;
                }
                sales.push(id, qty, med->price);
                issue.enqueue(id);
                cout << "Medicine sold successfully!"<<endl;
                break;
            }
            case 5: inventory.updateMedicine(); break;
            case 6: inventory.deleteMedicine(); break;
            case 7: sales.display();
			 break;
            case 8: issue.display(); break;
            case 0: cout << "Exiting..."<<endl; break;
            default: cout << "Invalid choice!"<<endl;
        }
    } while(choice != 0);

    cout << "Thank You for Using MS MEDI Pharmacy System!"<<endl;
    return 0;
}

