#include <stdio.h>
#include <iostream>
using namespace std;

#define maxlength 20

int  N = 0;  //��Ʒ������(Ĭ��)
int capacity = 0; //����������(capacity)

double weight[maxlength] = {0.0}; //ÿ����Ʒ������
double value[maxlength] = {0.0}; //ÿ����Ʒ�ļ�ֵ
double density[maxlength] = {0.0}; //ÿ����Ʒ�ļ�ֵ�ܶ�
int x[maxlength] = {0};      //x[i]=1������Ʒi���뱳����0��������

int CurWeight = 0; //��ǰ���뱳������Ʒ������
int CurValue = 0;  //��ǰ���뱳������Ʒ�ܼ�ֵ

int BestValue = 0; //����ֵ����ǰ������ֵ����ʼ��Ϊ0
int BestX[maxlength];      //���Ž⣻BestX[i]=1������Ʒi���뱳����0��������

int count = 0;

//�綨�������������������Žڵ��ֵ���Ͻ�
double  profitBound(int currentLevel)
{
    double remainingCapacity = capacity - CurWeight;
    double profitBound = CurValue;

    //����ֵ�ܶ�˳�����ʣ������
    while(currentLevel <= N - 1 && weight[currentLevel] <= remainingCapacity )
    {
        remainingCapacity -= weight[currentLevel];
        profitBound += value[currentLevel];
        currentLevel++;
    }

    //��ȡ��һ�������һ����
    if(currentLevel <= N - 1 )
        profitBound += density[currentLevel] * remainingCapacity;

    printf("Now, bound is %1f\n", profitBound);

    return profitBound;
}

//currentLevel = 0 to N-1
void backtrack(int currentLevel)
{
    count++;//������

    //Ҷ�ӽڵ㣬������
    if (currentLevel > N - 1)
    {
        //����ҵ���һ�����ŵĽ�
        if (CurValue > BestValue)
        {
            //������ŵ�ֵ�ͽ�
            BestValue = CurValue;
            for (int i = 0; i < N; ++i)
                BestX[i] = x[i];
            return;
        }
    }
    else
    {
        //������ǰ�ڵ���ӽڵ㣺0 �����뱳��(����������1���뱳��(������)
        for (int i = 0; i <= 1; ++i)
        {
            
            if (i == 1) //���뱳��,������
            {
                //Լ���������ŵ���
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
            else //�����뱳����������
            {
                if(profitBound(currentLevel + 1) > BestValue)
                {
                    x[currentLevel] = 0;
                    backtrack(currentLevel + 1);
                }
            }
        }
        //PS:��������Ϊ�˸����ϵݹ���ݵķ�ʽ�����������
    }
}

//����ֵ�ܶȶ������ͼ�ֵ��������(ð������)
void sortByValuedensity(double weight[], double value[], double density[])
{
    for(int i = 0; i < N; i++)
    {
        density[i] = value[i] / weight[i];
    }

    int i, j;
    double temp=0.0;
    //���ñ��λ��sorted�Ƿ������
    bool sorted = true;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            if(density[j] < density[j+1])
            {
                //�������ѭ������δ����õ������ͽ����õı�Ǹ�Ϊfalse����������ѭ��
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
    printf("����ֵ��%d\n", BestValue);

    printf("���Ž⣺");
    for (int i = 0; i < N; i++)
    {
        printf("%-3d", BestX[i]);
    }
    printf("\n����backtrack���� %d ��", count);
}

int main(int argc, char *argv[])
{
    printf("����������");
    scanf("%d", &N);
    printf("��������");
    scanf("%d", &capacity);
    printf("���뱳��������");
    for(int i = 0; i < N; i++)
    {
        cin>>weight[i];
    }
    printf("���뱳����ֵ��");
    for(int i = 0; i < N; i++)
    {
        cin>>value[i];
    }
    sortByValuedensity(weight, value, density);
    backtrack(0);
    ouputAnswer();

    return 0;
}
//�����޽纯�����ܶ�����ĵ���backtrack�Ĵ�������