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

