#include<iostream.h>
#include<stdlib.h>
#include <stdio.h> 
#include <time.h> 
#define MAX 100
struct shortEdge
{
	int lowcost;
	int adjvex;	
}shortEdge[];

class random   
{
public:
	
	bool**G;//G[i][j]=true��ʾ����i��j����
	int N;//ͼ�Ķ������
	int **D;//D[i][j]��ʾ��i��j�ľ���
	int *d;//d[i]��ʾ����i��Ȩ��
	int *v;//�ڵ��Ƿ񱻷��ʹ�
  
public:
    random(int num);//�вεĹ��캯��	
	~random(){}  //��������
	void  generate();//�����漴ͼ
	
	void PrintAM();//��ӡ�ڽӾ���
    void  DFS(int n);//��ȱ���
	void IsConnected();//�ж��Ƿ���ͨ��
	
    int MinEdge(struct shortEdge *shortEdge, int N);//Ѱ����̱ߵ��ڽӵ�K
    void Prim();//prim �㷨
	
	
};
void main()
{
	 
	int n;
	cout<<"���������ͼ��ĸ�����"<<endl<<endl;
	cin>>n;
	random random1(n);
	random1.generate();
	random1.PrintAM();
	random1.DFS(0);
	random1.IsConnected();
	random1.Prim();

}




random(int num)                       //���캯��
{
	srand((unsigned)time(NULL));
	N=num;
    G=new bool *[N];
	D=new int *[N];
    d=new int [N];
	v=new int [N];
	for(int i=0;i<N;i++)	
	{
		G[i]=new bool[N];
		D[i]=new int[N];
		for (int j=0;j<N;j++)
		{
			G[i][j]=false;//Ĭ�϶�������
			if(i!=j)
				D[i][j]=MAX;//��ľ���Ĭ��Ϊ�����
			else
				D[i][j]=0;
		}
		d[i]=rand()%10;//����ÿ�����Ȩ�أ����Ϊ9
		v[i]=0;
		
	}
	
	
}



/*random::~random()                           //��������
{
int i;
for(i=0;i<N;i++)
{
delete []G[i];
delete []D[i];
}
delete []G;
delete  []D;
delete  []d;
}  */



void generate()                       //�������ͼ
{
	cout<<endl<<"��ʼ������ɣ�"<<endl;
	srand((unsigned)time(NULL));//srand()��������һ���Ե�ǰʱ�俪ʼ���������.
	//	Ӧ�÷���for��ѭ�����ǰ�� ��ȻҪ�ܳ�ʱ��ȴ�
	for(int i=0;i<N;i++)
	{
		int n=rand()%N;//����i����n��������ͨ
		for (int k=0;k<n;k++)
		{			
			int j=rand()%N;//�;�����Ǹ����������
			if(i!=j)
			{
				G[i][j]=true;
				G[j][i]=true;
				D[i][j]=rand()%10+1;//���ñߵľ��룬�����Ϊ0~9
			}
		}
		
		//  d[i]=rand()%10;//����ÿ�����Ȩ�أ����Ϊ9
	}
	cout<<"���������ϣ�"<<endl<<endl;
}




void PrintAM() //��ӡ�ڽӾ���
{
    cout<<"�����ͼ���ڽӾ���A��"<<endl;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
			cout<<D[i][j]<<"\t";
		cout<<endl<<endl;
	}
}




void DFS(int n)                  //��ȱ���
{
	v[n]=1;
	for(int i=0;i<N;i++)
		if(G[n][i]==true&&v[i]==0)
			DFS(i);
}



void IsConnected()                   //����Ƿ�Ϊ��ͨͼ
{
	bool flag=true;//flag����Ƿ���ͨ
	for(int i=0;i<N;i++)
		if(v[i]==0)
		{	cout<<"��"<<i+1<<"���ڵ㲻��ͨ"<<endl;
		flag=false;
		}   
		if(!flag) 
			cout<<"��ͼ������ͨ��"<<endl;
		else
			cout<<"��ͼ����ͨ��"<<endl;
}     

void Prim()                      //prim�㷨
{
	int k=0;
	//shortEdge shortEdge=new shortEdge[N];
	for(int l=1;l<N;l++)   //��ʼ����������
	{
		shortEdge[l].lowcost=D[0][l];
		shortEdge[l].adjvex=0;
	}
	shortEdge[0].lowcost=0;
	for(int i=1;i<N;i++)
	{
		k=MinEdge(shortEdge,N);
		cout<<"("<<k<<shortEdge[k].adjvex<<")"<<shortEdge[k].lowcost;
        shortEdge[k].lowcost=0;
		for(int j=1;j<N;j++)
			if(D[k][j]<shortEdge[j].lowcost)
			{
				shortEdge[j].lowcost=D[k][j];
				shortEdge[j].adjvex=k;
			}
	}
	
}

int  MinEdge(shortEdge *shortEdge, int N)
{
	
	int min=0,k;
	for(int j=1;j<N;j++)
	{
		if(shortEdge[j].lowcost!=0)
			min=shortEdge[j].lowcost;
		break;
		
	}
	for(int i=1;i<N;i++)
	{	
		if(min>shortEdge[i].lowcost)
		{
			min=shortEdge[i].lowcost;
			k=i;
		}
	}
	return k;
}