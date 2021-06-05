/*
下次写代码题时，把题目和自己的感悟、思路贴进来，节省回想原题的时间
*/

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct point{
    int x,y;
    point(int a,int b):x(a),y(b){}
};

const int maxn = 1000 + 5;
char map[maxn][maxn];//存储地图

int d[8]={0,1,0,-1,1,0,-1,0};
int isvisited[maxn][maxn];//给搜索过的位置作标记
int n,m,i,j;
int ans[maxn]={0};//存储第t次搜索的结果

int bfs(int x,int y,int t)//t表示第几次搜索
{
    int sum = 1;//这次访问搜索到了几个点
    queue<point> q;
    point p(x,y);
    q.push(p);
    while(!q.empty())
    {
        p = q.front();
        q.pop();
        for(i=0;i<8;i+=2)
        {
            int tx=p.x+d[i];
            int ty=p.y+d[i+1];
            if(tx>0&&tx<=n&&ty>0&&ty<=n&&map[p.x][p.y]!=map[tx][ty]&&isvisited[tx][ty]==0)
            {
                point p1(tx,ty);
                q.push(p1);
                isvisited[tx][ty]=t;//记录第几次搜索访问到这个点
                sum++;
            }
        }
    }
    return sum;
}

int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)
        cin>>map[i];
    for(int k=1;k<=m;k++)
    {
        int x,y;
        cin>>x>>y;
        if(!isvisited[x][y])//如果该格子没有被搜索过，就要搜索一遍
        {
            isvisited[x][y]=k;
            ans[k]=bfs(x,y,k);
            cout<<ans[k]<<endl;
        }
        else//被搜索过的话，直接输出结果
        {
            int t=isvisited[x][y];//取出第几次访问到这个点，然后
            ans[m]=ans[t];
            cout<<ans[m]<<endl;
        }
    }
    return 0;
}

