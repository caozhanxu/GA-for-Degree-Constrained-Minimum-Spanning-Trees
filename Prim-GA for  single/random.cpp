#include<iostream.h>
#include<stdlib.h>
#include"random.h"
#include"Save.h"

#include <stdio.h> 
#include <time.h> 
#define MAX 999
//using namespace std; 
random::random(int num)                       //���캯��
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
			G[i][j]=false;//Ĭ�϶�������
			if(i!=j)
				D[i][j]=MAX;//��ľ���Ĭ��Ϊ�����
			else
				D[i][j]=0;
		}
		d[i]=rand()%10;//����ÿ�����Ȩ�أ����Ϊ9
		v[i]=0;	//ÿ���ڵ�Ĭ��δ������
		visited[i]=0;	//ÿ���ڵ�Ĭ��δ��ѡ��
		L[i]=0;//δ������С��ʱ��ÿ���ڵ��ʼ������Ϊ0
	}	
}
random::random()                       //�޲εĹ��캯��
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
			G[i][j]=false;//Ĭ�϶�������
			if(i!=j)
				D[i][j]=MAX;//��ľ���Ĭ��Ϊ�����
			else
				D[i][j]=0;
		}
		d[i]=rand()%10;//����ÿ�����Ȩ�أ����Ϊ9
		v[i]=0;	//ÿ���ڵ�Ĭ��δ������
		visited[i]=0;	//ÿ���ڵ�Ĭ��δ��ѡ��
		L[i]=0;//δ������С��ʱ��ÿ���ڵ��ʼ������Ϊ0
	}	
}
random::~random()                           //��������
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

void random::generate()                       //�������ͼ,ע��strand������ʹ��!!!
{
	cout<<endl<<"��ʼ�����漴ͼ"<<endl;
	srand((unsigned)time(NULL));//srand()��������һ���Ե�ǰʱ�俪ʼ���������.
	//	Ӧ�÷���for��ѭ�����ǰ�� ��ȻҪ�ܳ�ʱ��ȴ�
	for(int i=0;i<N;i++)
	{
		int n=rand()%N;//����i����n-1��������ͨ
		for (int k=0;k<n;k++)
		{			
			int j=rand()%N;//�;�����Ǹ����������
			if(i!=j)
			{
				G[i][j]=true;
				G[j][i]=true;
				D2[i][j]=D2[j][i]=D[i][j]=D[j][i]=rand()%10+1;//���ñߵľ��룬�����Ϊ1-10
			}
		}
	
	
		
		//  d[i]=rand()%10;//����ÿ�����Ȩ�أ����Ϊ9
	}
	cout<<"���ͼ�������"<<endl<<endl;
}


void random::PrintAM() //��ӡ�ڽӾ���
{
    cout<<"�����ͼ���ڽӾ���A��"<<endl;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
			cout<<D[i][j]<<"\t";
		cout<<endl<<endl;
	}
}




void random::DFS(int n)                  //��ȱ���
{
	v[n]=1;//���øõ㱻����
	for(int i=0;i<N;i++)
		if(G[n][i]==true&&v[i]==0)
			DFS(i);
}



void random::IsConnected()                   //����Ƿ�Ϊ��ͨͼ
{
	bool flag=true;//flag����Ƿ���ͨ
	for(int i=0;i<N;i++)
	{
		if(v[i]==0)	
		{
			flag=false;
			cout<<"��V"<<i<<"���ڵ㲻��ͨ(��Χ��V0��V"<<N-1<<"),��ʼ����У���õ�"<<endl;
			adjust(i);	
			PrintAM();		
			flag=true;
		}   
	}
//	cout<<"�ٴν�����ȱ���"<<endl;
	for(int k=0;k<N;k++)
		v[k]=0;
	DFS(0);	
	for(int j=0;j<N;j++)
	{
		if(v[i]==0)	
			flag=false;
	}
	if(!flag) 
		cout<<"����DFS��ȱ�������ͼ������ͨ��!"<<endl<<endl;
	else
		cout<<"����DFS��ȱ�������ͼ����ͨ��!"<<endl<<endl;
}     

void random::adjust(int m)                   //����������ͨ�ĵ�
{
	//	srand((unsigned)time(NULL));
	int n=rand()%N;//����m����n-1��������ͨ
	for (int k=0;k<n;k++)
	{			
		//		srand((unsigned)time(NULL));
		int j=rand()%N;//�;�����Ǹ����������
		if(m!=j)
		{
			G[m][j]=true;
			G[j][m]=true;
			D[m][j]=D[j][m]=rand()%10+1;//���ñߵľ��룬�����Ϊ0~10
		}
	}
	
}

void random::Prim()                      //prim�㷨
{
	int k=0;
	sum=0;
	cout<<"��ʼ����prim�㷨����С������"<<endl;
	for(int l=1;l<N;l++)   //��ʼ����������
	{
		shortEdge[l].lowcost=D[0][l];
		shortEdge[l].adjvex=0;
		//	cout<<shortEdge[l].adjvex<<"\t";                   //��һ�γ�ʼ����ֵ
	}
	/*   	cout<<endl;
	for(int r=1;r<N;r++)		
	cout<<shortEdge[r].lowcost<<"\t";    
	cout<<endl;*/
	
	shortEdge[0].lowcost=0;//������0���뼯��
	for(int i=1;i<N;i++)
	{
		k=MinEdge(shortEdge,N);//Ѱ����̱ߵ��ڽӵ�
		cout<<"("<<shortEdge[k].adjvex<<","<<k<<")="<<shortEdge[k].lowcost<<endl;
		sum+=shortEdge[k].lowcost;
        shortEdge[k].lowcost=0;//��������shortEdge
		for(int j=1;j<N;j++)
		{
			if(D[k][j]<shortEdge[j].lowcost)
			{
				shortEdge[j].lowcost=D[k][j];
				shortEdge[j].adjvex=k;
			}
			//	cout<<shortEdge[j].adjvex<<"\t";            //���ԣ�����������
		}
		
		/*	cout<<endl;
		for(int y=1;y<N;y++)		
		cout<<shortEdge[y].lowcost<<"\t";            //���ԣ�����������
		
		cout<<endl;*/
	}
    cout<<"��СȨֵΪ"<<sum<<endl;
}

int  random::MinEdge(shortedge *shortEdge, int N)  //������shortEdge�в�����Сֵ
{
	
	int min,k;
	for(int j=1;j<N;j++)
	{
		if(shortEdge[j].lowcost!=0)
		{
			min=shortEdge[j].lowcost;
			//		cout<<"��ʼʱ��С���ڽӱ�lowcostΪ"<<min<<endl;
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
	//	cout<<"����С���ڽӱ�lowcostΪ"<<min<<endl;
	//	cout<<"����С���ڽӵ�Ϊ"<<k<<endl;
	return k;
}



//====================================================================================

void random::RePrim(int n)                              //�Ľ�prim�㷨
{
	/*int n;
	cout<<"���������ƶ����Ĵ�С��";
	cin>>n;
	cout<<"���øĽ���prim�㷨����С������"<<endl;*/
	int k=0;//��̱ߵĽڵ�
	sum=0;
	for(int l=1;l<N;l++)   //��ʼ����������
	{
		shortEdge[l].lowcost=D[0][l];
		shortEdge[l].adjvex=0;
	}
	shortEdge[0].lowcost=0;//������0���뼯��
	visited[0]=1;
	
	for(int i=1;i<N;i++)//ѡȡN-1����
	{
		k=MinEdge(shortEdge,N);//Ѱ����̱ߵ��ڽӵ�
	cout<<"("<<shortEdge[k].adjvex<<","<<k<<")="<<shortEdge[k].lowcost<<endl;
		L[shortEdge[k].adjvex]++;
		L[k]++;		
	if(shortEdge[k].lowcost==MAX)
		{
			cout<<"�ڵ�"<<k<<"�޷������������У���ͼ�޷����ɶ����Ƶ���С������"<<endl;
			sum=0;
			L[shortEdge[k].adjvex]--;//�����ñ�
			L[k]--;
			break;
		}
		//	cout<<"     \t L["<<shortEdge[k].adjvex<<"]="<<L[shortEdge[k].adjvex]<<endl;
		//	cout<<"     \t L["<<k<<"]="<<L[k]<<endl;		
else if(L[shortEdge[k].adjvex]<=n&&L[k]<=n)
		{
			//cout<<"����"<<endl;
			sum+=shortEdge[k].lowcost;
			shortEdge[k].lowcost=0;//��K����뼯��U
            visited[k]=1;
			for(int j=1;j<N;j++)//��������shortEdge
			{
				if(D[k][j]<shortEdge[j].lowcost)
				{
					shortEdge[j].lowcost=D[k][j];
					shortEdge[j].adjvex=k;					
				}
			}
		}
		else if(L[shortEdge[k].adjvex]>n)       //����ѡ��ĳ�㳬������ʱ�����µ�����������shortEdge
		{
			visited[shortEdge[k].adjvex]=2;//��ǳ����������ƵĽڵ�
			cout<<"��ʱV"<<shortEdge[k].adjvex<<"�ڵ��Ѿ������������������ñߣ�����ѡȡ"<<endl;
			L[shortEdge[k].adjvex]--;//�����ñ�
			L[k]--;
			i--;			
		//		cout<<"     \t L["<<shortEdge[k].adjvex<<"]="<<L[shortEdge[k].adjvex]<<endl;
		//		cout<<"     \t L["<<k<<"]="<<L[k]<<endl;			
			for(int j=1;j<N;j++)//��������shortEdge,
			{ 
				//���ҵ�δ��ѡ�е����ڽӵ�������������Ľڵ�
				if(shortEdge[j].lowcost!=0&&visited[shortEdge[j].adjvex]==2)
				{    
					shortEdge[j].lowcost=MAX;
					for(int p=0;p<N;p++)//��ʣ��δ��������U���ҳ���δѡ�е����С�ı�
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
	cout<<"��СȨֵΪ"<<sum<<endl<<endl;
//	PrintDegree();// ��ӡ�ڵ�Ͷ�Ӧ�Ķ���
} 
void random::PrintDegree()                                      //��ӡ����
{
	
	cout<<"��ӡ������ÿ���ڵ�Ķ���"<<endl<<"�ڵ�";
	for(int o=0;o<N;o++)//��ʣ��δ��������U���ҳ���С�ı�
	{
		cout<<"\t"<<o;		
	}
	cout<<endl;
	cout<<"����";
	for(int w=0;w<N;w++)//��ʣ��δ��������U���ҳ���С�ı�
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

void Save::ratio()//����û�н����ռ�ı���
{
	float ratios=0;
	ratios=no/num;
	cout<<"�ò����������ռ����Ϊ��"<<ratios<<endl;
}

void Save::InsertSort(int *r,int num)//ֱ�Ӳ�������
{
	for(int i=2;i<num;i++)
	{
		r[0]=r[i];
		for(int j=i-1;r[0]<r[j];j--)
			r[j+1]=r[j];
		r[j+1]=r[0];
	}
	
}


