/*Implement a multiplayer game system that uses an AVL tree data structure to organize and
manage player data efficiently. The multiplayer game supports multiple players participating
simultaneously, and the AVL tree is used to store player information such as player_id and
scores (key, value pair). The system should provide following operation:
1. Player Registration
2. Leaderboard Display
3. Remove player from game*/

#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string name;
    int score;
    Node *left;
    Node *right;
    int height;
    Node(string n, int s)
    {
        name = n;
        score = s;
        left = right = NULL;
        height = 1;
    }
};

class AVL
{
public:
    Node *root;
    AVL()
    {
        root = NULL;
    }

    int height(Node *N)
    {
        if (N == NULL)
        {
            return 0;
        }
        return N->height;
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x; // return new root
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return y; // return new root
    }

    int getbalance(Node *N)
    {
        if (N == NULL)
        {
            return 0;
        }
        return height(N->left) - height(N->right);
    }

    Node *insertPlayer(Node *node, string name, int score)
    {
        if (node == NULL)
        {
            return new Node(name, score);
        }

        if (score < node->score)
        {
            node->left = insertPlayer(node->left, name, score);
        }
        else if (score > node->score)
        {
            node->right = insertPlayer(node->right, name, score);
        }
        else
        {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getbalance(node);

        if (balance > 1 && score < node->left->score)
        {
            return rightRotate(node);
        }

        if (balance < -1 && score > node->right->score)
        {
            return leftRotate(node);
        }

        if (balance > 1 && score > node->left->score)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && score < node->right->score)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void insert(string name, int score)
    {
        root = insertPlayer(root, name, score);
        cout << "Player registered." << endl;
    }

    void inorder(Node *node)
    {
        if (node == NULL)
        {
            return;
        }
        inorder(node->left);
        cout << node->name << " - " << node->score << endl;
        inorder(node->right);
    }

    void displayLeaderboard()
    {
        cout << "Leaderboard: " << endl;
        inorder(root);
    }

    Node *findPredecessor(Node *node)
    {
        Node *pred = node->left;
        while (pred->right != NULL)
        {
            pred = pred->right;
        }
        return pred;
    }

    Node *deletePlayer(Node *root, int score)
    {
        if (root == NULL)
        {
            return root;
        }

        if (score < root->score)
        {
            root->left = deletePlayer(root->left, score);
        }

        else if (score > root->score)
        {
            root->right = deletePlayer(root->right, score);
        }

        else
        {
            // No child
            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                return NULL;
            }
            else if (root->left == NULL || root->right == NULL)
            {
                Node *child = root->left ? root->left : root->right;
                delete root;
                return child;
            }
            else
            {
                Node *pred = findPredecessor(root);
                root->name = pred->name;
                root->score = pred->score;
                root->left = deletePlayer(root->left, pred->score);
            }
        }
        if (root == NULL)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getbalance(root);

        // Balancing
        if (balance > 1 && getbalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getbalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getbalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getbalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    void remove(int score)
    {
        root = deletePlayer(root, score);
        cout << "Player removed." << endl;
    }
};

int main()
{
    AVL game;

    game.insert("Alice", 100);
    game.insert("Bob", 150);
    game.insert("Charlie", 90);
    game.insert("Daisy", 200);
    game.insert("Eve", 120);
    game.insert("Keshav", 80);

    game.displayLeaderboard();

    game.remove(100);
    game.displayLeaderboard();
}