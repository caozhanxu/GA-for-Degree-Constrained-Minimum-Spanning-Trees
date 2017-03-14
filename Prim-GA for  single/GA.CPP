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
    
	gen=5000;//��������
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
		
        for(int j=0;j<N-2;j++)//ǰN-2��Ϊprufer���룬
		{
			//pop[i][j]=rand()%N+1;//�Ը���ÿ�������ֵΪ1-N֮��
            pop[i][j]=(int)myu(1,N);//�Ը���ÿ�������ֵΪ1-N֮��
            bestPrufer[j]=0;
		}
		Check_Modify(pop[i]);//�Գ��Բ�����prufer������м���У��
		
		for(int k=N-2;k<N;k++)//��N-1��ΪĿ�꺯��ֵ����N��Ϊ��Ӧ��ֵ,Ĭ��Ϊ0
		{
			pop[i][k]=0;
		}
		
		objvalue[i]=fitvalue[i]=0;
	}
		for (int m=0;m<N;m++)//�ڽӾ�������ĸ�Ȩֵͼ��Ĭ��Ϊ0
		{
           	D[m]=new int[N];
			for(int n=0;n<N;n++)
		    	D[m][n]=0;
			
		}  
}



double GA::myu(double a,double b)    //��a��b֮���������һ��С��
{
	
	double y;
	y = (double)rand()/(RAND_MAX);
	return (a+(b-a)*y)+0.5; 
}

void GA::PrintAM() //��ӡ�ڽӾ���
{
    cout<<"�����Ⱥ����Ӧ���ڽӾ���A��"<<endl;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
			cout<<D[i][j]<<"\t";
		cout<<endl<<endl;
	}
}
void GA::PrintPop()//��ӡ��Ⱥ
{
	cout<<"�����ͼ�ĳ�ʼpop("<<N-2<<"��)��"<<endl;
	for(int i=0;i<pop_size;i++)
	{
		for(int j=0;j<N-1;j++)
			cout<<pop[i][j]<<"\t";
		cout<<endl<<endl;
	}
}



void GA::PrintObjvalueAndFitvalue()//��ӡĿ�꺯��ֵ����Ӧ��ֵ
{
	cout<<"�����Ⱥ��Ŀ�꺯��ֵ����Ӧ��ֵ"<<endl;
	for(int i=0;i<pop_size;i++)
		cout<<i+1<<"\t"<<objvalue[i]<<"\t"<<setprecision(10)<<fitvalue[i]<<endl;
}

void GA::Check_Modify(int *b)//��prufer���м�����޸ĳ��ȵ���
{
		int flag=0;
	int* degree= new int[N];
	for(int i=0;i<N;i++)
		degree[i]=1;//��Ϊprufer�и������ĳ��ִ���Ϊ��Ӧ��-1������Ĭ�϶Ⱦ�Ϊ1��
	
	for(int j=0;j<N-2;j++)//ǰN-2��Ϊprufer����
	{
		degree[b[j]-1]++;// a[j]-1,����Ϊdegree�±��Ǵ�0��ʼ�ģ���prufer��Ϊ1~N
	}
flag=checkDeg(b);//���м���
	while(flag==1)
	{
		flag=0;
		for(int k=0;k<N-2;k++)
		{
			if(degree[b[k]-1]>deg)
			{
                degree[b[k]-1]--;//�������Ƚ��ж�-1��������滻��һ����
				b[k]=(int)myu(1,N);
                 degree[b[k]-1]++;//���滻�����ֵ���ж�+1

			}
			
		}
		flag=checkDeg(b);//�������ٴμ���
	}
	delete []degree;//�ͷ��ڴ�
	
}

void GA::Check_Chg(int *b)//��prufer���м���ͺ͸���prufer
{
	int flag=0;
	flag=checkDeg(b);
	//	cout<<flag<<endl<<endl;
	while(flag==1)
	{
		flag=0;
		for(int i=0;i<N-2;i++)//���¶�ǰN-2�и�ֵΪprufer���룬
		{
            b[i]=(int)myu(1,N);//�Ը���ÿ�������ֵΪ1-N֮��
		}
		flag=checkDeg(b);
		
	}
	
	
}
int GA::checkDeg(int *a)////���prufer�����Ƿ񳬹��������ƣ����򷵻�1
{
	//	cout<<a[0]<<endl;
	
	int flag=0;
	int* degree= new int[N];
	for(int i=0;i<N;i++)
		degree[i]=1;//��Ϊprufer�и������ĳ��ִ���Ϊ��Ӧ��-1������Ĭ�϶Ⱦ�Ϊ1��
	
	for(int j=0;j<N-2;j++)//ǰN-2��Ϊprufer����
	{
		degree[a[j]-1]++;// a[j]-1,����Ϊdegree�±��Ǵ�0��ʼ�ģ���prufer��Ϊ1~N
		
		
		if(degree[a[j]-1]>deg)
		{
			//	cout<<a[j]<<"�Ķ���Ϊ"<<degree[a[j]-1]<<"�Ը��н���У��"<<endl;
			
			flag=1;
			break;//һ�������жȳ���������ѭ��
		}
	}
		delete []degree;//�ͷ��ڴ�
	return flag;
}

void GA::decodeSide(int a[],int b[],int x,int y,int *A,int *B)//����һ����,��ϸ˵����prufer��������ĵ�
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


void GA::calobjvalue()//����ÿ�������Ŀ�꺯��ֵ��N-1��
{
    int *p=new int [N];
    int *pp=new int [N];
	int pointA=0,pointB=0;//����ʱ������ߵ�ֵ
	
	
	for(int i=0;i<pop_size;i++)//����pop_size�е�����
	{
		objvalue[i]=0;
		pop[i][N-2]=0;
		//����һ
		for(int w=0;w<N;w++)//Ĭ�����������ֵ��Ϊ0��1
		{
			p[w]=0;	
			pp[w]=1;
		}
		
		for(int j=0;j<N-2;j++)//���ݶ�Ӧ��prufer�룬���ɶ�Ӧ��������
		{
			p[pop[i][j]-1]++;;
			pp[pop[i][j]-1]=0;
			
		}
		//�����
		for(int k=0;k<N-2;k++)//�ܹ���Ҫ����N-1����,������N-2����
		{
            decodeSide(p,pp,i,k,&pointA,&pointB);
			//	cout<<"��"<<i+1<<"���ĵ�"<<k+1<<"����<"<<pointA<<","<<pointB<<">="<<D[pointA-1][pointB-1]<<endl;
			pop[i][N-2]+=D[pointA-1][pointB-1];	
			objvalue[i]+=D[pointA-1][pointB-1];
		}
		//������,������N-1����
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
		//		cout<<"��"<<i+1<<"���ĵ�"<<N-1<<"����<"<<pointA<<","<<pointB<<">="<<D[pointA-1][pointB-1]<<endl<<endl;
		objvalue[i]+=D[pointA-1][pointB-1];	
		pointA=pointB=0;
	}
	delete []p;
	delete []pp;
}


void GA::calfitvalue()    //����ÿ���������Ӧ��ֵ��N��
{		
	int max=999*(N-1)/2;
	double sum_fit=0;//��Ӧ����ֵ�ݶ�Ϊint�ͣ��Ժ�����Խڵ������ܸ���
	for(int i=0;i<pop_size;i++)//���ÿ���������Ӧֵ�Լ�����Ӧֵ��ֵ
	{
		//	fitvalue[i]=pop[i][N-1]=MAX2-pop[i][N-2];//��������ȥĿ��ֵ�����Խ�������Ӧ��Խ��
		
        fitvalue[i]=worst-fitvalue[i];//Ŀ��ֵ�ĵ��������Խ�������Ӧ��Խ��
		sum_fit+=fitvalue[i];
	}
	fitvalue[0]/=sum_fit;
	for(int j=1; j<pop_size; j++)
	{
		//	pop[j][N-1]=pop[j][N-1]/sum_fit;      //��һ����ת��Ϊÿ��Ⱦɫ��ı�ѡ����ʣ�
		//	pop[j][N-1]=pop[j][N-1]+pop[j-1][N-1];    //ת��Ϊ�ۻ���ѡ�����
		fitvalue[j]=fitvalue[j]/sum_fit;      //��һ����ת��Ϊÿ��Ⱦɫ��ı�ѡ����ʣ�
		fitvalue[j]=fitvalue[j]+fitvalue[j-1];    //ת��Ϊ�ۻ���ѡ�����
	}
	
	//	pop[pop_size-1][N-1]=1;
	fitvalue[pop_size-1]=1;
	
}


void GA::calbest()//����Ⱥ����С��Ŀ��ֵ�Լ���Ӧ��prufer����
{
	double best2;
	best2=objvalue[0];
	int k=0;//��С��Ŀ��ֵ�ǵڼ���
	for(int i=1;i<pop_size;i++)//�ҳ���Сֵ�Լ����ڵڼ�������
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
		bestPrufer[j]=pop[k][j];//�������Ÿ���
	}	
}


void GA::calobj_sort()//����Ŀ�꺯��ֵ���������
{
		calobjvalue();
	int *temp=new int [N];
	double temp2;
	for(int i=1;i<pop_size;i++)//ֱ�Ӳ�������
	{
		temp2=objvalue[i];//�ݴ����Ŀ��ֵ
		for(int j=0;j<N;j++)//�����Ŀ��ֵ��Ӧ��prufer����
			temp[j]=pop[i][j];
		
		for(int k=i-1;temp2<objvalue[k];k--)//Ѱ�Ҳ���λ��
		{
			objvalue[k+1]=objvalue[k];//��¼����
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


void GA::selection()  //ѡ������
{
	for(int m=0;m<N-2;m++)//��һ������Ϊ��һ�������Ÿ���
		pop[0][m]=bestPrufer[m];
	double r;
	for(int i=1;i<pop_size; i++) //��һ�����±�Ϊ0���Ѿ�����ֵ�����Դ��±��1��ʼ
	{
		r = myu(0, 1);
		for(int j = 0;j<pop_size; j++) //ѡ��Ⱦɫ��
		{
			if(r <= fitvalue[j])          //ѡ���j��Ⱦɫ�岢��Ϊ��һ����iֻȾɫ��
			{
				for(int k=0;k<N-2;k++)
					pop[i][k] = pop[j][k];
				break;
			}
		}
	}
}


void GA::crossover()  //��������
{
	int   i, j, jj, k,n;
	int *temp=new int[N];
    int num=(int)(pop_size*p_crossover/2+0.5); //��0.5���������������
	for(i = 1; i<=num; i++)         //�ܹ�ѡ��2����POP_SIZE*P_CROSSOVER/2+0.5����Ⱦɫ����н���
	{
		j = (int)myu(0,pop_size-1);
		jj = (int)myu(0,pop_size-1);
		n = (int)myu(0,N-2);         //ȷ�������n
		
		for(k=n; k<N-2; k++)   //ֻ���������n����Ļ���
		{
			temp[k] = pop[j][k];
			pop[j][k] = pop[jj][k];
			pop[jj][k]=temp[k];
		}
		Check_Modify(pop[j]);//�Խ����������Ⱦɫ����жȵļ���
		Check_Modify(pop[jj]);
		
	}
	delete []temp;
}



void GA::mutation()//��������
{
	double r=0;
	for(int i=1; i<pop_size; i++) 
	{ 
		for(int k=0; k<N-2; k++ )
		{
			r=myu(0,1)-0.5;
			if(r<=p_mutation)
			{
				pop[i][k]=(int)myu(1,N);//�����������
			}
			
		}
		Check_Modify(pop[i]);//����Ƿ񳬹�������
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
 //PrintPop();//�鿴��Ⱥ��prufer����
//		cout<<"��������="<<i<<"ʱ"<<endl;
//	 PrintObjvalueAndFitvalue();//�鿴�Ƿ���Ŀ��ֵ����Ӧ������

		selection();
	crossover();

//	calobj_sort();
//	 PrintPop();
		mutation();
		
	//	cout<<"��������="<<i<<endl;
	//	cout<<"Ŀǰ�ҵ������ź���ֵΪ="<<setprecision(10)<<best<<endl<<endl<<endl;
		fs<<i<<" "<<best<<endl;
	}
    finish = clock();
	duration = (double)(finish - start)/CLOCKS_PER_SEC;
//	cout<<"����CPUʱ��Ϊ��"<<duration<<"��"<<endl;
	fs.close();
	
}