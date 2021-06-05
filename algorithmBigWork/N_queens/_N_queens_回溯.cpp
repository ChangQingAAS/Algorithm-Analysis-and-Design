#include <stdio.h>  
   
#define N 8  
   
int Board[N][N];//���� 0��ʾ�հ� 1��ʾ�лʺ�  
int way;//�ڷŵķ�����  
   
   
//�ж��ܷ���(x,y)��λ�ðڷ�һ���ʺ�0�����ԣ�1����  
int Feasible(int row,int col)  
{  
    //λ�ò��Ϸ�  
    if(row>N || row<0 || col >N || col<0)  
        return 0;  
   
    //��λ���Ѿ��лʺ��ˣ�����  
    if(Board[row][col] != 0)  
    {   //�����г�ͻ�ж���Ҳ�����˸��жϣ����������Ϊ�����Ч��  
        return 0;  
    }  
   
    //  
    //�����ж��Ƿ�����еĳ�ͻ  
   
    //�к����Ƿ��ͻ  
    for(int i=0;i<N;++i)  
    {  
        if(Board[row][i] != 0 || Board[i][col]!=0)  
            return 0;  
    }  
   
    //б�߷����ͻ  
   
    for(int i=1;i<N;++i)  
    {  
/* i��ʾ�ӵ�ǰ��(row,col)���ĸ�б������չ�ĳ��� 
  
���Ͻ� \  / ���Ͻ�   i=2 
        \/           i=1 
        /\           i=1 
���½� /  \ ���½�   i=2 
*/  
        //���Ͻ�  
        if((row-i)>=0 && (col-i)>=0)    //λ�úϷ�  
        {  
            if(Board[row-i][col-i] != 0)//�˴����лʺ󣬳�ͻ  
                return 0;  
        }  
   
        //���½�  
        if((row+i)<N && (col-i)>=0)  
        {  
            if(Board[row+i][col-i] != 0)  
                return 0;  
        }  
   
        //���Ͻ�  
        if((row-i)>=0 && (col+i)<N)  
        {  
            if(Board[row-i][col+i] != 0)  
                return 0;  
        }  
   
        //���½�  
        if((row+i)<N && (col+i)<N)  
        {  
            if(Board[row+i][col+i] != 0)  
                return 0;  
        }  
    }  
   
    return 1; //���ᷢ����ͻ������1  
}  
   
   
//�ڷŵ�t���ʺ� ����1��ʼ  
void Queen(int t)  
{  
    //�ڷ���ɣ�������  
    if(t>N)  
    {  
        way++;  
        /*���N�ϴ��������������N��Сʱ��������������������� 
        for(int i=0;i<N;++i){ 
            for(int j=0;j<N;++j) 
                printf("%-3d",Board[i][j]); 
            printf("\n"); 
        } 
        printf("\n------------------------\n\n"); 
        */  
    }  
    else  
    {  
        for(int i=0;i<N;++i)  
        {  
            for(int j=0;j<N;++j)  
            {  
                //��i,j��λ�ÿ��԰ڷŻʺ󣬲���ͻ  
                if(Feasible(i,j))  
                {  
                    Board[i][j] = 1;  //�ڷŻʺ�t  
                    Queen(t+1);       //�ݹ�ڷŻʺ�t+1  
                    Board[i][j] = 0;  //�ָ�  
                }  
            }  
        }  
    }  
}  
   
//����num�Ľ׳�,num!  
int factorial(int num)  
{  
    if(num==0 || num==1)  
        return 1;  
    return num*factorial(num-1);  
}  
   
   
int main(int argc, char* argv[])  
{  
    //��ʼ��  
    for(int i=0;i<N;++i)  
    {  
        for(int j=0;j<N;++j)  
        {  
            Board[i][j]=0;  
        }  
    }  
   
    way = 0;  
   
    Queen(1);  //�ӵ�1���ʺ�ʼ�ڷ�  
   
    //���ÿ���ʺ󶼲�ͬ  
    printf("����ÿ���ʺ󶼲�ͬ���ڷŷ�����%d\n",way);//N=8ʱ, way=3709440 ��  
   
    //���ÿ���ʺ�һ������ô��Ҫ���� N����ȥ�ظ��Ĵ𰸣���Ϊ��ͬ����ÿ���ʺ���������λ�ã�  
    printf("����ÿ���ʺ󶼲�ͬ���ڷŷ�����%d\n",way/factorial(N));//N=8ʱ, way=3709440/8! = 92��  
   
    return 0;  
}  
/*�����⻹�и��ŵĽⷨ��
��������������ص�Լ��������
ÿ���ʺ��Ȼ�ڲ�ͬ����(��)��ÿ����(��)��ȻҲֻ��һ���ʺ�
�������ǾͿ��԰�N���ʺ�ŵ�N�����У�ʹ��Pos[i]��ʾ�ʺ�i��i���е�λ�ã�Ҳ�����кţ���i = 0 to N-1����
�����������ļ�࣬��Ϊ�ڵ���ӽڵ���Ŀ����٣��жϳ�ͻҲ���򵥡�*/