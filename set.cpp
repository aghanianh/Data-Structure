#include <iostream>
using namespace std;

struct Node
{
    int info;
    Node* next;
    Node(int _info, Node* _next = nullptr): info(_info), next(_next) {}
};
class Set   
{
    public:   
        Set();
        ~Set();
        Set(const Set&);
        Set(int*, int);
        Set& operator=(const Set&);   
        void insert(int); 
        bool is_contain(int) const;
        int count_after_item(int) const;
        Set cross(const Set&);
        void echo() const;
    private:
        Node* head;
        Node* tail;
        void clear();
};
Set Set:: cross(const Set& other)
{
    Set result;
    if(!other.head || !head)
    {
        return result;
    }

    Node* this_tmp = head;
    Node* other_tmp = other.head;
    Node* curr = nullptr;
    while(this_tmp != nullptr && other_tmp != nullptr)
    {
        if(this_tmp -> info < other_tmp -> info)
        {
            this_tmp = this_tmp -> next;
        }
        else if(this_tmp -> info > other_tmp -> info)
        {
            other_tmp = other_tmp -> next;
        }
        else
        {
            if(curr == nullptr)
            {
                result.head = new Node(this_tmp -> info);
                curr = result.head;
            }
            else
            {
                curr -> next = new Node(this_tmp -> info);
                curr = curr -> next;
                result.tail = curr;
            }
        
            this_tmp = this_tmp -> next;
            other_tmp = other_tmp -> next;
        }
    }
    return result;
}
Set::~Set()
{
    clear();
}
int Set::count_after_item(int item) const
{
    if(!is_contain(item) || head == nullptr)
    {
        return -1;
    }
    int count = 0;
    Node* tmp = head;
    while(tmp != nullptr)
    {
        if(tmp -> info > item)
        {
            count ++;
        }
        tmp = tmp -> next;
    }
    return count;
}
Set& Set:: operator=(const Set& other)
{
    if(this == &other)
    {
        return *this;
    }
    if(other.head != nullptr)
    {
        clear();
        head = new Node(other.head -> info);
        Node* this_tmp = head;
        Node* other_tmp = other.head -> next;
        while(other_tmp != nullptr)
        {
            this_tmp -> next = new Node(other_tmp->info);
            this_tmp = this_tmp -> next;
            other_tmp = other_tmp -> next;
        }
        tail = this_tmp;
    }
    return *this;
}
void Set::clear()
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
    tail = nullptr;
}
Set::Set()
{
    head = tail = nullptr;
}
bool Set::is_contain(int item) const 
{
    if(head == nullptr)
    {
        return false;
    }
    Node* tmp = head;
    while(tmp != nullptr)
    {
        if(tmp->info == item)
        {
            return true;
        }
        tmp = tmp -> next;
    }
    return false;
}
void Set::insert(int item)
{
    if(head == nullptr)
    {
        head = tail = new Node(item);
    }
    else if(head != nullptr && head->info > item)
    {
        Node* tmp = new Node(item);
        tmp->next = head;
        head = tmp;
    }
    else
    {
        if(!is_contain(item))
        {
            Node* tmp = head;
            while(tmp -> next != nullptr && tmp -> next -> info < item)
            {
                tmp = tmp -> next;
            }
            Node* new_inserted = new Node(item);
            new_inserted -> next = tmp -> next;
            tmp -> next = new_inserted;
            if(new_inserted -> next == nullptr)
            {
                tail = new_inserted;
            }
        }
        else
        {
            return;
        }
    }
    
}
Set::Set(const Set& other)
{
    if(other.head == nullptr)
    {
        head = tail = nullptr;
        return;
    }
    head = new Node(other.head -> info);
    Node* this_tmp = head;
    tail = this_tmp;
    if(other.head -> next)
    {
        Node* other_tmp = other.head -> next;
        while(other_tmp)
        {
            this_tmp -> next = new Node(other_tmp -> info);
            this_tmp = this_tmp -> next;
            other_tmp = other_tmp -> next;
        }
        tail = this_tmp;
    }
}
Set::Set(int* arr, int n) {
    head = tail = nullptr;
    if (arr == nullptr || n < 0) {
        return;
    }
    int* uniq_arr = new int[n];
    int counter = 0;

    for (int i = 0; i < n; i++) 
    {
        bool is_uniq = true;
        for (int j = 0; j < counter; j++) 
        {
            if (uniq_arr[j] == arr[i]) 
            {
                is_uniq = false;
                break;
            }
        }
        if (is_uniq) 
        {
            uniq_arr[counter++] = arr[i];
        }
    }
    head = new Node(uniq_arr[0]);
    Node* tmp = head;
    for (int i = 1; i < counter; i++) 
    {
        tmp->next = new Node(uniq_arr[i]);
        tmp = tmp->next;
    }
    tail = tmp;
    tail->next = nullptr;
    delete[] uniq_arr;
}

void Set:: echo() const
{
    if(head == nullptr)
        {
            cout << "empty Set" << endl;
            return;
        }
    Node* tmp = head;
    while(tmp != nullptr)
    {
        cout << tmp -> info << " ";
        tmp = tmp -> next;
    }
    cout << endl;
}

int main()
{
    Set s1;
    s1.echo();
    s1.insert(5);
    s1.insert(1);
    s1.insert(6);
    s1.insert(5);
    s1.insert(4);
    s1.echo();
    
    const int n = 10;
    int arr[n] = {1,1,2,2,3,3,4,4,5,5};
    Set s2(arr, n);
    s2.echo();

    Set s3(s2);
    s3.echo();

    Set s4 = s1.cross(s2);
    s4.echo();
}
