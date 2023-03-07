#include "bst.h"
/*
class BST
{
    public:
    class Node
    {
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);

        int value;
        Node* left;
        Node* right;
    };
public:
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

private:
    Node* root;
};
*/
/*  actually, there should be a more elegant way to
    implement Node class(create a Node.h and Node.cpp),
    but I just use nested class to make it more compact😇lol  */ 

using Node = BST::Node;


Node::Node (int value, BST::Node* left, BST::Node* right) :
         value(value), left(left), right(right)
{
    ;
}

Node::Node() 
{
    value = 0;
    left = nullptr;
    right = nullptr;
}

Node::Node(const Node& node) : value(node.value), left(node.left), right(node.right)
{
    ;
}

ostream& operator<<(ostream & out, Node& node)
{
    out << &node << setw(5) << setfill(' ') << "=>"
    "  " << "value:" << node.getValue() << "     left:"
    << node.getLeft() << "     right:" << node.getRight();
    return out;
}
bool operator<(int num, Node node)
{
    return num < node.value;
}
bool operator>(int num, Node node)
{
    return num > node.value;
}
bool operator==(int num, Node node)
{
    return num == node.value;
}
bool operator<=(int num, Node node)
{
    return num <= node.value;
}
bool operator>=(int num, Node node)
{
    return num >= node.value;
}

BST::BST() : root(nullptr)
{
    ;
}

BST::BST(std::initializer_list<int> nodeValues)
{
    root = nullptr;
    for (int nodeValue : nodeValues)
    {
        add_node(nodeValue);
    }
}

BST::BST(BST &bst){
    this->root = buildBST_Recur(bst.root);
}

Node* buildBST_Recur(Node* &node)
{
    // base case
    if (node == nullptr) {
        return nullptr;
    }
    // recursive case
    Node *copyNode = new Node(node->value, nullptr, nullptr);
    copyNode->left = buildBST_Recur(node->left);
    copyNode->right = buildBST_Recur(node->right);

    return copyNode;
}

// move constructor
BST::BST(BST &&bst)
{
    root = bst.root;
    // well, we need to null out the root of bst(rvalue)
    // becaues you see, in the test case,the passed in argument
    // may not acctually a rvalue, just be type cast using `std::move`
    // so we need to null out the passed in argument
    bst.root = nullptr;
}

Node*& BST::get_root() 
{
    return root;
}

Node* BST::get_root() const 
{
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func)
{
    if (root == nullptr) {
        return;
    }
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node *toPopNode = q.front();
        q.pop();
        func(toPopNode);
        if (toPopNode->left != nullptr) {
            q.push(toPopNode->left);
        }
        if (toPopNode->right != nullptr) {
            q.push(toPopNode->right);
        }
    }
}

size_t BST::length() 
{
    return length(get_root());
}

size_t BST::length(Node* curNode)
{
    size_t len;
    if (curNode == nullptr) {
        return 0;
    }
    len = 1 + length(curNode->left) + length(curNode->right);
    return len;

}

bool BST::add_node(int value)
{
    return add_node(value, root);
}

bool BST::add_node(int value, Node*& curNode)
{
    // base case
    if (curNode == nullptr) {
        curNode = new Node(value, nullptr, nullptr);
        return true;
    }

    // recursive case
    if (value < curNode->value) {
        return add_node(value, curNode->left);
    } else if (value == curNode->value) {
        return false; 
    } else {
        return add_node(value, curNode->right);
    }
}


ostream& operator<< (ostream& out, BST& bst) {
    vector<Node *> nodes = nodesOfBST(bst.get_root());
    out << setw(80) << setfill('*') << "*" << endl;
    for (auto node : nodes)
    {
        out << *node << std::endl;
    }
    out << "binary search tree size: " << bst.length() << endl;
    out << setw(80) << setfill('*') << '*' << endl;
    return out;
}

vector<Node *> nodesOfBST(Node* root)
{
    vector<Node *> nodes{};
    if (root == nullptr)
    {
        return vector<Node *>{};
    }
    nodes.push_back(root);
    for (auto node : nodesOfBST(root->left)) {
        nodes.push_back(node);
    }
    for (auto node : nodesOfBST(root->right)) {
        nodes.push_back(node);
    }
    return nodes;
}

Node** BST::find_node(int value)
{
    return find_node(value, &get_root());
}

Node** BST::find_node(int value, Node** curNode) 
{
    while (*curNode != nullptr) {
        if ((*curNode)->getValue() == value) {
            return curNode;
        } else if (value < (*curNode)->getValue()) {
            if ((*curNode)->right == nullptr) {
                return nullptr;
            }
            curNode = &(*curNode)->left;
        } else {
            if ((*curNode)->right == nullptr) {
                return nullptr;
            }
            curNode = &(*curNode)->right;
        }
    }
    // this return statement is useless,or say unreachable
    return nullptr;
}

// prefix ++
BST& BST::operator++()
{
    for (auto node : nodesOfBST(this->get_root())) {
        node->value = node->value + 1;
    }
    return *this;
}

// postfix ++ , the int is implicitly passes '0' to 
// differentiate prefix ++ and postfix ++
BST& BST::operator++(int)
{
    BST* temp = new BST(*this);
    for (auto node : nodesOfBST(this->get_root())) {
        node->value = node->value + 1;
    }
    return *temp;
}
/*
following code is not correct
you can't return a reference to a local variable
but you can return its value
or say , use `BST` as the type of return value 

BST& BST::operator++(int)
{
    BST temp(*this);
    for (auto node : nodesOfBST(this->get_root())) {
        node->value = node->value + 1;
    }
    return temp;
}
*/

BST& BST::operator=(BST &bst)
{
    // check for self-assignment
    if (this->root != bst.root) {
        root = buildBST_Recur(bst.root);
    }
    return *this;
}
BST& BST::operator=(BST &&bst)
{
    // check for self-assignment
    // in this case, you don't have to allocate new memory location
    // because in move version, you are actually "stealing" from the rvalue reference
    if (this->root != bst.root) {
        this->root = std::move(bst.root);
    }
    bst.root = nullptr;
    return *this;
}

BST::~BST() 
{
    std::vector<Node *> nodes;
    bfs([&nodes](BST::Node *&node)
        {nodes.push_back(node); });
    for (auto &node : nodes)
        delete node;
    
}
