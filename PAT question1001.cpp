#include <iostream>
using namespace std;
int main()
{
    int a,n=0;
    cin>>a;
    while(a!=1)
    {
        if(a%2==0)
        {
            a=a/2;
            ++n;
        }
        else
        {
            a=(3*a+1)/2;
            ++n;
        }
       

    }
    cout <<n;
    return 0;
}
