#include <iostream>
using namespace std;

int main()
{
    int i, j, x = 1,count = 0;
    int n = 3;
    for (i = 0; i < n; i++)
        for (j = i; j < n; j++)
        {    x = x * 2;
            count++;
        }

    cout<<count;
    return x;
}