#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

#define inf 1.7e+5
#define NO_EDGE 0x0
#define MAX_NUM 0xff

// Variables for the algorithm
int n, binaryOfN;
double mincost, temp;
double **dis;
double **Route;
int **way;


void init_all_arrays(int n, int binaryOfN)
{
    Route = new double *[n];
    dis = new double *[n];
    way = new int *[n];
    for (int i = 0; i <= n; i++)
    {
        Route[i] = new double[binaryOfN];
        dis[i] = new double[n];
        way[i] = new int[binaryOfN];
    }
}