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
	cout<<"���������ͼ��ĸ�����"<<endl<<endl;
	cin>>n;
	//cout<<"���������ʵ��Ĵ�����"<<endl<<endl;
//	cin>>n2;
	cout<<"���������ƶ����Ĵ�С��"<<endl<<endl;
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
//	cout<<"����CPUʱ��Ϊ��"<<duration<<"��"<<endl<<endl;


   GA ga(n,n3);
  
	for(int i=0;i<n;i++)
	{ 
	
		for(int j=0;j<n;j++)
			ga.D[i][j]=random1.D[i][j];
	}
//	ga.PrintAM();
//	ga.PrintPop();
	ga.test_GA();

	cout<<endl<<"ʹ��GA�Ŵ��㷨�����СȨֵΪ:"<<ga.best<<endl;

	cout<<endl<<"ʹ�øĽ���prim�㷨���:"<<endl;
	random1.RePrim(n3);
	random1.PrintDegree();



}