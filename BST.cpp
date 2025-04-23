#include<iostream>
#include<string>
#include<queue>
using namespace std;

class Node{
    public:
    string faculty;
    string course;
    Node* left;
    Node* right;
};

class Dictionary{
    public:
    Node* root;
    Dictionary(){
        root = NULL;
    }

    void inorder(Node *r)
    {
        if (!r)
            return;
        inorder(r->left);
        cout << r->course << "\t<" << r->faculty << ">" << endl;
        inorder(r->right);
    }

    Node* findPredecessor(Node* root){
        Node* pred = root->left;
        while (pred->right != NULL){
            pred = pred->right;
        }
        return pred;
    }

    void insertNode(string c, string f){
        Node* nn = new Node();
        
        if(!nn){
            return;
        }

        nn->course = c;
        nn->faculty = f;
        nn->left = nn->right = NULL;

        if(root == NULL){
            root = nn;
            return;
        }

        Node* ptr = root;

        while(ptr){
            if(ptr->course == c){
                return;
            }

            if(ptr->course < c){
                if(ptr->right == NULL){
                    ptr->right = nn;
                    return;
                }
                ptr = ptr->right;
            }

            else{
                if(ptr->left == NULL){
                    ptr->left = nn;
                    return;
                }
                ptr = ptr->left;
            }
        }
    }

    Node *deleteNode(Node* root, string c){
        if(root == NULL){
            return NULL;
        }

        if(root->course == c){
            //No child
            if(root->left == NULL && root->right == NULL){
                delete root;
                return NULL;
            }

            //One child
            if(root->left == NULL || root->right == NULL){
                Node* child = (root->left)? root->left : root->right;
                delete root;
                return child;
            }

            //Two child
            Node* pred = findPredecessor(root);
            root->course = pred->course;
            root->faculty = pred->faculty;
            root->left = deleteNode(root->left,pred->course);
        }

        else if(c < root->course){
            root->left = deleteNode(root->left, c);
        }

        else{
            root->right = deleteNode(root->right, c);
        }
        return root;
    }

    string searchNode(string c){
        Node* curr = root;
        while(curr != NULL){
            if (curr->course == c)
            {
                return curr->faculty;
            }
            if (c < curr->course)
            {
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }
        return "Not found\n";
    }

    Node *mirror(Node *root)
    {
        if (root == NULL)
            return NULL;
        Node *temp = new Node{root->faculty, root->course, NULL, NULL};
        temp->left = mirror(root->right);
        temp->right = mirror(root->left);
        return temp;
    }

    void displayMirror()
    {
        Node *mirroredRoot = mirror(root);
        inorder(mirroredRoot);
        delete mirroredRoot;
    }
    
    Node *copyTree(Node *root)
    {
        if (root == NULL)
            return NULL;
        Node *temp = new Node{root->faculty, root->course, NULL, NULL};
        temp->left = copyTree(root->left);
        temp->right = copyTree(root->right);
        return temp;
    }

    void displayCopy()
    {
        Node *copiedRoot = copyTree(root);
        inorder(copiedRoot);
        delete copiedRoot;
    }

    void levelOrder(Node* root){
        if(root == NULL){
            return;
        }
        queue<Node*> q;
        q.push(root);
        cout << "\nLevel order: ";
        while(!q.empty()){
            Node* current = q.front();
            q.pop();

            cout << current->course << "\t" << "<" << current->faculty<< ">" << endl;

            if(current->left != NULL){
                q.push(current->left);
            }

            if(current->right != NULL){
                q.push(current->right);
            }
        }
    }
};


int main(){
    Dictionary d;
    d.insertNode("sci", "sir");
    d.insertNode("bio", "mam");
    d.inorder(d.root);
    d.root = d.deleteNode(d.root, "sci");
    d.inorder(d.root);
    cout<< d.searchNode("sci");
    d.displayMirror();
    d.displayCopy();


    d.levelOrder(d.root);
}