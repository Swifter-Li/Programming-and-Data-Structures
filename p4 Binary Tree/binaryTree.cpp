#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &str, int num, Node *left, Node *right) {
    // TODO: implement this function.
    this->str=str;
    this->num=num;
    this->right=right;
    this->left=left;
}

Node* Node::leftSubtree() const{
    // TODO: implement this function.  
    return this->left;
}

void Node::setleft(Node *n) {
    // TODO: implement this function.
    this->left=n;  
}

Node* Node::rightSubtree() const{
    // TODO: implement this function.  
    return this->right;
}

void Node::setright(Node *n) {
    // TODO: implement this function.  
    this->right=n; 
}

string Node::getstr() const {
    // TODO: implement this function.  
    return this->str;
}

int Node::getnum() const {
    // TODO: implement this function.  
    return this->num;
}

void Node::incnum() {
    // TODO: implement this function.
    this->num++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    // TODO: implement this function.
    string str=leftNode->getstr()+rightNode->getstr();
    int num=leftNode->getnum()+rightNode->getnum();
    Node *p=new Node(str, num, leftNode, rightNode);
    return p;
}

/* =============================== Binary Tree =============================== */
Node* copyhelper(Node* root)
{
    if (root!=nullptr)
    {
        Node* np1=nullptr, *np2=nullptr;
        if (root->leftSubtree()!=nullptr)
        {
            np1=copyhelper(root->leftSubtree());
        }
        if (root->rightSubtree()!=nullptr)
        {
            np2=copyhelper(root->rightSubtree());
        }
        Node* np=new Node(root->getstr(),root->getnum(),np1,np2);
        return np;
    }
    else return nullptr;
}
BinaryTree::BinaryTree(Node *rootNode)
{
    // this->root=copyhelper(rootNode);
    this->root=rootNode;
}

void deletehelper(Node* root)
{
    if (root!=nullptr)
    {
        deletehelper(root->leftSubtree());
        deletehelper(root->rightSubtree());
        delete root;
        return;
    }
    else return;
}
BinaryTree::~BinaryTree() {
    // TODO: implement this function.
    deletehelper(root);
    return;
}
string findPath_helper(Node* root,const string &s)
{
     if (root->getstr()==s) return  "";
     else if (!(root->leftSubtree()||root->rightSubtree())) return "-1";
     if (root->leftSubtree())
     {
         string p=findPath_helper(root->leftSubtree(),s);
         if (p!="-1") return "0"+p;
     }
     if(root->rightSubtree())
     {
         string q=findPath_helper(root->rightSubtree(),s);
         if (q!="-1") return "1"+q;
     } 
     return "-1";
} 


string BinaryTree::findPath(const string &s) const{
    // TODO: implement this function.
    return findPath_helper(this->root,s);
}
int sum_helper(Node* root)
{
    if (root==nullptr) return 0;
    else 
    {
        return sum_helper(root->leftSubtree())+sum_helper(root->rightSubtree())+root->getnum();
    }

}
int BinaryTree::sum() const {
    // TODO: implement this function.
    return sum_helper(root);
}

int depth_helper(Node* root)
{
    if (root==nullptr) return 0;
    if (root->leftSubtree()==nullptr&&root->rightSubtree()==nullptr) return 1;
    int max=depth_helper(root->leftSubtree())>depth_helper(root->rightSubtree())?
            depth_helper(root->leftSubtree()):depth_helper(root->rightSubtree());
    return 1+max;
}

int BinaryTree::depth() const {
    // TODO: implement this function.
    return depth_helper(root);
}


void preorder_helper(Node* root)
{
    if (root!=nullptr)
    {
        cout<<root->getnum()<<" ";
        preorder_helper(root->leftSubtree());
        preorder_helper(root->rightSubtree());
    }
    return;
}
void BinaryTree::preorder_num() const {
    // TODO: implement this function.
    preorder_helper(root);
    cout<<endl;
}

void inorder_helper(Node* root)
{
    if (root!=nullptr)
    {
        inorder_helper(root->leftSubtree());
        cout<<root->getstr()<<" ";
        inorder_helper(root->rightSubtree());
    }
    return;
}
void BinaryTree::inorder_str() const {
    // TODO: implement this function.
    inorder_helper(root);
    cout<<endl;
}

void postorder_helper(Node* root)
{
    if (root!=nullptr)
    {
        postorder_helper(root->leftSubtree());
        postorder_helper(root->rightSubtree());
        cout<<root->getnum()<<" ";
    }
    return;
}
void BinaryTree::postorder_num() const {
    // TODO: implement this function.
    postorder_helper(root);
    cout<<endl;
}

int allpathsungreater_helper(Node* root)
{
    //int sum=0;
    if (root==nullptr) return 0;
    else 
    {
        if (root->leftSubtree()==nullptr) return root->getnum()+allpathsungreater_helper(root->rightSubtree());
        else if (root->rightSubtree()==nullptr) return root->getnum()+allpathsungreater_helper(root->leftSubtree());
        else 
        {
            int left=root->getnum()+allpathsungreater_helper(root->leftSubtree());
            int right=root->getnum()+allpathsungreater_helper(root->rightSubtree());
            return left<right? left:right;
        }
    }
}
bool BinaryTree::allPathSumGreater(int sum) const {
    // TODO: implement this function.
    int p=allpathsungreater_helper(root);
    if (p>sum) return 1;
    else return 0;
}

bool covered_by_helper(Node* root,Node* input)
{
    if (input==nullptr)
    {
        if (root==nullptr) return 1;
        else return 0;
    }
    else 
    {
        if (root==nullptr) return 1;
        else return root->getnum()==input->getnum()&&covered_by_helper(root->leftSubtree(),input->leftSubtree())
        &&covered_by_helper(root->rightSubtree(),input->rightSubtree());
    }
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    // TODO: implement this function.
    return covered_by_helper(this->root,tree.root);
}

bool contained_by_helper(Node* root,Node* input)
{
    if (covered_by_helper(root,input)) return true;
    if (input==nullptr) return 0;
    return contained_by_helper(root,input->leftSubtree())
    ||contained_by_helper(root,input->rightSubtree());
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    // TODO: implement this function.
        return contained_by_helper(this->root,tree.root);
}


BinaryTree BinaryTree::copy() const {
    // TODO: implement this function.
        BinaryTree tree(copyhelper(root));
        return tree;
}
