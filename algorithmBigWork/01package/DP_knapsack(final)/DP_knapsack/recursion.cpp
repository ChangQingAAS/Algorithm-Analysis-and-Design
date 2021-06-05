/**
 * 动态规划-0/1背包问题 递归实现
 */

#ifndef _KNAPSACK_H_
#define _KNAPSACK_H_
#include <iostream>
#include <ctime>
using namespace std;

void result();
long_d DP_F(int i, int y);  // i: index of items, y: current capacity of backpack


long_d DP_F(int i, int y){
    if(i == n) return (y < w[n] ? 0 : p[n]);
    if(y < w[i]){
        total_recurse_time++; 
        return DP_F(i + 1, y);
    }
    total_recurse_time += 2;
    return max(DP_F(i + 1, y), DP_F(i + 1, y - w[i]) + p[i]);
}

void result(){
    res_optimum[file_index] = DP_F(1, c);
    int r = c;
    for(int i = 1; i < n; i++){
        if(DP_F(i, r) == DP_F(i + 1, r)){
            res[i] = 0;
        }
        else{
            res[i] = 1;
            r -= w[i];
        }
    }
    if(DP_F(n, r)) res[n] = 1;
    else res[n] = 0;
}

#endif