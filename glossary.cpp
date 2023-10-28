#include <iostream>
#include <cstring>
using namespace std;

struct Node
{
    char* str;
    Node* next;
    Node(const char* str_copied, Node* next_copied = nullptr)
    {
        str = new char[strlen(str_copied) + 1];
        strcpy(str, str_copied);
        next = next_copied;
    }
};

class Glossary
{
    public:
        Glossary(); 
        Glossary(const Glossary&);
        Glossary& operator=(const Glossary&);
        ~Glossary();
        void add_string(const char*);
        void echo() const;
        bool is_ordered() const;
        Glossary unit(const Glossary&);
        void make_ordered();
    private:
        Node* head; 
        Node* tail;
        void clear();
};
Glossary Glossary::unit(const Glossary& other)
{
    Glossary result;
    Node* this_curr = head;
    Node* other_curr = other.head;

    if(!head && !other.head)
    {
        return result;
    }
    if(head && !other.head)
    {
        return *this;
    }
    if(!head && other.head)
    {
        return other;
    }
    //creating first element of result;
    if(strcmp(this_curr -> str, other_curr -> str) > 0)
    {
        result.head = new Node(other_curr -> str);
        other_curr = other_curr -> next;
        result.tail = result.head;
    }
    else if(strcmp(this_curr -> str, other_curr -> str) < 0)
    {
        result.head = new Node(this_curr -> str);
        this_curr = this_curr -> next;
        result.tail = result.head;
    }
    else if(strcmp(this_curr -> str, other_curr -> str) == 0)
    {
        result.head = new Node(this_curr -> str);
        this_curr = this_curr -> next;
        other_curr = other_curr -> next;
        result.tail = result.head;
    }
    /////////////////////////////
    while(this_curr != nullptr && other_curr != nullptr)
    {
        if(strcmp(this_curr -> str, other_curr -> str) > 0)
        {
            result.tail->next = new Node(other_curr -> str);
            other_curr = other_curr -> next;
            result.tail = result.tail -> next;
        }
        else if(strcmp(this_curr -> str, other_curr -> str) < 0)
        {
            result.tail -> next = new Node(this_curr -> str);
            this_curr = this_curr -> next;
            result.tail = result.tail -> next;
        }
        else
        {
            result.tail -> next = new Node(this_curr -> str);
            this_curr = this_curr -> next;
            other_curr = other_curr -> next;
            result.tail = result.tail -> next;
        }
    }
    while(this_curr)
    {
        result.tail -> next = new Node(this_curr -> str);
        this_curr = this_curr -> next;
        result.tail = result.tail -> next;
    }
    while(other_curr)
    {
        result.tail -> next = new Node(other_curr -> str);
        other_curr = other_curr -> next;
        result.tail = result.tail -> next;
    }
    return result;
}
void Glossary::make_ordered()
{
    if(head == nullptr || head -> next == nullptr)
    {
        return; // The glossary already sorted
    }
    Node* first_tmp = head;
    Node* second_tmp;
    while(first_tmp)
    {
        second_tmp = first_tmp -> next;
        while(second_tmp)
        {
            if(strcmp(first_tmp->str, second_tmp->str) > 0)
            {
                char* tmp = first_tmp -> str;
                first_tmp -> str = second_tmp -> str;
                second_tmp -> str = tmp;
            }
            second_tmp = second_tmp -> next;
        }
        first_tmp = first_tmp -> next;
    }
}
bool Glossary::isordered() const
{
    Node* tmp = head;
    while(tmp != nullptr && tmp -> next != nullptr)
    {
        if(strcmp(tmp -> str, tmp -> next -> str) > 0)
            return false;
        tmp = tmp -> next;
    }
    return true;
}
Glossary::Glossary()
{
    head = tail = nullptr;
}
Glossary::Glossary(const Glossary& other)
{
    head = tail = nullptr;
    if(other.head == nullptr)
    {
        return;
    }
    head = new Node(other.head->str);
    Node* tmp = head;
    Node* other_tmp = other.head->next;
    while(other_tmp != nullptr)
    {
        Node* current = new Node(other_tmp->str);
        tmp->next = current;
        other_tmp = other_tmp -> next;
        tmp = tmp -> next;
    }
    tail = tmp;
    tail -> next = nullptr;
}
Glossary::~Glossary()
{
    clear();

}
void Glossary:: clear()
{
    while(head != nullptr)
    {
        Node* tmp = head ;
        head = head -> next;
        delete tmp;
    }
    tail = nullptr;
}   
Glossary& Glossary::operator=(const Glossary& other)
{
    
    if(this == &other)
    {
        return *this; 
    }
    clear();
    if(other.head != nullptr)
    {
        head = new Node(other.head->str);
        Node* tmp = head;
        Node* other_tmp = other.head->next;
        while(other_tmp != nullptr)
        {
            Node* copied_node = new Node(other_tmp->str);
            tmp -> next = copied_node;
            other_tmp = other_tmp -> next;
            tmp = tmp -> next;
        }
        tail = tmp;
        tail-> next = nullptr;
    }
    return *this;
}
void Glossary:: echo() const
{
    Node* curr = head;
    if(head == nullptr)
    {
        cout << "NONE" << endl;
        return;
    }
    while(curr != nullptr)
    {
        cout << curr->str << " ";
        curr = curr -> next;
    }
    cout << endl;
}
void Glossary:: add_string(const char* sequence)
{
    Node* add_node = new Node(sequence);
    if(head == nullptr)
    {
        head = tail = add_node;
        return;
    }
    tail -> next = add_node;
    tail = add_node;
}
int main()
{
    Glossary g1,g2;
    
    g1.add_string("hello");
    g1.add_string("world");
    g1.echo();

    g2.add_string("Varuzhan");
    g2.add_string("Aghanyan");
    g2.echo();
    
    Glossary g3 = g1.unit(g2);
    g3.echo();
    
    Glossary g4 ;
    g4.add_string("Work");
    g4.add_string("Hard");
    g4.echo();

    Glossary g5;
    g5 = g4.unit(g2);
    g5.echo();
    
    Glossary g6;
    g6.add_string("Varuzhan");
    g6.add_string("Aghanyan");
    g6.make_ordered();
    g6.echo();
}

