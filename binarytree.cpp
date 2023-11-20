                                                                //RECURSIVE APPROACH//
#include <iostream>
using namespace std;

struct tree_node
{
    tree_node* left;
    tree_node* right;
    int item;
    tree_node(int i, tree_node* l = nullptr, tree_node* r = nullptr) : item(i), left(l), right(r) {}
};

class binary_tree
{
public:
    binary_tree();
    ~binary_tree();
    binary_tree(const binary_tree&);
    binary_tree(int*, int);
    void echo();

private:
    tree_node* root;
    tree_node* insert(tree_node*, int);
    tree_node* copy_tree(tree_node*);
    void destroy_node(tree_node*);
    void print_tree_inorder_traverse(tree_node*);
};

void binary_tree::print_tree_inorder_traverse(tree_node* node)
{
    if (node == nullptr)
    {
        return;
    }
    print_tree_inorder_traverse(node->left);
    cout << node->item << " ";
    print_tree_inorder_traverse(node->right);
}

void binary_tree::echo()
{
    print_tree_inorder_traverse(root);
    cout << endl;
}

binary_tree::binary_tree(int* arr, int size)
{
    root = nullptr;

    for (int i = 0; i < size; i++)
    {
        root = insert(root, arr[i]);
    }
}

void binary_tree::destroy_node(tree_node* node)
{
    if (node == nullptr)
    {
        return;
    }

    destroy_node(node->left);
    destroy_node(node->right);
    delete node;
}

binary_tree::~binary_tree()
{
    destroy_node(root);
}

binary_tree::binary_tree()
{
    root = nullptr;
}

tree_node* binary_tree::insert(tree_node* node, int item)
{
    if (node == nullptr)
    {
        return new tree_node(item);
    }
    if (item < node->item)
    {
        node->left = insert(node->left, item);
    }
    else if (item > node->item)
    {
        node->right = insert(node->right, item);
    }
    return node;
}

tree_node* binary_tree::copy_tree(tree_node* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    tree_node* new_node = new tree_node(node->item);
    new_node->left = copy_tree(node->left);
    new_node->right = copy_tree(node->right);
    return new_node;
}

binary_tree::binary_tree(const binary_tree& other)
{
    root = copy_tree(other.root);
}

int main()
{
    int* arr = new int[7];
    for (int i = 0; i < 5; i++)
    {
        arr[i] = i;
    }
    arr[5] = 5;
    arr[6] = 5; //Check if program delete our same numbers;
    binary_tree s1(arr, 6);
    s1.echo();
    binary_tree s2(s1); //copy-ctor
    s2.echo();
    delete[] arr;
    return 0;
}

