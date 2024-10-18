//
//  main.cpp
//  Midterm Exam 2
//
//  Created by Xiao Zhang on 10/18/24.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        string name;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr)
            : name(val), prev(p), next(n) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void push_back(const string& name) { // Add a person to the back of the line
        Node* newNode = new Node(name);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void pop_front() { // Remove the person at the front of the line
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
    }

    void pop_back() { // Remove the person at the back of the line
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
    }

    void push_front(const string& name) {  // Add a VIP person to the front of the line
        Node* newNode = new Node(name);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void remove(const string& name) {// Remove a specific person by name
            Node* temp = head;
            while (temp && temp->name != name) {
                temp = temp->next;
            }
            if (!temp) return;
            if (temp->prev) temp->prev->next = temp->next;
            else head = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            else tail = temp->prev;
            delete temp;
        }

        bool empty() const { //see if the line is empty
            return head == nullptr;
        }

        string front() const {// Get the name of the person at the front
            if (head) return head->name;
            return "";
        }

        string back() const {// Get the name of the person at the back
            if (tail) return tail->name;
            return "";
        }

        void print() const {// Print the current line
            Node* temp = head;
            while (temp) {
                cout << "\n" << temp->name;
                temp = temp->next;
            }
            cout << endl;
        }
    };

    
void load_names(string names[], int& size) {
        ifstream file("names.txt");
        size = 0;
        while (file >> names[size]) {
            size++;
        }
        file.close();
    }



void simulate_coffee_shop() { // Simulate the coffee shop operations for 20 minutes
    DoublyLinkedList line;
    string names[100];
    int nameCount;
    load_names(names, nameCount);  // Load available names
    
    // Add 5 customers to the line
    cout << "Store opens:\n";
    for (int i = 0; i < 5; ++i) {
        string customer = names[rand() % nameCount];
        cout << customer << " joins the line\n";
        line.push_back(customer);
    }
    cout << "Resulting line: ";
    line.print();
    
    for (int minute = 1; minute <= 20; ++minute) { // Run  20 minutes
        cout << "\nTime step #" << minute << ":\n";

        // 40% chance a customer is served
        if (rand() % 100 < 40 && !line.empty()) {
            cout << line.front() << " is served\n";
            line.pop_front();
        }

        // 60% chance a new customer joins the line
        if (rand() % 100 < 60) {
            string customer = names[rand() % nameCount];
            cout << customer << " joins the line\n";
            line.push_back(customer);
        }

        // 20% chance the last customer leaves
        if (rand() % 100 < 20 && !line.empty()) {
            cout << line.back() << " (at the rear) left the line\n";
            line.pop_back();
        }

        // 10% chance any random customer leaves
        if (rand() % 100 < 10 && !line.empty()) {
            string randomCustomer = names[rand() % nameCount];
            cout << randomCustomer << " left the line\n";
            line.remove(randomCustomer);
        }

        // 10% chance a VIP customer joins the front
        if (rand() % 100 < 10) {
            string vipCustomer = names[rand() % nameCount];
            cout << vipCustomer << " (VIP) joins the front of the line\n";
            line.push_front(vipCustomer);
        }
        
        cout << "Resulting line: ";
        line.print();//print the current line
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    simulate_coffee_shop();
    return 0;
}
    
