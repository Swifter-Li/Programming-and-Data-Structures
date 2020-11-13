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
void print(string word,int i,Node* root);
//Effect: the helper to find the str


void decompressseve(const string& treefile,const string& binary);
//Effect: the decompressserver


int main(int argc, char *argv[]) {
    // TODO: implement this function
    string file1=argv[1];
    string file2=argv[2];
    decompressseve(file1,file2);
}

void print(string word,int i,Node* root)
//Effect: the helper to find the str
{
    int p=word.length();
    if (i!=word.length()-1)
    {
        if (word[i]=='0')  
        {
            i++;
            return print(word,i,root->leftSubtree());
        }
        if (word[i]=='1')  
        {
            i++;
            return print(word,i,root->rightSubtree());
        }
    }
    else
    {
        if (word[i]=='0')  
        {
            cout<<root->leftSubtree()->getstr();
            return;
        }
        else if (word[i]=='1')  
        {
            cout<<root->rightSubtree()->getstr();
            return;
        }
    }

}

void decompressseve(const string& treefile,const string& binary)
//Effect: the decompressserver
{
    HuffmanTree tree(treefile);
    ifstream ifile;
    ifile.open(binary);
    string line;
    while (getline(ifile,line))
    {
        int index=0;
        int num=0;
        while(line.find(' ',index)!=string::npos)
        {
            num++;
            index=(int)line.find(' ',index)+1;
        }
        string word[num]; 
        istringstream istream;
        istream.str(line);
        for (int i=0;i<num;i++)
        {
            istream>>word[i];
        }
        for (int i=0;i<num;i++)
        {
            print(word[i],0,tree.root);
        }
    }
    ifile.close();
}