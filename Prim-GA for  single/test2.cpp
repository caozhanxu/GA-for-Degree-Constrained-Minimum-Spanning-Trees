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
	
	bool**G;//G[i][j]=true表示顶点i和j相邻
	int N;//图的顶点个数
	int **D;//D[i][j]表示点i和j的距离
	int *d;//d[i]表示顶点i的权重
	int *v;//节点是否被访问过
  
public:
    random(int num);//有参的构造函数	
	~random(){}  //析构函数
	void  generate();//生成随即图
	
	void PrintAM();//打印邻接矩阵
    void  DFS(int n);//深度遍历
	void IsConnected();//判断是否连通；
	
    int MinEdge(struct shortEdge *shortEdge, int N);//寻找最短边的邻接点K
    void Prim();//prim 算法
	
	
};
void main()
{
	 
	int n;
	cout<<"请输入随机图点的个数："<<endl<<endl;
	cin>>n;
	random random1(n);
	random1.generate();
	random1.PrintAM();
	random1.DFS(0);
	random1.IsConnected();
	random1.Prim();

}




random(int num)                       //构造函数
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
			G[i][j]=false;//默认都不相邻
			if(i!=j)
				D[i][j]=MAX;//点的距离默认为无穷大
			else
				D[i][j]=0;
		}
		d[i]=rand()%10;//设置每个点的权重，最大为9
		v[i]=0;
		
	}
	
	
}



/*random::~random()                           //析构函数
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



void generate()                       //随机生成图
{
	cout<<endl<<"开始随机生成！"<<endl;
	srand((unsigned)time(NULL));//srand()函数产生一个以当前时间开始的随机种子.
	//	应该放在for等循环语句前面 不然要很长时间等待
	for(int i=0;i<N;i++)
	{
		int n=rand()%N;//顶点i最多和n个顶点连通
		for (int k=0;k<n;k++)
		{			
			int j=rand()%N;//和具体的那个点进行连接
			if(i!=j)
			{
				G[i][j]=true;
				G[j][i]=true;
				D[i][j]=rand()%10+1;//设置边的距离，随机域为0~9
			}
		}
		
		//  d[i]=rand()%10;//设置每个点的权重，最大为9
	}
	cout<<"随机生成完毕！"<<endl<<endl;
}




void PrintAM() //打印邻接矩阵
{
    cout<<"输出该图的邻接矩阵A："<<endl;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
			cout<<D[i][j]<<"\t";
		cout<<endl<<endl;
	}
}




void DFS(int n)                  //深度遍历
{
	v[n]=1;
	for(int i=0;i<N;i++)
		if(G[n][i]==true&&v[i]==0)
			DFS(i);
}



void IsConnected()                   //检测是否为连通图
{
	bool flag=true;//flag标记是否连通
	for(int i=0;i<N;i++)
		if(v[i]==0)
		{	cout<<"第"<<i+1<<"个节点不连通"<<endl;
		flag=false;
		}   
		if(!flag) 
			cout<<"该图不是连通的"<<endl;
		else
			cout<<"该图是连通的"<<endl;
}     

void Prim()                      //prim算法
{
	int k=0;
	//shortEdge shortEdge=new shortEdge[N];
	for(int l=1;l<N;l++)   //初始化辅助数组
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