#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "dlist.h"
//#include "dlist_impl.h"
using namespace std;
template <class T>
class Stack
{
    private: Dlist<T> dlist;
    public :
    Stack();
    T top();
    bool empty();
    void push(T obj);
    T pop();

};

template <class T>
Stack<T>::Stack():dlist()
{

}

template <class T>
T Stack<T>::top()
{
    if (dlist.isEmpty()) throw emptyList();
    T *p = dlist.removeFront();
    dlist.insertFront(p);
    return *p;
}

template <class T>
bool Stack<T>::empty()
{
    if (dlist.isEmpty()) return 1;
    else return 0;
}

template <class T>
void Stack<T>::push(T obj)
{
    T* p= new T;
    (*p)= obj;
    dlist.insertFront(p);
}

template <class T>
T Stack<T>::pop()
{
    if (dlist.isEmpty()) throw emptyList();
    T *p = dlist.removeFront();
    T result=*p;
    delete p;
    return result;
}

int cmp(char a,char b);
//Effect: the cmp function

void calculator(const string& str);
//The calculating part

void transferfunction(const string& str);
//Effect: the tranfering part

int main()
{
    string str;
    getline(cin, str);
    transferfunction(str);
}

int cmp(char a,char b)
//Effect: the cmp function
{
    if (a=='+'||a=='-')
    {
        if (b=='+'||b=='-') return 0;
        else if (b=='*'||b=='/') return -1;
    }
    else if (a=='*'||a=='/')
    {
        if (b=='+'||b=='-') return 1;
        else if (b=='*'||b=='/') return 0;
    }
    return 0;
}
void calculator(const string& str)
//The calculating part
{
    int length=str.length();
    int pos=0;
    Stack<int> list;
    while (pos<length)
    {
        if (str[pos]>='0'&&str[pos]<='9') 
        {
            int sum=str[pos]-'0';
            while (str[pos+1]>='0'&&str[pos+1]<='9')
            {
                sum=sum*10+str[pos+1]-'0';
                pos++;
            }
            list.push(sum);
        }
        else if (str[pos]=='+'||str[pos]=='-'||str[pos]=='*'||str[pos]=='/')
        {
            string line="error";
            try
            {
                if (list.empty()) throw line;
            }
            catch (string& line)
            {
                cout << "ERROR: Not enough operands" << endl;
                return;
            }
            int a=list.pop();
            try
            {
                if (list.empty()) throw line;
            }
            catch (string& line)
            {
                cout << "ERROR: Not enough operands" << endl;
                return;
            }
            int b=list.pop();
            if (str[pos]=='+') list.push(a+b);
            else if (str[pos]=='-') list.push(b-a);
            else if (str[pos]=='*') list.push(a*b);
            else if (str[pos]=='/') 
            {
                string line="error";
                try
                {
                    if (a==0) throw line;
                    else list.push(b/a);
                }
                catch(string& line)
                {
                    cout << "ERROR: Divide by zero" << endl;
                    return;
                }
            }
        }
        pos++;
    }
    int p=list.pop();
    string line="error";
    try 
    {
        if (!list.empty()) throw line;
        else cout<<p;
    }
    catch(string& line)
    {
        cout << "ERROR: Too many operands" << endl;
    }
}

void transferfunction(const string& str)
//Effect: the tranfering part
{
    int length=str.length();
    stringstream result;
    int pos=0;
    Stack<char> list;
    while (pos<length)
    {
        if (str[pos]>='0'&&str[pos]<='9') 
        {
            result<<str[pos];
            while (str[pos+1]>='0'&&str[pos+1]<='9')
            {
                result<<str[pos+1];
                pos++;
            }
            result<<" ";
        }
        else if (str[pos]=='+'||str[pos]=='-'||str[pos]=='*'||str[pos]=='/')
        {
            while((!list.empty()&&cmp(list.top(),str[pos])==1)||
                    (!list.empty()&&cmp(list.top(),str[pos])==0&&list.top()!='('))
            {
                result<<list.pop()<<" ";
            }
            list.push(str[pos]);
        }
        else if (str[pos]=='(') list.push(str[pos]);
        else if (str[pos]==')')
        {
            while (list.empty()==0&&list.top()!='(') 
            {
                result<<list.pop()<<" ";
            }
            string line="error";
            try {
                if (list.empty()) throw line;
            }
            catch (string& line)
            {
                cout << "ERROR: Parenthesis mismatch" << endl;
                return;
            }
            if (list.top()=='(') list.pop();
        }
        string l=result.str();
        pos++;
    }
    while(!list.empty())
    {
        char p=list.pop();
        string line="error";
        try{
            if (p=='(') throw line;
        }
        catch (string& line)
        {
            cout << "ERROR: Parenthesis mismatch" << endl;
            return;
        }
        result<<p<<" ";
    }
    cout<<result.str()<<endl;
    calculator(result.str());
}