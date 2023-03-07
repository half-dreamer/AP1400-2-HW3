#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional>
#include <vector>
#include <queue>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::queue;
using std::setfill;
using std::setw;
using std::vector;
class BST
{
    public:
    // nested clasee : Node
    class Node
        {
        public:
            Node(int value, Node* left, Node* right);
            Node();
            Node(const Node& node);

            int value;
            Node* left;
            Node* right;
            
            //user-defined member function
            bool isLeaf() {
                return left == nullptr && right == nullptr;
            };
            int getValue() {
                return value;
            }
            Node* getLeft() {
                return left;
            }
            Node* getRight() {
                return right;
            }
            friend ostream& operator<<(ostream & out, Node& node);

            // inequality with an int 
            // member function part 
            bool operator<(int num) {
                return value < num;
            }
            bool operator>(int num) {
                return value > num;
            }
            bool operator>=(int num) {
                return value >= num;
            }
            bool operator==(int num) {
                return value == num;
            }
            bool operator<=(int num) {
                return value <= num;
            }
            // non-member function part(declaration)
            friend bool operator<(int num, Node node);
            friend bool operator>(int num, Node node);
            friend bool operator==(int num, Node node);
            friend bool operator<=(int num, Node node);
            friend bool operator>=(int num, Node node);
        };
    BST();
    BST(std::initializer_list<int> nodeValues);
    BST(BST &bst);
    BST(BST &&bst);
    
    Node *&get_root();
    Node *get_root() const;
    friend ostream& operator<<(ostream& out, BST& bst);
    friend vector<Node *> nodesOfBST(Node* root);
    friend Node *buildBST_Recur(Node *&node);
    void bfs(std::function<void(Node *&node)> func);
    size_t length();
    size_t length(Node* curNode);
    bool add_node(int value);
    bool add_node(int value, Node*& curNode);
    Node** find_node(int value);
    Node **find_node(int value, Node **curNode);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    BST& operator++();
    BST &operator++(int);
    BST &operator=(BST &bst);
    BST &operator=(BST &&bst);

    ~BST();

private:
    Node* root;
};
#endif //BST_H