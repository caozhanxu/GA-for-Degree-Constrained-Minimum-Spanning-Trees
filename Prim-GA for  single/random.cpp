#include<iostream.h>
#include<stdlib.h>
#include"random.h"
#include"Save.h"

#include <stdio.h> 
#include <time.h> 
#define MAX 999
//using namespace std; 
random::random(int num)                       //构造函数
{
	N=num;
    G=new bool *[N];
	D=new int *[N];
	D2=new int *[N];
    d=new int [N];
	v=new int [N];
	visited=new int [N];
	L=new int[N];
	shortEdge=new shortedge[N];
	for(int i=0;i<N;i++)	
	{
		G[i]=new bool[N];
		D[i]=new int[N];
		D2[i]=new int[N];
		for (int j=0;j<N;j++)
		{
			G[i][j]=false;//默认都不相邻
			if(i!=j)
				D[i][j]=MAX;//点的距离默认为无穷大
			else
				D[i][j]=0;
		}
		d[i]=rand()%10;//设置每个点的权重，最大为9
		v[i]=0;	//每个节点默认未被访问
		visited[i]=0;	//每个节点默认未被选中
		L[i]=0;//未生成最小树时，每个节点初始度数均为0
	}	
}
random::random()                       //无参的构造函数
{
N=0;
}
void random::setN(int num)
{
	N=num;
    G=new bool *[N];
	D=new int *[N];
	D2=new int *[N];
    d=new int [N];
	v=new int [N];
	visited=new int [N];
	L=new int[N];
	shortEdge=new shortedge[N];
	for(int i=0;i<N;i++)	
	{
		G[i]=new bool[N];
		D[i]=new int[N];
		D2[i]=new int[N];
		for (int j=0;j<N;j++)
		{
			G[i][j]=false;//默认都不相邻
			if(i!=j)
				D[i][j]=MAX;//点的距离默认为无穷大
			else
				D[i][j]=0;
		}
		d[i]=rand()%10;//设置每个点的权重，最大为9
		v[i]=0;	//每个节点默认未被访问
		visited[i]=0;	//每个节点默认未被选中
		L[i]=0;//未生成最小树时，每个节点初始度数均为0
	}	
}
random::~random()                           //析构函数
{

for(int i=0;i<N;i++)
{

delete []G[i];
delete []D[i];
}
delete []G;
delete  []D;
delete  []d;
}  

void random::generate()                       //随机生成图,注意strand函数的使用!!!
{
	cout<<endl<<"开始生成随即图"<<endl;
	srand((unsigned)time(NULL));//srand()函数产生一个以当前时间开始的随机种子.
	//	应该放在for等循环语句前面 不然要很长时间等待
	for(int i=0;i<N;i++)
	{
		int n=rand()%N;//顶点i最多和n-1个顶点连通
		for (int k=0;k<n;k++)
		{			
			int j=rand()%N;//和具体的那个点进行连接
			if(i!=j)
			{
				G[i][j]=true;
				G[j][i]=true;
				D2[i][j]=D2[j][i]=D[i][j]=D[j][i]=rand()%10+1;//设置边的距离，随机域为1-10
			}
		}
	
	
		
		//  d[i]=rand()%10;//设置每个点的权重，最大为9
	}
	cout<<"随机图生成完毕"<<endl<<endl;
}


void random::PrintAM() //打印邻接矩阵
{
    cout<<"输出该图的邻接矩阵A："<<endl;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
			cout<<D[i][j]<<"\t";
		cout<<endl<<endl;
	}
}




void random::DFS(int n)                  //深度遍历
{
	v[n]=1;//设置该点被访问
	for(int i=0;i<N;i++)
		if(G[n][i]==true&&v[i]==0)
			DFS(i);
}



void random::IsConnected()                   //检测是否为连通图
{
	bool flag=true;//flag标记是否连通
	for(int i=0;i<N;i++)
	{
		if(v[i]==0)	
		{
			flag=false;
			cout<<"第V"<<i<<"个节点不连通(范围是V0至V"<<N-1<<"),开始进行校正该点"<<endl;
			adjust(i);	
			PrintAM();		
			flag=true;
		}   
	}
//	cout<<"再次进行深度遍历"<<endl;
	for(int k=0;k<N;k++)
		v[k]=0;
	DFS(0);	
	for(int j=0;j<N;j++)
	{
		if(v[i]==0)	
			flag=false;
	}
	if(!flag) 
		cout<<"根据DFS深度遍历，该图不是连通的!"<<endl<<endl;
	else
		cout<<"根据DFS深度遍历，该图是连通的!"<<endl<<endl;
}     

void random::adjust(int m)                   //调整不是连通的点
{
	//	srand((unsigned)time(NULL));
	int n=rand()%N;//顶点m最多和n-1个顶点连通
	for (int k=0;k<n;k++)
	{			
		//		srand((unsigned)time(NULL));
		int j=rand()%N;//和具体的那个点进行连接
		if(m!=j)
		{
			G[m][j]=true;
			G[j][m]=true;
			D[m][j]=D[j][m]=rand()%10+1;//设置边的距离，随机域为0~10
		}
	}
	
}

void random::Prim()                      //prim算法
{
	int k=0;
	sum=0;
	cout<<"开始根据prim算法求最小生成树"<<endl;
	for(int l=1;l<N;l++)   //初始化辅助数组
	{
		shortEdge[l].lowcost=D[0][l];
		shortEdge[l].adjvex=0;
		//	cout<<shortEdge[l].adjvex<<"\t";                   //第一次初始化的值
	}
	/*   	cout<<endl;
	for(int r=1;r<N;r++)		
	cout<<shortEdge[r].lowcost<<"\t";    
	cout<<endl;*/
	
	shortEdge[0].lowcost=0;//将顶点0加入集合
	for(int i=1;i<N;i++)
	{
		k=MinEdge(shortEdge,N);//寻找最短边的邻接点
		cout<<"("<<shortEdge[k].adjvex<<","<<k<<")="<<shortEdge[k].lowcost<<endl;
		sum+=shortEdge[k].lowcost;
        shortEdge[k].lowcost=0;//调整数组shortEdge
		for(int j=1;j<N;j++)
		{
			if(D[k][j]<shortEdge[j].lowcost)
			{
				shortEdge[j].lowcost=D[k][j];
				shortEdge[j].adjvex=k;
			}
			//	cout<<shortEdge[j].adjvex<<"\t";            //测试：输出调整后的
		}
		
		/*	cout<<endl;
		for(int y=1;y<N;y++)		
		cout<<shortEdge[y].lowcost<<"\t";            //测试：输出调整后的
		
		cout<<endl;*/
	}
    cout<<"最小权值为"<<sum<<endl;
}

int  random::MinEdge(shortedge *shortEdge, int N)  //在数组shortEdge中查找最小值
{
	
	int min,k;
	for(int j=1;j<N;j++)
	{
		if(shortEdge[j].lowcost!=0)
		{
			min=shortEdge[j].lowcost;
			//		cout<<"开始时最小边邻接边lowcost为"<<min<<endl;
			k=j;
			break;
		}
		
	}
	for(int i=1;i<N;i++)
	{	
		if(shortEdge[i].lowcost!=0&&min>shortEdge[i].lowcost)
		{
			min=shortEdge[i].lowcost;
			k=i;
		}
	}
	//	cout<<"新最小边邻接边lowcost为"<<min<<endl;
	//	cout<<"新最小边邻接点为"<<k<<endl;
	return k;
}



//====================================================================================

void random::RePrim(int n)                              //改进prim算法
{
	/*int n;
	cout<<"请输入限制度数的大小：";
	cin>>n;
	cout<<"采用改进的prim算法求最小生成树"<<endl;*/
	int k=0;//最短边的节点
	sum=0;
	for(int l=1;l<N;l++)   //初始化辅助数组
	{
		shortEdge[l].lowcost=D[0][l];
		shortEdge[l].adjvex=0;
	}
	shortEdge[0].lowcost=0;//将顶点0加入集合
	visited[0]=1;
	
	for(int i=1;i<N;i++)//选取N-1条边
	{
		k=MinEdge(shortEdge,N);//寻找最短边的邻接点
	cout<<"("<<shortEdge[k].adjvex<<","<<k<<")="<<shortEdge[k].lowcost<<endl;
		L[shortEdge[k].adjvex]++;
		L[k]++;		
	if(shortEdge[k].lowcost==MAX)
		{
			cout<<"节点"<<k<<"无法加入生成树中，该图无法生成度限制的最小生成树"<<endl;
			sum=0;
			L[shortEdge[k].adjvex]--;//撤销该边
			L[k]--;
			break;
		}
		//	cout<<"     \t L["<<shortEdge[k].adjvex<<"]="<<L[shortEdge[k].adjvex]<<endl;
		//	cout<<"     \t L["<<k<<"]="<<L[k]<<endl;		
else if(L[shortEdge[k].adjvex]<=n&&L[k]<=n)
		{
			//cout<<"正常"<<endl;
			sum+=shortEdge[k].lowcost;
			shortEdge[k].lowcost=0;//将K点加入集合U
            visited[k]=1;
			for(int j=1;j<N;j++)//调整数组shortEdge
			{
				if(D[k][j]<shortEdge[j].lowcost)
				{
					shortEdge[j].lowcost=D[k][j];
					shortEdge[j].adjvex=k;					
				}
			}
		}
		else if(L[shortEdge[k].adjvex]>n)       //当所选边某点超出度数时，重新调整调整数组shortEdge
		{
			visited[shortEdge[k].adjvex]=2;//标记超过度数限制的节点
			cout<<"此时V"<<shortEdge[k].adjvex<<"节点已经超出最大度数，撤销该边，重新选取"<<endl;
			L[shortEdge[k].adjvex]--;//撤销该边
			L[k]--;
			i--;			
		//		cout<<"     \t L["<<shortEdge[k].adjvex<<"]="<<L[shortEdge[k].adjvex]<<endl;
		//		cout<<"     \t L["<<k<<"]="<<L[k]<<endl;			
			for(int j=1;j<N;j++)//调整数组shortEdge,
			{ 
				//先找到未被选中但是邻接点是已满度数点的节点
				if(shortEdge[j].lowcost!=0&&visited[shortEdge[j].adjvex]==2)
				{    
					shortEdge[j].lowcost=MAX;
					for(int p=0;p<N;p++)//从剩下未满度数的U中找出与未选中点的最小的边
					{
						if(visited[p]==1&&D[p][j]<=shortEdge[j].lowcost)
						{
							shortEdge[j].lowcost=D[p][j];
							shortEdge[j].adjvex=p;  
						}
					}	
					
				}
			}		
		}
		
	}
	cout<<"最小权值为"<<sum<<endl<<endl;
//	PrintDegree();// 打印节点和对应的度数
} 
void random::PrintDegree()                                      //打印度数
{
	
	cout<<"打印出最终每个节点的度数"<<endl<<"节点";
	for(int o=0;o<N;o++)//从剩下未满度数的U中找出最小的边
	{
		cout<<"\t"<<o;		
	}
	cout<<endl;
	cout<<"度数";
	for(int w=0;w<N;w++)//从剩下未满度数的U中找出最小的边
	{
		cout<<"\t"<<L[w];		
	}
	cout<<endl;
}

//==============================================================================

Save::Save(int n)
{
	num=n;
	result=new int [num];
	for(int i=0;i<num;i++)
		result[i]=0;
	no=0;
	
}

void Save::ratio()//计算没有结果所占的比例
{
	float ratios=0;
	ratios=no/num;
	cout<<"得不到的情况所占比例为："<<ratios<<endl;
}

void Save::InsertSort(int *r,int num)//直接插入排序
{
	for(int i=2;i<num;i++)
	{
		r[0]=r[i];
		for(int j=i-1;r[0]<r[j];j--)
			r[j+1]=r[j];
		r[j+1]=r[0];
	}
	
}


