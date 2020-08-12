#include <iostream>
#include <stack>

using namespace std;

template<class T>
class TreeNode {
private:
    T val;
    TreeNode<T> *left_child;
    TreeNode<T> *right_child;
public:
    TreeNode();

    explicit TreeNode(T val);

    T value();

    TreeNode<T> *left();

    TreeNode<T> *right();

    void setLeft(TreeNode<T> *left);

    void setRight(TreeNode<T> *right);
};

template<class T>
TreeNode<T>::TreeNode() {
    left_child = NULL;
    right_child = NULL;
}

template<class T>
TreeNode<T>::TreeNode(T val) {
    this->val = val;
    left_child = NULL;
    right_child = NULL;
}

template<class T>
TreeNode<T> *TreeNode<T>::left() {
    return left_child;
}

template<class T>
TreeNode<T> *TreeNode<T>::right() {
    return right_child;
}

template<class T>
void TreeNode<T>::setLeft(TreeNode<T> *left) {
    left_child = left;
}

template<class T>
void TreeNode<T>::setRight(TreeNode<T> *right) {
    right_child = right;
}

template<class T>
T TreeNode<T>::value() {
    return val;
}

template<class T>
class BinaryTree {
private:
    TreeNode<T> *root;
public:
    BinaryTree();

    explicit BinaryTree(T src[]);

    ~BinaryTree();

    TreeNode<T> *getRoot();

    TreeNode<T> *CreateTree(T src[], int &n);

    void DeleteTree(TreeNode<T> *r);

    bool search(TreeNode<T> *r, T val);

    bool search_without_recursion(TreeNode<T> *r, T val);
};

template<class T>
BinaryTree<T>::BinaryTree() {
    root = NULL;
}

template<class T>
BinaryTree<T>::BinaryTree(T *src) {
    int num = 0;
    root = CreateTree(src, num);
}

template<class T>
BinaryTree<T>::~BinaryTree() {
    DeleteTree(root);
}

template<class T>
TreeNode<T> *BinaryTree<T>::getRoot() {
    return root;
}

template<class T>
TreeNode<T> *BinaryTree<T>::CreateTree(T *src, int &n) {
    T val = src[n++];
    if (val == -1) return NULL;
    TreeNode<T> *node;
    node = new TreeNode<T>(val);
    node->setLeft(CreateTree(src, n));
    node->setRight(CreateTree(src, n));
    return node;
}

template<class T>
void BinaryTree<T>::DeleteTree(TreeNode<T> *r) {
    if (r != NULL) {
        DeleteTree(r->left());
        DeleteTree(r->right());
        delete r;
    }
}

template<class T>
bool BinaryTree<T>::search(TreeNode<T> *r, T val) {
    if (r == NULL) return false;
    if (r->value() == val) return true;
    return search(r->left(), val) || search(r->right(), val);
}

template<class T>
bool BinaryTree<T>::search_without_recursion(TreeNode<T> *r, T val) {
    stack<TreeNode<T> *> s;
    TreeNode<T> *p = r;
    s.push(NULL);
    while (p != NULL) {
        if (p->value() == val) return true;
        if (p->right() != NULL) s.push(p->right());
        if (p->left() != NULL) p = p->left();
        else {
            p = s.top();
            s.pop();
        }
    }
    return false;
}


int main() {
    int Data[] = {3, 9, -1, -1, 20, 15, -1, -1, 7, -1, -1};
    int k1;
    int k2;
    BinaryTree<int> *BiT;
    BiT = new BinaryTree<int>(Data);
    cout << "Please enter the number_k1 you want to search(recursion):" << endl;
    cin >> k1;
    if (BiT->search(BiT->getRoot(), k1)) cout << k1 << " is found." << endl;
    else cout << k1 << " is not in the tree." << endl;

    cout << "Please enter the number_k1 you want to search(without recursion):" << endl;
    cin >> k2;
    if (BiT->search_without_recursion(BiT->getRoot(), k2)) cout << k2 << " is found." << endl;
    else cout << k2 << " is not in the tree." << endl;
    return 0;
}
