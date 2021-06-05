#include <stdio.h>
#include <iostream>
using namespace std;

#define maxlength 20

int  N = 0;  //物品的数量(默认)
int capacity = 0; //背包的容量(capacity)

double weight[maxlength] = {0.0}; //每个物品的重量
double value[maxlength] = {0.0}; //每个物品的价值
double density[maxlength] = {0.0}; //每个物品的价值密度
int x[maxlength] = {0};      //x[i]=1代表物品i放入背包，0代表不放入

int CurWeight = 0; //当前放入背包的物品总重量
int CurValue = 0;  //当前放入背包的物品总价值

int BestValue = 0; //最优值；当前的最大价值，初始化为0
int BestX[maxlength];      //最优解；BestX[i]=1代表物品i放入背包，0代表不放入

int count = 0;

//界定函数，返回子树中最优节点的值的上界
double  profitBound(int currentLevel)
{
    double remainingCapacity = capacity - CurWeight;
    double profitBound = CurValue;

    //按价值密度顺序填充剩余容量
    while(currentLevel <= N - 1 && weight[currentLevel] <= remainingCapacity )
    {
        remainingCapacity -= weight[currentLevel];
        profitBound += value[currentLevel];
        currentLevel++;
    }

    //读取下一个对象的一部分
    if(currentLevel <= N - 1 )
        profitBound += density[currentLevel] * remainingCapacity;

    printf("Now, bound is %1f\n", profitBound);

    return profitBound;
}

//currentLevel = 0 to N-1
void backtrack(int currentLevel)
{
    count++;//计数器

    //叶子节点，输出结果
    if (currentLevel > N - 1)
    {
        //如果找到了一个更优的解
        if (CurValue > BestValue)
        {
            //保存更优的值和解
            BestValue = CurValue;
            for (int i = 0; i < N; ++i)
                BestX[i] = x[i];
            return;
        }
    }
    else
    {
        //遍历当前节点的子节点：0 不放入背包(右子树），1放入背包(左子树)
        for (int i = 0; i <= 1; ++i)
        {
            
            if (i == 1) //放入背包,左子树
            {
                //约束条件：放的下
                if (CurWeight + weight[currentLevel] <= capacity)
                {
                    x[currentLevel] = 1;
                    CurWeight += weight[currentLevel];
                    CurValue += value[currentLevel];
                    backtrack(currentLevel + 1);
                    x[currentLevel] = 0;
                    CurWeight -= weight[currentLevel];
                    CurValue -= value[currentLevel];
                }
                
            }
            else //不放入背包，右子树
            {
                if(profitBound(currentLevel + 1) > BestValue)
                {
                    x[currentLevel] = 0;
                    backtrack(currentLevel + 1);
                }
            }
        }
        //PS:上述代码为了更符合递归回溯的范式，并不够简洁
    }
}

//按价值密度对重量和价值进行排序(冒泡排序)
void sortByValuedensity(double weight[], double value[], double density[])
{
    for(int i = 0; i < N; i++)
    {
        density[i] = value[i] / weight[i];
    }

    int i, j;
    double temp=0.0;
    //设置标记位，sorted是否排序好
    bool sorted = true;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            if(density[j] < density[j+1])
            {
                //如果本轮循环，有未排序好的数，就将设置的标记改为false，继续下轮循环
                sorted = false;
                temp = density[j];
                density[j] = density[j+1];
                density[j+1] = temp; 

                temp = weight[j];
                weight[j] = weight[j+1];
                weight[j+1] = temp; 

                temp = value[j];
                value[j] = value[j+1];
                value[j+1] = temp; 

            }
        }
        if(sorted) break;
    }
    return;
}

void ouputAnswer()
{
    printf("最优值：%d\n", BestValue);

    printf("最优解：");
    for (int i = 0; i < N; i++)
    {
        printf("%-3d", BestX[i]);
    }
    printf("\n进入backtrack函数 %d 次", count);
}

int main(int argc, char *argv[])
{
    printf("背包数量：");
    scanf("%d", &N);
    printf("总容量：");
    scanf("%d", &capacity);
    printf("输入背包重量：");
    for(int i = 0; i < N; i++)
    {
        cin>>weight[i];
    }
    printf("输入背包价值：");
    for(int i = 0; i < N; i++)
    {
        cin>>value[i];
    }
    sortByValuedensity(weight, value, density);
    backtrack(0);
    ouputAnswer();

    return 0;
}
//不加限界函数和密度排序的调用backtrack的次数更多