#include "global.h"

using namespace std;

void all_pairs(){

    int i, j, k;

    // calculate c[i][j] = c(i, j, k)
    for(k = 0; k < n; k++){
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                if(c[i][k] != inf && c[k][j] != inf 
                        && (c[i][j] == inf || c[i][j] > c[i][k] + c[k][j])){
                            c[i][j] = c[i][k] + c[k][j];
                            kay[i][j] = k;
                        }
            }
        }
    }
}

void output(int i, int j){
    if(i == j) return;
    if(kay[i][j] == 0) cout << j << " ";
    else{
        output(i, kay[i][j]);
        output(kay[i][j], j);
    }
}

void output_path(int i, int j){
    if(c[i][j] == inf){
        cout << "There is no path from " << i << " to " << j << endl;
    }
    else{
        cout << "The path is from " << i << " to " << j << " is: " << i << " ";
        output(i, j);
        cout << endl;
        cout<<"The cost of the path is "<<c[i][j]<<endl;
    }
}

void output_all_path(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i != j)
            {
                output_path(i, j);
                cout << '\n';
            }
        }
    }
}
