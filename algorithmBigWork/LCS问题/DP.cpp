/*
二、问题：求两字符序列的最长公共字符子序列（LCS）

问题描述：字符序列的子序列是指从给定字符序列中随意地（不一定连续）去掉若干个字符（可能一个也不去掉）后所形成的字符序列。令给定的字符序列X=“x0，x1，…，xm-1”，序列Y=“y0，y1，…，yk-1”是X的子序列，存在X的一个严格递增下标序列<i0，i1，…，ik-1>，使得对所有的j=0，1，…，k-1，有xij=yj。例如，X=“ABCBDAB”，Y=“BCDB”是X的一个子序列。



三、分析

考虑最长公共子序列问题如何分解成子问题，设A=“a0，a1，…，am-1”，B=“b0，b1，…，bm-1”，并Z=“z0，z1，…，zk-1”为它们的最长公共子序列。不难证明有以下性质：

（1） 如果am-1=bn-1，则zk-1=am-1=bn-1，且“z0，z1，…，zk-2”是“a0，a1，…，am-2”和“b0，b1，…，bn-2”的一个最长公共子序列；

（2） 如果am-1!=bn-1，则若zk-1!=am-1，蕴涵“z0，z1，…，zk-1”是“a0，a1，…，am-2”和“b0，b1，…，bn-1”的一个最长公共子序列；

（3） 如果am-1!=bn-1，则若zk-1!=bn-1，蕴涵“z0，z1，…，zk-1”是“a0，a1，…，am-1”和“b0，b1，…，bn-2”的一个最长公共子序列。

这样，在找A和B的公共子序列时，如有am-1=bn-1，则进一步解决一个子问题，找“a0，a1，…，am-2”和“b0，b1，…，bm-2”的一个最长公共子序列；如果am-1!=bn-1，则要解决两个子问题，找出“a0，a1，…，am-2”和“b0，b1，…，bn-1”的一个最长公共子序列和找出“a0，a1，…，am-1”和“b0，b1，…，bn-2”的一个最长公共子序列，再取两者中较长者作为A和B的最长公共子序列。



四、求解

引进一个二维数组c[][]，用c[i][j]记录X[i]与Y[j] 的LCS 的长度，b[i][j]记录c[i][j]是通过哪一个子问题的值求得的，以决定搜索的方向。
我们是自底向上进行递推计算，那么在计算c[i,j]之前，c[i-1][j-1]，c[i-1][j]与c[i][j-1]均已计算出来。此时我们根据X[i] = Y[j]还是X[i] != Y[j]，就可以计算出c[i][j]。

问题的递归式写成：

if(s[i] == t[j])	
	lcs[i][j] = lcs[i-1][j-1] + 1;
else
	lcs[i][j] = max(lcs[i][j-1] , lcs[i-1][j]);
    
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <stack>

using namespace std;
const int maxn = 1005;

int nums;
int numt;
string s, t;
int lcs[maxn][maxn]; //lcs[i][j]代表两前缀s[1...i] & t[1...j]的LCS

int GetLCS()
{
    nums = s.length();
    numt = t.length();
    int i = 1, j = 1;
    string::iterator sp, tp;
    memset(lcs, 0, sizeof(lcs));
    for (sp = s.begin(); sp != s.end(); i++, sp++)
    {
        j = 1;
        for (tp = t.begin(); tp != t.end(); j++, tp++)
        {
            if (*sp == *tp)
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            else
                lcs[i][j] = max(lcs[i][j - 1], lcs[i - 1][j]);
        }
    }
    return lcs[nums][numt];
}

void print_LCS()
{
    stack<char> ans;
        int i = nums, j = numt;
        while (lcs[i][j])
        {
            if (lcs[i][j] == lcs[i - 1][j])
                i--;
            else if (lcs[i][j] == lcs[i][j - 1])
                j--;
            else
            {
                ans.push(s[i - 1]);
                i--;
                j--;
            }
        }
        while (!ans.empty())
        {
            printf("%c", ans.top());
            ans.pop();
        }
        cout<<endl;
}

int main()
{
    while (cin >> s >> t)
    {
        cout << GetLCS() << endl;
        print_LCS();
    }
    return 0;
}