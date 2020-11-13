#include "binaryTree.h"
#include "huffmanTree.h"
//#include"binaryTree.cpp"
//#include"huffmanTree.cpp"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
Node* checkletter(Node** letter, int& nodenum,const char& c);
//Effect: check the letter whether is already in the array or not
//if not, add it to the array

bool cmp(Node* a,Node* b);
//Effect: sort helper function

void huffmansever(const int& num, const string& str);
//Effect: the huffman sever

int main(int argc, char *argv[]) {
    // TODO: implement this function
    string str;
    if (argc==2) str=argv[1];
    else str=argv[2];
    huffmansever(argc,str);
    //huffmansever(2,"textfile.txt");
}

Node* checkletter(Node** letter, int& nodenum,const char& c)
//Effect: check the letter whether is already in the array or not
//if not, add it to the array
{
    bool pin=0;      
    string str;
    if (c==10) str.push_back('\n');
    else str=c;
    for (int i=0;i<nodenum;i++)
    {
      if (letter[i]->getstr()==str)
      {
        pin=1;
        letter[i]->incnum();
        return nullptr;
      }
    }
    if (pin==0)
    {
      Node* p=new Node(str,1,nullptr,nullptr);
      letter[nodenum++]=p;
      return p;
    }  
    return nullptr;
}


bool cmp(Node* a,Node* b)
//Effect: sort helper function
{
  if (a->getnum()!=b->getnum()) return a->getnum()>b->getnum()? 1:0;
  else return a->getstr()>b->getstr()? 1:0;
}

void huffmansever(const int& num, const string& str)
//Effect: the huffman sever
{
    ifstream ifile;
    ifile.open(str);
    char c;
    Node** letter=new Node*[30];
    int nodenum=0;
    c=ifile.get();
    while (!ifile.eof())
    { 
      checkletter(letter,nodenum,c);
      c=ifile.get();
    }   
    string charac[nodenum];
    int charnum=nodenum;
    for (int i=0;i<nodenum;i++)
    {
      charac[i]=letter[i]->getstr();
    }
    while (nodenum!=1)
    {
      sort(letter,letter+nodenum,cmp); 
      Node *p;
      p=p->mergeNodes(letter[nodenum-2],letter[nodenum-1]); 
      nodenum=nodenum-2;
      letter[nodenum++]=p;
    } 
    HuffmanTree tree(letter[0]);    
    ifile.close();
    if (num==3) tree.printTree();
    else if (num==2)
    {
      ifstream ifile2;
      ifile2.open(str);
      c=ifile2.get();
      while (!ifile2.eof())
      { 
        string temp;
        temp.push_back(c);
        cout<<tree.findPath(temp)<<" ";
        c=ifile2.get();
      }   
      cout<<endl;
      ifile2.close();
    }
   // check(letter,nodenum);
    delete[] letter;

}