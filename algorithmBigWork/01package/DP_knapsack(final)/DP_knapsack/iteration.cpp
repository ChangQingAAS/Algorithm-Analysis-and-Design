/**
 * 动态规划-0/1背包问题 迭代实现
 */

#ifndef _KNAPSACK_H_
#define _KNAPSACK_H_
#include <iostream>
#include <assert.h>
#endif
using namespace std;

#define F_ROW 101
#define F_COLUMN 6500000

long_d f[F_ROW][F_COLUMN];
void Knapsack();
void Traceback();
void Init_f();

void Init_f(){
    for(long_d i = 0; i < F_ROW; i++){
        for(long_d j = 0; j < F_COLUMN; j++){
            f[i][j] = 0;
        }
    }
}

void Knapsack(){

    long_d yMax = min(w[n] - 1, c);
    /* y < w[n]， f(n, y) = 0 */
    for(long_d y = 0; y <= yMax; y++){
        assert(y <= F_COLUMN); 
        f[n][y] = 0;
    }
    /* y >= w[n], f(n, y) = 1 */
    for(long_d y = w[n]; y <= c; y++){
        assert(y <= F_COLUMN); 
        f[n][y] = p[n];
    }
    
    for(long_d i = n - 1; i > 1; i--){
        yMax = min(w[i] - 1, c);
        for(long_d y = 0; y <= yMax; y++){
            /* y < w[i], f(i, y) = f(i + 1, y) */ 
            assert(y <= F_COLUMN); 
            f[i][y] = f[i + 1][y];
        }
        for(long_d y = w[i]; y <= c; y++){
            /* y >= w[i], f(i, y) = max(f(i + 1, y), f(i + 1, y - w[i]) + p[i]) */
            assert(y <= F_COLUMN); 
            f[i][y] = max(f[i + 1][y], f[i + 1][y - w[i]] + p[i]);
        }
    }
    /* there is no need to calculate f[1][0 -> c-1] */
    f[1][c] = f[2][c];
    if(c >= w[1]) f[1][c] = max(f[1][c], f[2][c - w[1]] + p[1]);

    res_optimum[file_index] = f[1][c];
}

void Traceback(){
    
    long_d y = c;
    for(long_d i = 1; i < n; i++){
        if(f[i][y] == f[i + 1][y]) res[i] = 0;
        else{
            res[i] = 1;
            y -= w[i];
        }
    }
    res[n] = (f[n][y] > 0) ? 1 : 0;
}
