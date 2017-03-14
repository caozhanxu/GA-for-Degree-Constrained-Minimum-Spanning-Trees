#include<iostream.h>
#include"random.h"
#include"Save.h"
#include"GA.h"
#include<time.h>
#define MAX 999
void main()
{	
//	clock_t start,finish;
//	double duration;
//	start=clock();
	int n,n3;
	cout<<"请输入随机图点的个数："<<endl<<endl;
	cin>>n;
	//cout<<"请输入进行实验的次数："<<endl<<endl;
//	cin>>n2;
	cout<<"请输入限制度数的大小："<<endl<<endl;
	cin>>n3;

	random random1(n);
	random1.generate();	
	random1.PrintAM();
	random1.DFS(0);
	random1.IsConnected();
//	random1.RePrim(n3);
//	random1.PrintDegree();

//	finish=clock();
//	duration=(double)(finish-start)/CLOCKS_PER_SEC;
//	cout<<"运算CPU时间为："<<duration<<"秒"<<endl<<endl;


   GA ga(n,n3);
  
	for(int i=0;i<n;i++)
	{ 
	
		for(int j=0;j<n;j++)
			ga.D[i][j]=random1.D[i][j];
	}
//	ga.PrintAM();
//	ga.PrintPop();
	ga.test_GA();

	cout<<endl<<"使用GA遗传算法求得最小权值为:"<<ga.best<<endl;

	cout<<endl<<"使用改进的prim算法求得:"<<endl;
	random1.RePrim(n3);
	random1.PrintDegree();



}