#pragma once
#include <iostream>
#include <cmath>
struct Node {
    int degree;
    int num;
    Node* next;

    Node(int d = 0, int n = 0, Node* next = nullptr) : degree(d), num(n), next(next) {}
};

class Polyndrom {
public:
    Polyndrom();
    ~Polyndrom();
    Polyndrom(const Polyndrom&);
    Polyndrom& operator=(const Polyndrom&);
    Polyndrom operator+(const Polyndrom&);
    void clear();
    void add_element(int data, int degree);
    bool isValid();
    bool isNodeValid(Node* node);
    void echo();
    int getsum(int data);

private:
    Node* head;
};
Polyndrom Polyndrom::operator+ (const Polyndrom& other)
{
  Polyndrom result;
  Node* tmp = head;
  Node* otmp = other.head;
  Node* res = nullptr;

  while (tmp != nullptr) {
    result.add_element(tmp->num, tmp->degree);
    tmp = tmp->next;
  }

  while (otmp != nullptr) {
    result.add_element(otmp->num, otmp->degree);
    otmp = otmp->next;
  }

  res = result.head;
  while (res->next != nullptr && res != nullptr) {
    if (res->degree == res->next->degree) {
      res->num += res->next->num;
      Node* temp = res->next;
      res->next = res->next->next;
      delete temp;
    } else {
      res = res->next;
    }
  }

  return result;
}
int Polyndrom::getsum(int data)
{
    int sum = 0;
    Node* tmp = head;
    while(tmp != nullptr)
    {
        sum += pow(data, tmp->degree);
        tmp = tmp -> next;
    }
    return sum;

}
Polyndrom::Polyndrom() : head(nullptr) {}

Polyndrom::~Polyndrom() {

    clear();
    std::cout<<"Now you have not polndrom :D :D :D" << std:: endl;
}

Polyndrom::Polyndrom(const Polyndrom& other) : head(nullptr) {
    Node* tmp = nullptr;
    Node* otmp = other.head;

    while (otmp != nullptr) {
        Node* new_node = new Node(otmp->degree, otmp->num);
        if (tmp == nullptr) {
            head = new_node;
            tmp = head;
        } else {
            tmp->next = new_node;
            tmp = new_node;
        }
        otmp = otmp->next;
    }
}

void Polyndrom::clear() {
    Node* tmp = head;
    while (tmp != nullptr) {
        Node* curr = tmp->next;
        delete tmp;
        tmp = curr;
    }
    head = nullptr;
}

void Polyndrom::add_element(int data, int degree) {
    Node* new_element = new Node(degree, data);
    if (!isNodeValid(new_element)) {
        return;
    }

    if (head == nullptr) {
        head = new_element;
    } else {
        Node* tmp = head;
        if (degree > tmp->degree) {
            new_element->next = tmp;
            head = new_element;
        } else {
            while (tmp->next != nullptr && tmp->next->degree >= degree) {
                tmp = tmp->next;
            }
            new_element->next = tmp->next;
            tmp->next = new_element;
        }
    }
}

bool Polyndrom::isValid() {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->num == 0) {
            return false;
        }
        curr = curr->next;
    }
    return true;
}

bool Polyndrom::isNodeValid(Node* node) {
    if (node != nullptr) {
        return node->num != 0;
    }
    return false;
}

Polyndrom& Polyndrom::operator=(const Polyndrom& other) {
    if (this == &other) {
        return *this;
    }

    clear();
    Node* tmp = nullptr;
    Node* otmp = other.head;

    while (otmp != nullptr) {
        Node* new_node = new Node(otmp->degree, otmp->num);
        if (tmp == nullptr) {
            head = new_node;
            tmp = head;
        } else {
            tmp->next = new_node;
            tmp = new_node;
        }
        otmp = otmp->next;
    }
    return *this;
}
void Polyndrom:: echo()
{
    Node* tmp = head;
    while(tmp != nullptr)
    {
        std::cout << tmp->num << "x^" << tmp -> degree ;
        tmp = tmp -> next;
        if(tmp != nullptr)
        {
            std::cout << " + ";
        }
    }
    std:: cout << '\n';
}

