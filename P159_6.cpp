#include <iostream>

using namespace std;

template<class T>
class TreeNode {
private:
    T val;
    TreeNode<T> *child_node;
    TreeNode<T> *sibling_node;
public:
    TreeNode();

    explicit TreeNode(T val);

    T value();

    TreeNode<T> *child();

    TreeNode<T> *sibling();

    void set_child(TreeNode<T> *node);

    void set_sibling(TreeNode<T> *node);

    void insert_child(TreeNode<T> *node);

    void insert_sibling(TreeNode<T> *node);

};

template<class T>
TreeNode<T>::TreeNode() {
    child_node = NULL;
    sibling_node = NULL;
}

template<class T>
TreeNode<T>::TreeNode(T val) {
    this->val = val;
    child_node = NULL;
    sibling_node = NULL;
}

template<class T>
T TreeNode<T>::value() {
    return val;
}

template<class T>
TreeNode<T> *TreeNode<T>::child() {
    return child_node;
}

template<class T>
TreeNode<T> *TreeNode<T>::sibling() {
    return sibling_node;
}

template<class T>
void TreeNode<T>::set_child(TreeNode<T> *node) {
    child_node = node;
}

template<class T>
void TreeNode<T>::set_sibling(TreeNode<T> *node) {
    sibling_node = node;
}

template<class T>
void TreeNode<T>::insert_child(TreeNode<T> *node) {
    if (child_node == NULL) child_node = node;
    else {
        node->set_sibling(child_node);
        child_node = node;
    }
}

template<class T>
void TreeNode<T>::insert_sibling(TreeNode<T> *node) {
    if (sibling_node == NULL) sibling_node = node;
    else {
        node->set_sibling(sibling_node);
        sibling_node = node;
    }
}


template<class T>
class Tree {
private:
    TreeNode<T> *root;
public:
    explicit Tree(T val_root);

    ~Tree();

    TreeNode<T> *getRoot();

    void Delete(TreeNode<T> *r);

    void PreOrder(TreeNode<T> *r);

    int Node_num(TreeNode<T> *r);
};

template<class T>
Tree<T>::Tree(T val_root) {
    root = new TreeNode<T>(val_root);
}

template<class T>
Tree<T>::~Tree() {
    Delete(root);
}

template<class T>
TreeNode<T> *Tree<T>::getRoot() {
    return root;
}

template<class T>
void Tree<T>::Delete(TreeNode<T> *r) {
    if (r == NULL) return;
    Delete(r->child());
    Delete(r->sibling());
    delete r;
}

template<class T>
int Tree<T>::Node_num(TreeNode<T> *r) {
    if (r == NULL) return 0;
    return Node_num(r->child()) + Node_num(r->sibling()) + 1;
}

template<class T>
void Tree<T>::PreOrder(TreeNode<T> *r) {
    if (r == NULL) return;
    cout << r->value() << ' ';
    PreOrder(r->child());
    PreOrder(r->sibling());
}

int main() {
    Tree<char> *tr;
    tr = new Tree<char>('A');
    TreeNode<char> *node1;
    node1 = new TreeNode<char>('B');
    TreeNode<char> *node2;
    node2 = new TreeNode<char>('C');
    TreeNode<char> *node3;
    node3 = new TreeNode<char>('D');
    TreeNode<char> *node4;
    node4 = new TreeNode<char>('E');
    TreeNode<char> *node5;
    node5 = new TreeNode<char>('F');
    TreeNode<char> *node6;
    node6 = new TreeNode<char>('G');
    TreeNode<char> *node7;
    node7 = new TreeNode<char>('H');
    TreeNode<char> *node8;
    node8 = new TreeNode<char>('I');
    TreeNode<char> *node9;
    node9 = new TreeNode<char>('J');
    TreeNode<char> *node10;
    node10 = new TreeNode<char>('K');

    tr->getRoot()->insert_child(node1);
    tr->getRoot()->insert_child(node2);
    tr->getRoot()->insert_child(node3);
    tr->getRoot()->insert_sibling(node7);
    tr->getRoot()->insert_sibling(node10);
    node1->insert_child(node4);
    node2->insert_child(node5);
    node2->insert_sibling(node6);
    node7->insert_child(node8);
    node7->insert_child(node9);

    cout << "PreOrder:";
    tr->PreOrder(tr->getRoot());
    cout << endl;
    int num = tr->Node_num(tr->getRoot());
    cout << "Number of nodes:";
    cout << num << endl;
    return 0;
}
