#include <iostream>
using namespace std;
struct Node
{
    char info;
    Node* next;
    Node* prev;
    Node(char _info, Node* _next = nullptr, Node* _prev = nullptr)
    {
        info = _info;
        next = _next;
        prev = _prev;
    }
};
class String
{
    public:
        String();
        String(const char*);
        String(const String&);
        ~String();
        String& operator=(const String&);
        void reverse();
        void echo() const;
        void add_$();
    private:
        Node* tail;
        Node* head;
        void clear();
        bool is_all_digit() const;
};
void String::add_$() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node* current = head->next;

    while (current != nullptr) 
    {
        bool flag = true;
        Node* fast_tmp = current;
        while(fast_tmp != nullptr)
        {
            if((!(fast_tmp->info >= '0' && fast_tmp->info <= '9')) && fast_tmp -> info != ' ')
            {
                flag = false;
            }
            if(fast_tmp -> info == ' ')
            {
                break;
            }
            fast_tmp = fast_tmp -> next;
        }
        if(flag)
        {
            Node* add_node = new Node('$');
            add_node -> next = current;
            add_node -> prev = current -> prev;
            if(current -> prev != nullptr)
            {
                current -> prev -> next = add_node;
            }
            if(current == head -> next)
            {
                head -> next = add_node;
            }
        } 
        if(fast_tmp != nullptr)
        {
            current = fast_tmp -> next;
        }
        else
        {
            break;
        }
    }
}

bool String:: is_all_digit() const
{
    if(head == nullptr || head -> next == nullptr)
    {
        return false;
    }
    Node* tmp = head -> next;
    while(tmp!=nullptr)
    {
            
        if(!(tmp->info >= '0' && tmp -> info <= '9'))
        {
            return false;
        }
        tmp = tmp -> next;
    }
    return true;
}
void String:: echo() const
{
    Node* tmp = head;
    while(tmp!=nullptr)
    {
        cout <<  tmp->info;
        tmp = tmp -> next;
    }
    cout << endl;

}
String::String()
{
    head = tail = new Node('\0');
}
String::String(const char* str)
{
    if(str != nullptr)
    {
        head = new Node('\0');
        head->next = new Node(str[0]);
        Node* tmp = head -> next;
        int counter = 1;
        while(str[counter] != '\0')
        {
            Node* new_node = new Node(str[counter]);
            new_node -> prev = tmp;
            tmp -> next = new_node;
            tmp = tmp -> next;
            counter ++;
        }
        tail = tmp;
        tail -> next = nullptr;
    }
    else
    {
        head = tail = new Node('\0');
    }
}
String::String(const String& other)
{
    if(other.head == nullptr || other.head -> next == nullptr)
    {
        head = tail = new Node('\0');
        return;
    }
    head = tail = new Node('\0');
    head -> next = new Node(other.head -> next -> info);
    Node* tmp = head -> next;
    Node* other_tmp = other.head->next;
    while(other_tmp!=nullptr)
    {
        Node* new_node = new Node(other_tmp -> info);
        new_node -> prev = tmp;
        tmp -> next = new_node;
        tmp = tmp -> next;
        other_tmp = other_tmp -> next;
    }
    tail = tmp;
    tail -> next = nullptr;

}
String::~String()
{
    clear();
}
void String::clear()
{
    if(head == nullptr)
    {
        return;
    }
    while(head != nullptr)
    {
        Node* tmp = head;
        head = head -> next;
        delete tmp;
    }
    tail = tail->next = nullptr;
}
String& String:: operator=(const String& other)
{
    if(this == &other)
    {
        return *this;
    }
    if(other.head == nullptr)
    {
        return *this;
    }
    if(other.head -> next == nullptr)
    {
        head = tail = new Node('\0');
        return *this;
    }
    head = tail = new Node('\0');
    Node* tmp = head;
    Node* other_tmp = other.head->next;
    while(other_tmp != nullptr)
    {
        Node* new_node = new Node(other_tmp->info);
        new_node->prev = tmp;
        tmp -> next = new_node;
        tmp = tmp -> next;
        other_tmp = other_tmp -> next;
    }
    tail = tmp;
    tail -> next = nullptr;
    return *this;
}   
void String:: reverse()
{
    if(head == nullptr || head->next == nullptr || head -> next -> next == nullptr)
    {
        return;
    }
    
    Node* prev = nullptr;
    Node* curr = head;
    Node* next = nullptr;
    while(curr != nullptr)
    {
        next = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

int main()
{
    String s1("Hello world");
    s1.echo();
    s1.reverse();
    s1.echo();

    String s2(s1);
    s2.echo();
    s2.reverse();
    s2.echo();
    s2.add_$();
    s2.echo();

    String s3("123 345 aa45 asdv 1");
    s3.add_$();
    s3.echo();
    s3.reverse();
    s3.echo();
}
