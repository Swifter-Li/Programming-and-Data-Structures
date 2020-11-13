#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

bool tri(int num)
{
  num=num*2; 
  int x=(int)sqrt(num);
  if (num==x*(x+1)) return 1;
  else return 0 ;
}
bool pal(int num)
{
 char str[8]; char revstr[8];
 sprintf(str,"%d",num);
 int big=0;
 for (int i=1;i<9;i++)
 {
     num/=10;
     if (num==0)
     {big=i; break;}
 }
 for (int i=0;i<big;i++)
 {revstr[i]=str[big-1-i];}
 for (int i=0;i<big;i++)
 {
     if (revstr[i]!=str[i]) return 0;
 }
 return 1;
}
bool power(int num)
{ 
 int x=(int)sqrt(num); int pin=0;
 if (num==1) return 1;
 else
 {
     for (int i=2;i<=x;i++)
    {
        int num2=num;
         while(num2%i==0)
        {
             num2=num2/i;
        }
        if (num2==1) {pin=1;break;}
    }
 } 
 if (pin==1) return 1;
 else return 0;
}
bool abu(int num)
{ 
    int sum=0;
    for(int i = 1; i < num; ++i)
    {
        if(num % i == 0)
            sum=sum+i;
    }
    if (sum>num) return 1;
    else return 0;
}
int main()
{
    int integer; int testnum; int key=1;
    while (key==1)
    {
        cout<<"Please enter the integer and the test number: "; 
        cin>> integer >> testnum;
        if (integer>0&&integer<10000000&&testnum>0&&testnum<5)// Test whether it's in the range
        {
            key=0;
            switch (testnum)
            {
                case 1: cout<<tri(integer);
                break;
                case 2: cout<<pal(integer);
                break;
                case 3: cout<<power(integer);
                break;
                case 4: cout<<abu(integer);
                break;
            }
        }
        else key=1;
        
    }
} 
