#include <iostream>
#include "dlist.h"
using namespace std;

bool cmp(const int *a, const int *b)
{
    return *a == *b ? 1 : 0;
}

int main(int argc, char *argv[])
{
    int result = 0;

    Dlist<int> ilist;
    int *ip = new int(1);
    ilist.insertFront(ip);

    ip = ilist.removeFront();
    if (*ip != 1)
        result = -1;
    delete ip;

    if (!ilist.isEmpty())
        result = -1;

    int *ip1 = new int(-2), *ip2 = new int(0), *ip3 = new int(3), *ip4 = new int(4), *ip5 = new int(5);
    Dlist<int> ilist2;

    cout << ilist.isEmpty() << endl; // 1
    ilist.insertBack(ip1);
    cout << ilist.isEmpty() << endl; // 0
    ilist.insertFront(ip2);          // now has 0 -2
    ilist2.insertBack(ip3);
    ilist2.insertBack(ip4);
    ilist2.insertFront(ip5); // now has 5 3 4

    Dlist<int> ilist3 = Dlist<int>(ilist); // now has 0 -2
    ilist3 = ilist2;                       // now has 5 3 4
    ilist2=ilist2; //check operator=
    int *tmp = ilist2.removeFront(); // now has 3 4
    cout << *tmp << endl;            // 5
    delete tmp;
    tmp = ilist2.removeBack(); // now has 3
    cout << *tmp << endl;      // 4
    delete tmp;
    tmp = ilist2.removeBack(); // now is empty
    cout << *tmp << endl;      // 3
    delete tmp;
    tmp = nullptr;

    int *tmp2 = ilist3.removeBack(); // now has 5 3
    cout << *tmp2 << endl;           // 4
    delete tmp2;
    tmp2 = nullptr;

    int *ip6 = new int(6), *ip7 = new int(7), *ip8 = new int(8), *ip9 = new int(9);
    ilist3.insertBack(ip6);
    ilist3.insertBack(ip7);
    ilist3.insertBack(ip8);
    ilist3.insertBack(ip9); // now has 5 3 6 7 8 9

    int *ipCmp1 = new int(5), *ipCmp2 = new int(9), *ipCmp3 = new int(7), *ipCmp4 = new int(10);
    tmp2 = ilist3.remove(cmp, ipCmp1); // now has 3 6 7 8 9
    cout << *tmp2 << endl;             // 5
    delete tmp2;
    tmp2 = ilist3.remove(cmp, ipCmp2); // now has 3 6 7 8
    cout << *tmp2 << endl;             // 9
    delete tmp2;
    tmp2 = ilist3.remove(cmp, ipCmp3); // now has 3 6 8
    cout << *tmp2 << endl;             // 7
    delete tmp2;
    tmp2 = ilist3.remove(cmp, ipCmp4); // now has 3 6 8
    cout << tmp2 << endl;              // nullptr: 0

    delete ipCmp1;
    delete ipCmp2;
    delete ipCmp3;
    delete ipCmp4;

    return result;
}