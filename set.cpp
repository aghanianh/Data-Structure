#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node* next;
    Node(int d, Node* p = nullptr):data(d), next(p){}
};
class Set
{
    public:
        Set();
        Set(int* , int);
        Set(const Set&);
        ~Set();
        void clear();
        void add_element(int);
        void echo();
        Set operator+(const Set&);
    private:
        Node* head;
        Node* tail;
        void sort();
        void remove_duplicates();
};
void Set::remove_duplicates() {
    if (!head || !head->next) {
        return; // No duplicates to remove
    }

    Node* current = head;
    while (current) {
        Node* nextNode = current;
        while (nextNode->next) {
            if (current->data == nextNode->next->data) {
                Node* duplicate = nextNode->next;
                nextNode->next = nextNode->next->next;
                delete duplicate;
            } else {
                nextNode = nextNode->next;
            }
        }
        current = current->next;
    }
}
void Set::clear()
{
    Node* tmp = head;
    while(tmp != nullptr)
    {
        tmp = tmp -> next;
        delete head;
        head = tmp;
    }
}
Set::~Set()
{
    clear();
}
void Set::sort() {
    if (!head || !head->next) {
        return; // The list is already sorted
    }

    Node* current = head;
    while (current) {
        Node* nextNode = current->next;
        while (nextNode) {
            if (current->data > nextNode->data) {
                int temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }
    remove_duplicates();
}    
Set::Set()
{
    head = tail = nullptr;
}
Set::Set(int* arr, int n)
{
    if(arr != nullptr)
    {
        Node* nodeik = new Node(arr[0]);
        head = tail = nodeik;
        for(int i = 1; i < n; i++)
        {
            Node* tmp = new Node(arr[i]);
            tail -> next = tmp;
            tail = tmp;  
        }
        sort();
    }
}
Set::Set(const Set& other)
{
    if(other.head != nullptr)
    {
        Node* nodeik = new Node(other.head -> data);
        head = tail = nodeik;
        Node* tmp = head;
        Node* otmp = other.head->next;
        while(otmp != nullptr)
        {
            Node* new_node = new Node(otmp -> data);
            tail-> next = new_node;
            tail = new_node;
            otmp = otmp -> next;
        }
    }
}
void Set::add_element(int item)
{
    if(head == nullptr)
    {
        Node* new_node = new Node(item);
        head = tail = new_node;
        return;
    }
    if(head -> data == item)
    {
        return;
    }
    if(item < head-> data)
    {
        Node* new_node = new Node(item, head);
        head = new_node;
        return;
    }
    Node* new_node = new Node(item);
    Node* tmp = head;
    while(tmp-> next != nullptr)
    {
        if(tmp->next->data == item)
        {
            return;
        }
        if(tmp -> next -> data > item)
        {
            break;
        }
    tmp = tmp -> next;
    }
    tmp -> next = new_node;
    new_node -> next = tmp -> next -> next;
    if(new_node->next == nullptr)
    {
        tail = new_node;
    }
}
void Set:: echo()
{
    Node* tmp = head;
    while(tmp != nullptr)
    {
        std::cout << tmp -> data << " ";
        tmp = tmp -> next;
    }
    std::cout << std:: endl;
}
Set Set::operator+(const Set& other) {
    Set result(*this); // Create a copy of the current Set

    Node* otherCurrent = other.head;
    while (otherCurrent) {
        result.add_element(otherCurrent->data);
        otherCurrent = otherCurrent->next;
    }
    result.sort();
    return result;
}


int main()
{
    Set s1;
    s1.add_element(5);
    s1.add_element(4);
    s1.add_element(3);
    s1.add_element(2);
    s1.add_element(1);
    s1.echo();
    Set s2(s1);
    s2.echo();
    int arr[10] = {1,1,2,2,4,4,5,5,6,6};
    Set s3(arr, 10);
    s3.echo();
    Set s4;
    s4 = s1 + s3;
    s4.echo();

}
