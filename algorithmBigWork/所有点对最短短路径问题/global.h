#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

#define inf 1.7e+308
#define NO_EDGE 0x0
#define MAX_NUM 0xff

// Variables for the algorithm
int n;
double **c;
int **kay;

// variables for data input and output
// string data_path = "";
// string output_path = "";

// int file_index;

// ifstream infile;
// ofstream outfile;

void display_matrix(double **c){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(c[i][j] == inf) cout << "inf";
            else cout << c[i][j];
            cout << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}

void init_c_kay(int n){
    c = new double*[n + 1];
    kay = new int*[n + 1];
    for(int i = 0; i <= n; i++){
        c[i] = new double[n + 1];
        kay[i] = new int[n + 1];
    }

    // initialize kay[i][j] = 0
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            kay[i][j] = 0;
        }
    }

    // initialize c[i][i] = 0,c[i][j] = inf
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
        if(i == j)
            c[i][j] = 0.0;
        else
        {
            c[i][j] = inf;
        }
        
    }
}