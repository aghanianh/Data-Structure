#include <iostream>
using namespace std;

struct Node
{
    int info;
    Node* next;
    Node* prev;
    Node(int _info, Node* _next = nullptr, Node* _prev = nullptr)
    {
        info = _info;
        next = _next;
        prev = _prev;
    }
};

class int_sequence
{
    public:
        int_sequence();
        int_sequence(int*,int);
        ~int_sequence();
        int_sequence(const int_sequence&);
        int_sequence& operator=(const int_sequence&);
        int get_divs_k(int) const;
        void insert_end(int);
        void insert_front(int);
        int get_size() const;
        void remove_duplicates();
        void echo() const;
    private:
        Node* head;
        Node* tail;
        int size;
        void clear();
};
void int_sequence::echo() const
{
    Node* tmp = head;
    while(tmp != nullptr)
    {
        cout << tmp -> info << " ";
        tmp = tmp -> next;
    }
    cout << endl;

}
void int_sequence:: remove_duplicates()
{
    if(head == nullptr || head->next == nullptr)
    {
        return;
    }
    Node* tmp = head;
    while(tmp != nullptr)
    {
        Node* fast_tmp = tmp -> next;
        while(fast_tmp != nullptr)
        {   
            if(tmp -> info == fast_tmp -> info)
            {
                Node* del_fast = fast_tmp;
                fast_tmp = fast_tmp -> next;
                if(del_fast -> prev)
                {
                    del_fast -> prev -> next = del_fast -> next;
                }
                else
                {
                    head = del_fast -> next;    
                
                }
                if(del_fast -> next)
                {
                    del_fast -> next -> prev = del_fast -> prev;
                }
                delete del_fast;
                size --;
            }
            else
            {
                fast_tmp = fast_tmp -> next;
            }
        }
        tmp = tmp -> next;
    }
}
int int_sequence:: get_divs_k(int k ) const //3-6-9-12 ...
{
    if(head==nullptr || head -> next == nullptr)
    {
        return -1;
    }
    if(k > get_size())
    {
        return -1;
    }
    int sum = 0;
    int count = 0;
    Node* tmp = head;
    for(int i = 0; i < get_size(); i++)
    {
        if(i % k == 0 )
        {
            sum += tmp -> info;
            count++;
        }
        if(tmp == nullptr)
        {
            return (sum/count);
        }
        else
        {
            tmp = tmp -> next;
        }
        
    }
    return sum / count;
}
int int_sequence:: get_size() const
{
    return size;
}
int_sequence::int_sequence(const int_sequence& other)
{   size = 0;
    if(other.head != nullptr)
    {
        head = tail = nullptr;
        Node* new_item = new Node(other.head -> info);
        head = new_item;
        size ++;
        Node* tmp = head;
        Node* other_tmp = other.head->next;
        while(other_tmp != nullptr)
        {
            Node* ins_node = new Node(other_tmp->info);
            tmp -> next = ins_node;
            ins_node -> prev = tmp;
            tmp = tmp -> next;
            other_tmp = other_tmp -> next;
            size ++;
        }
        tail = tmp;
        tail -> next = nullptr; 
    }
    else
    {
        head = tail = nullptr;
    }    
}

void int_sequence::insert_front(int item)
{
    if(head == nullptr)
    {
        head = tail = new Node(item);
    }
    Node* new_item = new Node(item);
    new_item -> next = head;
    head -> prev = new_item;
    head = new_item;
    size ++;
}
void int_sequence::insert_end(int item)
{
    if(head == nullptr)
    {
        head = tail = new Node(item);
        return;
    }
    Node* new_item = new Node(item);
    tail-> next = new_item;
    new_item -> prev = tail;
    tail = new_item;
    size ++;
} 
int_sequence:: int_sequence()
{
    size = 0;
    head = tail = nullptr;
}
int_sequence::int_sequence(int*arr, int n)
{
    size = 0;
    head = tail = nullptr;
    if(arr == nullptr)
    {
        return;
    }
    head = new Node(arr[0]);
    size++;
    Node* tmp = head;
    for(int i = 1; i < n; i++)
    {
        Node* new_node = new Node(arr[i]);
        new_node -> prev = tmp;
        tmp -> next = new_node;
        tmp = tmp -> next;
        tail = new_node;
        size ++;
    }
}
void int_sequence::clear()
{
    if(head == nullptr)
    {
        return;
    }
    Node* tmp = head;
    while(tmp)
    {
        Node* curr = tmp;
        tmp = tmp -> next;
        delete curr;
    }
    size = 0;
    head = tail = nullptr;
}
int_sequence::~int_sequence()
{
    clear();
}

int main()
{
    int_sequence seq1;
    for(int i = 0; i < 12; i++)
    {
        seq1.insert_end(i);
        seq1.insert_end(i + 1);
    }    
    seq1.echo();
    seq1.remove_duplicates();
    seq1.echo();
    cout << seq1.get_divs_k(2) << endl;//print 2.NODE 4.NODE 6.NODE ...
    int_sequence seq2(seq1);
    seq2.echo();
    return 0;
}

