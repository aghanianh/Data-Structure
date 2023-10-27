#include <iostream>
#include <cstring>
using namespace std;
struct Node
{
    char info;
    Node* next;
    Node(char info, Node* next = nullptr): info(info), next(next) {}
};
class String
{
    public:
        String(); //Ctor without argument
        String(const String&); //Copy ctor
        String(const char*); //Ctor with string became String :D
        ~String(); //Dtor
        String& operator=(const String&); 
        void echo() const;     //Printing
        void extend_with(int);      //If passing value is greater than size, will  extend with '!', else will delete Nodes;
        int  get_size() const;      // return size of String
        Node* search_str(const char*) const;     //Search string and returns address of first Node;
        bool String:: is_char_in_string(char) const;
    private:
        Node* head;
        Node* tail;
        void clear();  //For deleting Node
        int size;    
};
bool String:: is_char_in_string(char c) const
{
    Node* tmp = head;
    bool flag = false;
    while(tmp != nullptr)
        {
            if(tmp -> info == c)
            {
                flag = true;
                break;
            }
            tmp = tmp -> next;
        }
    return flag;
    
}
Node* String:: search_str(const char* str)
{
    if(str == nullptr || str[0] == '\0')
    {
        return nullptr;
    }
    Node* tmp = head;
    Node* result_node = nullptr;
    bool flag = false;
    while(tmp != nullptr)
    {
        Node* current = tmp;
        int i;
        for(i = 0; i < strlen(str); ++i)
        {
            if(str[i] != tmp -> info)
            {
                flag = false;
                break;
            }
            result_node = current;
            flag = true;
            if(tmp -> next)
            {
                current = tmp -> next;
            }
            
            if(tmp -> next == nullptr && i != strlen(str) - 1)
            {
                return nullptr; // case, that substring is longer
            }
        }
        if(i == strlen(str) && flag == true)
        {
            return result_node;
        }
        tmp = tmp -> next;
    }
    return nullptr;

}
String::String()
{
    head = tail = nullptr;
}
void String:: extend_with(int num_to_extend)
{
    if(num_to_extend > size)
    {
        int counter = size;
        Node* tmp = tail;
        while(counter < num_to_extend)
        {
            tmp  -> next = new Node('!');
            tmp = tmp -> next;
            counter ++;
            size ++;
        }
        tail = tmp;
        tail->next = nullptr;
    }
    else if(num_to_extend < size)
    {   
        size = num_to_extend;
        Node* tmp = head;
        int counter = 0;
        while(counter != num_to_extend)
        {
            tmp = tmp -> next;
            counter ++;
        }
        Node* tmp_for_tmp = tmp;
        while(tmp_for_tmp != nullptr)
        {
            Node* other_tmp = tmp_for_tmp ;
            tmp_for_tmp = tmp_for_tmp -> next;
            delete other_tmp;
        }
        tail = tmp;
        tail -> next = nullptr;    
    }

}
String::String(const char* sequence)
{   
    size = 0;
    if(sequence == nullptr)
    {
        head = tail = nullptr;
        return;
    }
    head = new Node(sequence[0]);
    size ++;
    int counter = 1;
    Node* tmp = head;
    while(sequence[counter])
    {
        tmp -> next = new Node(sequence[counter++]);
        tmp = tmp -> next;
        size ++;
    }
    tail = tmp;
    tmp -> next = nullptr;
}
String::String(const String& other)
{   
    size = 0;
    if(other.head == nullptr)
    {
        head = tail = nullptr;
        return;
    }
    head = tail = new Node(other.head->info);
    size ++;
    Node* other_tmp = other.head->next;
    Node* this_node = head;
    while(other_tmp != nullptr)
    {
        Node* tmp = new Node(other_tmp->info);
        this_node -> next = tmp;
        other_tmp = other_tmp -> next;
        this_node = this_node -> next;
        size ++;
    }
    tail = this_node;
    tail -> next = nullptr;

}
String& String:: operator= (const String& other)
{   
    size = 0;
    if(this == &other)
    {
        return *this;
    }
    if(other.head != nullptr) // other maybe created by String() with head and tail are nullptr, or 
    {
        clear();
        head = new Node(other.head->info);
        Node* this_tmp = head;
        size++;
        Node* other_tmp = other.head->next;
        while(other_tmp != nullptr)
        {
            Node* nodeik = new Node(other_tmp -> info);
            this_tmp -> next = nodeik;
            other_tmp = other_tmp -> next;
            this_tmp = this_tmp -> next;
            size ++;
        }
        tail = this_tmp;
        tail->next = nullptr;
        return *this;
    }
    else
    {
        head = tail = nullptr;
        return *this;
    }
    
    
}
String::~String()
{
    clear();
}
void String:: clear()
{
    while(head != nullptr)
    {
        Node* tmp = head;
        head = head -> next;
        delete tmp;
    }
    tail = nullptr;
}
void String::echo() const
{
    if(head == nullptr)
    {
        cout << "NONE" << endl;
        return;
    }
    Node* tmp = head;
    while(tmp != nullptr)
    {
        cout << tmp -> info;
        tmp = tmp -> next;
    }
    cout << endl;


}
int String:: get_size() const
{
    return size;
}


int main()
{
    const char* str = "Hello";
    String s2(str);
    s2.echo();

    String s1;
    s1.echo();

    String s4(s2);
    s4.echo();
    String s5;

    s5 = s4;
    s5.echo();

    s5.extend_with(14);
    s5.echo();

    s5.extend_with(5);
    s5.echo();

    Node* result = s2.search_str("ll");
    if(result)
    {
        cout << "Substring found starting from character: " << result -> info << endl;
    }
    else
    {
        cout << "Substring is not found" << endl;
    }
    
    cout << s4.get_size() << endl;
    cout << s5.get_size() << endl;
}
