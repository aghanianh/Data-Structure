#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node* next;
    Node(int data = 0):data(data), next(nullptr){}
    Node(int data, Node* next): data(data), next(next){}
};

class mqueue
{
    public:
        mqueue()
        {
            tail = nullptr;
            head = nullptr;
        }
        void enmqueue(int value)
        {
            Node* new_node = new Node(value);
            if (head == nullptr)
            {
                head = new_node;
                tail = new_node;
                return;
            }
            new_node->next = tail;
            tail = new_node;
        }
        void demqueue()
        {
            head-> next = nullptr;
        }
        void echo()
        {
            Node* tmp = tail;
            while(tmp != nullptr)
            {
                cout<<tmp->data<<" ";
                tmp = tmp->next;
            }
        
        }
    



    private:
        Node* tail;
        Node* head;
};
int main()
{
    mqueue mq;
    mq.enmqueue(4);
    mq.enmqueue(6);
    mq.demqueue();
    mq.echo();
}
