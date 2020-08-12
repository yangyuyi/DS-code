#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
class TreeNode {
private:
    T value;
    TreeNode *leftchild;
    TreeNode *rightchild;
public:
    TreeNode();

    explicit TreeNode(T val);

    T val();

    TreeNode<T> *left();

    TreeNode<T> *right();

    void setleft(TreeNode<T> *left);

    void setright(TreeNode<T> *right);
};

template<class T>
TreeNode<T>::TreeNode() {
    this->leftchild = NULL;
    this->rightchild = NULL;
}

template<class T>
TreeNode<T>::TreeNode(const T val) {
    this->value = val;
    this->leftchild = NULL;
    this->rightchild = NULL;
}

template<class T>
T TreeNode<T>::val() {
    return value;
}

template<class T>
TreeNode<T> *TreeNode<T>::left() {
    return leftchild;
}

template<class T>
TreeNode<T> *TreeNode<T>::right() {
    return rightchild;
}

template<class T>
void TreeNode<T>::setleft(TreeNode<T> *left) {
    leftchild = left;
}

template<class T>
void TreeNode<T>::setright(TreeNode<T> *right) {
    rightchild = right;
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

    int depth(TreeNode<T> *r);
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
TreeNode<T> *BinaryTree<T>::CreateTree(T *src, int &n) {
    T val = src[n++];
    if (val == -1) return NULL;
    TreeNode<T> *node;
    node = new TreeNode<T>(val);
    node->setleft(CreateTree(src, n));
    node->setright(CreateTree(src, n));
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
int BinaryTree<T>::depth(TreeNode<T> *r) {
    if (r == NULL) return 0;
    return max(depth(r->left()), depth(r->right())) + 1;
}

template<class T>
TreeNode<T> *BinaryTree<T>::getRoot() {
    return root;
}

int main() {
    int Data[] = {3, 9, -1, -1, 20, 15, -1, -1, 7, -1, -1};
    BinaryTree<int> *BiT;
    BiT = new BinaryTree<int>(Data);
    int dep = 0;
    dep = BiT->depth(BiT->getRoot());
    cout << dep << endl;
    return 0;
}
