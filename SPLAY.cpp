#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

class SplayTree {
private:
    Node* root;

    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    Node* splay(Node* root, int key) {
        if (root == nullptr || root->key == key) return root;

        if (key < root->key) {
            if (root->left == nullptr) return root;

            if (key < root->left->key) {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            }
            else if (key > root->left->key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr)
                    root->left = leftRotate(root->left);
            }

            return (root->left == nullptr) ? root : rightRotate(root);
        }
        else {
            if (root->right == nullptr) return root;

            if (key < root->right->key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr)
                    root->right = rightRotate(root->right);
            }
            else if (key > root->right->key) {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            }

            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }

    Node* insert(Node* root, int key) {
        if (root == nullptr) return new Node(key);

        root = splay(root, key);
        if (root->key == key) return root; // Duplicate

        Node* newNode = new Node(key);

        if (key < root->key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        }
        else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }

        return newNode;
    }

    Node* deleteKey(Node* root, int key) {
        if (root == nullptr) return nullptr;

        root = splay(root, key);

        if (root->key != key) {
            cout << "Key not found.\n";
            return root;
        }

        Node* temp;
        if (!root->left) {
            temp = root->right;
        } else {
            temp = splay(root->left, key); // Splay max node of left subtree
            temp->right = root->right;
        }

        delete root;
        return temp;
    }

    void inorder(Node* root) {
        if (!root) return;
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }

public:
    SplayTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void search(int key) {
        root = splay(root, key);
        if (root && root->key == key)
            cout << "Found " << key << " at root after splay.\n";
        else
            cout << key << " not found.\n";
    }

    void remove(int key) {
        root = deleteKey(root, key);
    }

    void printInorder() {
        cout << "Inorder traversal: ";
        inorder(root);
        cout << endl;
    }
};

int main() {
    SplayTree st;
    st.insert(10);
    st.insert(20);
    st.insert(30);
    st.insert(40);
    st.insert(50);

    st.printInorder();

    st.search(30);
    st.printInorder();

    st.remove(30);
    st.printInorder();

    st.remove(100);  // Attempt to delete non-existent node
}
