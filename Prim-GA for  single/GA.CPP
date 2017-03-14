#include<iostream.h>
#include<stdlib.h>
#include <stdio.h> 
#include <time.h>
#include <fstream.h>
#include <cmath>
#include <iomanip.h>
#include"GA.h" 
#define MAX2 9000

GA::GA(int n,int degree)
{
    
	gen=5000;//迭代次数
	p_crossover=0.4;
	p_mutation=0.1;
	
	N=n;
	pop_size=2*N;
	deg=degree;
	
	best=200000;
	worst=0;
	
	D=new int *[N];
	pop=new int *[pop_size];
	bestPrufer=new int [N-2];
	objvalue=new double [pop_size];
	fitvalue=new double [pop_size];
	
	for(int i=0;i<pop_size;i++)	
	{
	
        pop[i]=new int[N];
		
        for(int j=0;j<N-2;j++)//前N-2列为prufer编码，
		{
			//pop[i][j]=rand()%N+1;//对个体每列随机赋值为1-N之间
            pop[i][j]=(int)myu(1,N);//对个体每列随机赋值为1-N之间
            bestPrufer[j]=0;
		}
		Check_Modify(pop[i]);//对初试产生的prufer编码进行检查和校对
		
		for(int k=N-2;k<N;k++)//第N-1列为目标函数值，第N列为适应度值,默认为0
		{
			pop[i][k]=0;
		}
		
		objvalue[i]=fitvalue[i]=0;
	}
		for (int m=0;m<N;m++)//邻接矩阵代表的赋权值图先默认为0
		{
           	D[m]=new int[N];
			for(int n=0;n<N;n++)
		    	D[m][n]=0;
			
		}  
}



double GA::myu(double a,double b)    //在a与b之间随机产生一个小数
{
	
	double y;
	y = (double)rand()/(RAND_MAX);
	return (a+(b-a)*y)+0.5; 
}

void GA::PrintAM() //打印邻接矩阵
{
    cout<<"输出种群所对应的邻接矩阵A："<<endl;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
			cout<<D[i][j]<<"\t";
		cout<<endl<<endl;
	}
}
void GA::PrintPop()//打印种群
{
	cout<<"输出该图的初始pop("<<N-2<<"列)："<<endl;
	for(int i=0;i<pop_size;i++)
	{
		for(int j=0;j<N-1;j++)
			cout<<pop[i][j]<<"\t";
		cout<<endl<<endl;
	}
}



void GA::PrintObjvalueAndFitvalue()//打印目标函数值和适应度值
{
	cout<<"输出种群的目标函数值和适应度值"<<endl;
	for(int i=0;i<pop_size;i++)
		cout<<i+1<<"\t"<<objvalue[i]<<"\t"<<setprecision(10)<<fitvalue[i]<<endl;
}

void GA::Check_Modify(int *b)//对prufer进行检验和修改超度的码
{
		int flag=0;
	int* degree= new int[N];
	for(int i=0;i<N;i++)
		degree[i]=1;//因为prufer中各个数的出现次数为对应度-1，故先默认度均为1，
	
	for(int j=0;j<N-2;j++)//前N-2列为prufer编码
	{
		degree[b[j]-1]++;// a[j]-1,是因为degree下标是从0开始的，而prufer均为1~N
	}
flag=checkDeg(b);//进行检验
	while(flag==1)
	{
		flag=0;
		for(int k=0;k<N-2;k++)
		{
			if(degree[b[k]-1]>deg)
			{
                degree[b[k]-1]--;//超出的先进行度-1，再随机替换成一个数
				b[k]=(int)myu(1,N);
                 degree[b[k]-1]++;//对替换后的数值进行度+1

			}
			
		}
		flag=checkDeg(b);//纠正后再次检验
	}
	delete []degree;//释放内存
	
}

void GA::Check_Chg(int *b)//对prufer进行检验和和更换prufer
{
	int flag=0;
	flag=checkDeg(b);
	//	cout<<flag<<endl<<endl;
	while(flag==1)
	{
		flag=0;
		for(int i=0;i<N-2;i++)//重新对前N-2列赋值为prufer编码，
		{
            b[i]=(int)myu(1,N);//对个体每列随机赋值为1-N之间
		}
		flag=checkDeg(b);
		
	}
	
	
}
int GA::checkDeg(int *a)////检查prufer编码是否超过度数限制，是则返回1
{
	//	cout<<a[0]<<endl;
	
	int flag=0;
	int* degree= new int[N];
	for(int i=0;i<N;i++)
		degree[i]=1;//因为prufer中各个数的出现次数为对应度-1，故先默认度均为1，
	
	for(int j=0;j<N-2;j++)//前N-2列为prufer编码
	{
		degree[a[j]-1]++;// a[j]-1,是因为degree下标是从0开始的，而prufer均为1~N
		
		
		if(degree[a[j]-1]>deg)
		{
			//	cout<<a[j]<<"的度数为"<<degree[a[j]-1]<<"对该行进行校正"<<endl;
			
			flag=1;
			break;//一旦发现有度超出，结束循环
		}
	}
		delete []degree;//释放内存
	return flag;
}

void GA::decodeSide(int a[],int b[],int x,int y,int *A,int *B)//解码一条边,详细说明见prufer解码过程文档
{
	*A=0;
	*B=0;
	
	*A=pop[x][y]; 
  	 a[*A-1]--;
	 
	 for(int i=0;i<N;i++)
	 {
		 if(b[i]>0)
		 {
			 *B=i+1; 
			 b[i]--;
			 break;
		 }
	 }
	 if(a[*A-1]==0)
		 b[*A-1]++;	
}


void GA::calobjvalue()//计算每个个体的目标函数值第N-1列
{
    int *p=new int [N];
    int *pp=new int [N];
	int pointA=0,pointB=0;//解码时依次求边的值
	
	
	for(int i=0;i<pop_size;i++)//计算pop_size行的数据
	{
		objvalue[i]=0;
		pop[i][N-2]=0;
		//步骤一
		for(int w=0;w<N;w++)//默认两个数组初值各为0和1
		{
			p[w]=0;	
			pp[w]=1;
		}
		
		for(int j=0;j<N-2;j++)//根据对应的prufer码，生成对应两个数组
		{
			p[pop[i][j]-1]++;;
			pp[pop[i][j]-1]=0;
			
		}
		//步骤二
		for(int k=0;k<N-2;k++)//总共需要生成N-1条边,先生成N-2条边
		{
            decodeSide(p,pp,i,k,&pointA,&pointB);
			//	cout<<"第"<<i+1<<"个的第"<<k+1<<"条边<"<<pointA<<","<<pointB<<">="<<D[pointA-1][pointB-1]<<endl;
			pop[i][N-2]+=D[pointA-1][pointB-1];	
			objvalue[i]+=D[pointA-1][pointB-1];
		}
		//步骤三,求最后第N-1条边
		for(int l=0;l<N;l++)
		{
			if(pp[l]!=0)
			{
				pointA=l+1;
				pp[l]=0;
				break;
			}
		}
		for(int m=0;m<N;m++)
		{
			if(pp[m]!=0)
			{
				pointB=m+1;
				pp[m]=0;
				break;
			}
		}
		pop[i][N-2]+=D[pointA-1][pointB-1];	
		//		cout<<"第"<<i+1<<"个的第"<<N-1<<"条边<"<<pointA<<","<<pointB<<">="<<D[pointA-1][pointB-1]<<endl<<endl;
		objvalue[i]+=D[pointA-1][pointB-1];	
		pointA=pointB=0;
	}
	delete []p;
	delete []pp;
}


void GA::calfitvalue()    //计算每个个体的适应度值第N列
{		
	int max=999*(N-1)/2;
	double sum_fit=0;//适应度总值暂定为int型，以后随测试节点增大能更改
	for(int i=0;i<pop_size;i++)//求出每个个体的适应值以及求适应值总值
	{
		//	fitvalue[i]=pop[i][N-1]=MAX2-pop[i][N-2];//用无穷大减去目标值，结果越大表明适应度越好
		
        fitvalue[i]=worst-fitvalue[i];//目标值的倒数，结果越大表明适应度越好
		sum_fit+=fitvalue[i];
	}
	fitvalue[0]/=sum_fit;
	for(int j=1; j<pop_size; j++)
	{
		//	pop[j][N-1]=pop[j][N-1]/sum_fit;      //归一化（转化为每个染色体的被选择概率）
		//	pop[j][N-1]=pop[j][N-1]+pop[j-1][N-1];    //转化为累积被选择概率
		fitvalue[j]=fitvalue[j]/sum_fit;      //归一化（转化为每个染色体的被选择概率）
		fitvalue[j]=fitvalue[j]+fitvalue[j-1];    //转化为累积被选择概率
	}
	
	//	pop[pop_size-1][N-1]=1;
	fitvalue[pop_size-1]=1;
	
}


void GA::calbest()//求种群中最小的目标值以及对应的prufer编码
{
	double best2;
	best2=objvalue[0];
	int k=0;//最小的目标值是第几个
	for(int i=1;i<pop_size;i++)//找出最小值以及属于第几个个体
	{
		if(best2>objvalue[i])
		{
			best2=objvalue[i];
			k=i;
		}
		if(worst<objvalue[i])
			worst=objvalue[i];

	}
	if(best>best2)
	{
		best=best2;
	for(int j=0;j<N-2;j++)
		bestPrufer[j]=pop[k][j];//保存最优个体
	}	
}


void GA::calobj_sort()//计算目标函数值后进行排序
{
		calobjvalue();
	int *temp=new int [N];
	double temp2;
	for(int i=1;i<pop_size;i++)//直接插入排序
	{
		temp2=objvalue[i];//暂存待插目标值
		for(int j=0;j<N;j++)//保存该目标值对应的prufer编码
			temp[j]=pop[i][j];
		
		for(int k=i-1;temp2<objvalue[k];k--)//寻找插入位置
		{
			objvalue[k+1]=objvalue[k];//记录后移
			pop[k+1][N-2]=pop[k][N-2];
			for(int m=0;m<N;m++)
				pop[k+1][m]=pop[k][m];
		}
		objvalue[k+1]=temp2;
		pop[k+1][N-2]=temp2;
		for(int n=0;n<N;n++)
				pop[k+1][n]=temp[n];

	}
	delete []temp;
}


void GA::selection()  //选择算子
{
	for(int m=0;m<N-2;m++)//第一个个体为上一代的最优个体
		pop[0][m]=bestPrufer[m];
	double r;
	for(int i=1;i<pop_size; i++) //第一个即下标为0的已经被赋值，所以从下标的1开始
	{
		r = myu(0, 1);
		for(int j = 0;j<pop_size; j++) //选择染色体
		{
			if(r <= fitvalue[j])          //选择第j个染色体并作为下一代第i只染色体
			{
				for(int k=0;k<N-2;k++)
					pop[i][k] = pop[j][k];
				break;
			}
		}
	}
}


void GA::crossover()  //交叉算子
{
	int   i, j, jj, k,n;
	int *temp=new int[N];
    int num=(int)(pop_size*p_crossover/2+0.5); //加0.5起到四舍五入的作用
	for(i = 1; i<=num; i++)         //总共选择2×（POP_SIZE*P_CROSSOVER/2+0.5）个染色体进行交叉
	{
		j = (int)myu(0,pop_size-1);
		jj = (int)myu(0,pop_size-1);
		n = (int)myu(0,N-2);         //确定交叉点n
		
		for(k=n; k<N-2; k++)   //只交换交叉点n后面的基因
		{
			temp[k] = pop[j][k];
			pop[j][k] = pop[jj][k];
			pop[jj][k]=temp[k];
		}
		Check_Modify(pop[j]);//对交叉完的两个染色体进行度的检验
		Check_Modify(pop[jj]);
		
	}
	delete []temp;
}



void GA::mutation()//变异算子
{
	double r=0;
	for(int i=1; i<pop_size; i++) 
	{ 
		for(int k=0; k<N-2; k++ )
		{
			r=myu(0,1)-0.5;
			if(r<=p_mutation)
			{
				pop[i][k]=(int)myu(1,N);//进行随机变异
			}
			
		}
		Check_Modify(pop[i]);//检查是否超过度数，
	}		 	
}


void GA::test_GA()
{
	
	clock_t start, finish; 
	double duration;
	start = clock(); 
		ofstream fs;
		fs.open("Result.txt",ios::trunc);
	
	
	for(int i = 1; i <=gen; i++) 
	{
		calobjvalue();
			calbest();
		calfitvalue();
 //PrintPop();//查看种群的prufer编码
//		cout<<"迭代次数="<<i<<"时"<<endl;
//	 PrintObjvalueAndFitvalue();//查看是否有目标值和适应度生成

		selection();
	crossover();

//	calobj_sort();
//	 PrintPop();
		mutation();
		
	//	cout<<"迭代次数="<<i<<endl;
	//	cout<<"目前找到的最优函数值为="<<setprecision(10)<<best<<endl<<endl<<endl;
		fs<<i<<" "<<best<<endl;
	}
    finish = clock();
	duration = (double)(finish - start)/CLOCKS_PER_SEC;
//	cout<<"运算CPU时间为："<<duration<<"秒"<<endl;
	fs.close();
	
}
