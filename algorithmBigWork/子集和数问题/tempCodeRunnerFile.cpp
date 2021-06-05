if(subset[n][M])
    {
        printf("Found a subset with given sum");
        string sol = "";
        // using backtracing to find the solution
        int i = n;
        while (i >= 0)
        {
            if(subset[i][M] && !subset[i-1][M])
            {   
                // sol += S[i-1];
                M -= st[i-1];
            }
            if(M == 0)
                break;
            i -= 1;
        }
        // printf("The solution is %s.", sol);
    }
    else
    {
        printf("No subset with given sum\n");
    }