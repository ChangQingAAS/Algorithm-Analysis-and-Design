#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char array1[5] = {'a', 'b', 'c', 'd', 'e'};
    int array2[5] = {5, 4, 3, 2, 1};
    int temp = 0;
    char temp2 = ' ';
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5- i; j++)
        {
            if (array2[j] > array2[j + 1])
            {
                temp = array2[j + 1];
                array2[j + 1] = array2[j];
                array2[j] = temp;
                temp2 = array1[j + 1];
                array1[j + 1] = array1[j];
                array1[j] = temp2;
            }
        }
    }
    for(int i = 0; i < 5; i++)
    {
        cout<<array1[i]<<"";
        cout<<array2[i]<<" ";
    }
}