#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

int st[4] = {2, 3, 4, 5};
int n = 4;
int sm = 7;

int  isSubsetSum(int S[], int n, int M)
{
    // The value of subset[i][j] will be
    // true if there is a subset of
    // set[0..j-1] with sum equal to i
    int subset[M+1][n+1] = {1};

    // If sum is 0, then answer is true
    for(int i= 0; i< n+1; i++) 
        subset[i][0] = 1;

    // If sum is not 0 and set is empty,
    // then answer is false
    for(int i= 1; i< M +1; i++)
        subset[0][i] = 0;

    // Fill the subset table in bottom-up manner
    for(int i = 1; i < n+1; i++)
    {
        for(int j = 1; j < M+1; j++)
        {
            if (j < S[i-1])
                subset[i][j] = subset[i-1][j];
            else
                subset[i][j] = subset[i-1][j] || subset[i-1][j-S[i-1]];
        }
    }

    // print the True-False table
    for(int i=0;i<n+1;i++)
    {
        for(int j=0;j<M+1;j++)
        {
            cout<<subset[i][j]<<" ";
        }
        printf("\n");
    }

    if(subset[n][M])
    {
        printf("Found a subset with given sum");
        string sol = "";
        // using backtracing to find the solution
        int i = n;
        while (i >= 0)
        {
            if(subset[i][M] && !! subset[i-1][M])
            {   
                sol += (char)S[i-1];
                M -= st[i-1];
            }
            if(M == 0)
                break;
            i -= 1;
        }
        printf("The solution is %s.", sol);
    }
    else
    {
        printf("No subset with given sum\n");
    }
    return 0;
}

int main()
{
    isSubsetSum(st, n, sm);
}
