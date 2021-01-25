#include<iostream>
#include<queue>
#include<stack>
using namespace std;

class Node{
    public:
        Node* lchild;
        int data;
        Node *rchild;
        
        Node(int x){
            data = x;
            lchild = rchild = nullptr;
        }
};

class BinaryTree{

    public:
        Node* root;
        BinaryTree(){
            root = nullptr;
        }
        void create();
        Node* Deletion(Node*,int);
        void preOrderTraversal(Node*);
        void inOrderTraversal(Node*);
        void postOrderTraversal(Node*);
        void levelOrderTraversal();
        void iterativePreOrder();
        void iterativeInOrder();
        void iterativePostOrder();
        int height(Node*);
        int count(Node*);
        int count_Deg0_Nodes(Node*);
        int count_Deg1_Nodes(Node*);
        int count_Deg2_Nodes(Node*);
        int count_Internal_Nodes(Node*);
};

void BinaryTree::create(){

    cout<<"Enter root node : ";
    int x;
    cin>>x;
    root = new Node(x);
    queue<Node*> Q;
    Q.push(root);
    Node *p;
    while(!Q.empty()){
        p = Q.front();
        Q.pop();
        cout<<"Enter lchild of "<<p->data<<" : ";
        int val;
        cin>>val;
        if(val!=-1){
            Node *temp = new Node(val);
            p->lchild = temp;
            Q.push(temp);
        }
        cout<<"Enter rchild of "<<p->data<<" : ";
        cin>>val;
        if(val!=-1){
            Node *temp = new Node(val);
            p->rchild = temp;
            Q.push(temp);
        }
    }
}

void deleteDeepest(Node* root,Node* toDelete){

    queue<Node*> Q;
    Q.push(root);
    cout<<"5"<<endl;
    Node* temp;
    cout<<"6"<<endl;
    while(!Q.empty()){
        temp = Q.front();
        Q.pop();
        cout<<"* ";
        if(temp->lchild){
            if(temp->lchild == toDelete){
                temp->lchild = nullptr;
                cout<<"1"<<endl;
                delete toDelete;
                return;
            }
            else Q.push(temp->lchild);
        }

        if(temp->rchild){
            if(temp->rchild == toDelete){
                temp->rchild = nullptr;
                cout<<"2"<<endl;
                delete toDelete;
                return;
            }
            else Q.push(temp->rchild);
        }

    }
    cout<<endl;
}

Node* BinaryTree::Deletion(Node* root,int x){

    if(!root) return nullptr;

    if(!root->lchild && !root->rchild){
        if(root->data == x){
            delete root;
            return nullptr;
        }
        else return root;
    }
    queue<Node*> Q;
    Q.push(root);

    Node * temp;
    Node* keyNode = nullptr;

    while(!Q.empty()){
        temp = Q.front();
        Q.pop();

        if(temp->data == x)
            keyNode = temp;

        if(temp->lchild)
            Q.push(temp->lchild);
        
        if(temp->rchild)
            Q.push(temp->rchild); 
    
    }

    if(keyNode){
        int val = temp->data;
        keyNode->data = val;
        deleteDeepest(root,temp);
    }

    return root;
}

void BinaryTree::preOrderTraversal(Node* p){
    if(p==nullptr) return;
    cout<<p->data<<" ";
    preOrderTraversal(p->lchild);
    preOrderTraversal(p->rchild);
}

void BinaryTree::inOrderTraversal(Node* p){
    if(p==nullptr) return;
    inOrderTraversal(p->lchild);
    cout<<p->data<<" ";
    inOrderTraversal(p->rchild);
}

void BinaryTree::postOrderTraversal(Node* p){
    if(p==nullptr) return;
    postOrderTraversal(p->lchild);
    postOrderTraversal(p->rchild);
    cout<<p->data<<" ";
}

void BinaryTree::iterativePreOrder(){

    stack<Node*> S;
    Node *p = root;
    while(p || !S.empty()){
        if(p){
            S.push(p);
            cout<<p->data<<" ";
            p=p->lchild;
        }
        if(!p){
            p = S.top();
            S.pop();
            p = p->rchild;
        }
    }
}

void BinaryTree::iterativeInOrder(){

    stack<Node*> S;
    Node *p = root;
    while(p || !S.empty()){
        if(p){
            S.push(p);
            p=p->lchild;
        }
        if(!p){
            p = S.top();
            S.pop();
            cout<<p->data<<" ";
            p = p->rchild;
        }
    }
}

void BinaryTree::iterativePostOrder(){

    stack<Node*> S;
    Node *p = root;
    while(p || !S.empty()){
        if(p){
            if(p->rchild) S.push(p->rchild);
            S.push(p);
            p=p->lchild;
        }
        if(!p){
            p = S.top();
            S.pop();
            if(p->rchild && !S.empty() && S.top() == p->rchild){
                S.pop();
                S.push(p);
                p = p->rchild;
            }
            else{
                cout<<p->data<<" ";
                p = nullptr;
            }
        }
    }


}

void BinaryTree::levelOrderTraversal(){
    queue<Node*> Q;
    if(root)
    Q.push(root);
    while(!Q.empty()){
        Node *p = Q.front();
        Q.pop();
        cout<<p->data<<" ";
        if(p->lchild) Q.push(p->lchild);
        if(p->rchild) Q.push(p->rchild);
    }
}

int BinaryTree::height(Node *p){

    if(!p) return -1;

    int a = height(p->lchild); 
    int b = height(p->rchild);
    if(a>b) return a+1;
    else return b+1;

}

int BinaryTree::count(Node* p){

    if(p==nullptr) return 0;
    return count(p->lchild)+count(p->rchild)+1;

}

int BinaryTree::count_Deg0_Nodes(Node* p){
    
    if(p==nullptr) return 0;

    int a = count_Deg0_Nodes(p->lchild);
    int b = count_Deg0_Nodes(p->rchild);

    if(!p->lchild && !p->rchild)
        return a+b+1;
    return a+b;

}

int BinaryTree::count_Deg1_Nodes(Node* p){

    if(p==nullptr) return 0;

    int a = count_Deg1_Nodes(p->lchild);
    int b = count_Deg1_Nodes(p->rchild);

    if(!!p->lchild ^ !!p->rchild)
        return a+b+1;
    return a+b;

}

int BinaryTree::count_Deg2_Nodes(Node* p){

   if(p==nullptr) return 0;

    int a = count_Deg2_Nodes(p->lchild);
    int b = count_Deg2_Nodes(p->rchild);

    if(p->lchild && p->rchild)
        return a+b+1;
    return a+b;

}

int BinaryTree::count_Internal_Nodes(Node* p){

    if(p==nullptr) return 0;

    int a = count_Internal_Nodes(p->lchild);
    int b = count_Internal_Nodes(p->rchild);

    if(p->lchild || p->rchild)
        return a+b+1;
    return a+b;


}



int main(){

    BinaryTree tree;
    tree.create();
    tree.levelOrderTraversal();
    cout<<endl;
    tree.root = tree.Deletion(tree.root,5);

    tree.levelOrderTraversal();
    // cout<<endl;
    return 0;
}

//Tree Implementation
// create
// preorder
// inorder
// postorder
// level order
// iterative preorder,inorder,postorder
// height
// generate tree from traversal
// count nodes in a binary tree
// count deg(0),deg(1),deg(2) nodes
// internal nodes
// external nodes
