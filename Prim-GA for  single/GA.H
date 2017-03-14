
class GA
{
public:
	int **D;//D[i][j]表示点i和j的距离

	int **pop;//pop[pop_size][N],种群的大小，前N-2为prufer编码，
	//N-1列为目标函数，第N列为适应度函数(被选择概率和累积概率)

    int N;//节点的个数为N
	int deg;//度的限制数

	int pop_size;//20群体的大小
	int gen;//100遗传迭代次数
	double p_crossover;//0.2交叉概率
	double p_mutation;//0.1变异概率
	
	double best;//最小目标值
	double worst;//最大/坏目标值
	int *bestPrufer;//最小目标值对应的prufer值
	double *objvalue;//目标函数值
	double *fitvalue;//适应度值
	
	
public:
	GA(int n,int degree);//有参构造函数
	double myu(double a,double b);//在a与b之间随机产生一个小数

	void PrintAM(); //打印邻接矩阵
	void PrintPop();//打印种群
	void PrintObjvalueAndFitvalue();//打印目标函数值和适应度值
	
	void Check_Modify(int *b);//对prufer进行检验和修改超度的码
	void Check_Chg(int *b);//对prufer进行检验和更换prufer
	int checkDeg(int *a);//检查prufer编码是否超过度数限制n3，超过返回1，没超返回0
	
	void decodeSide(int a[],int b[],int x,int y,int *A,int *B);//解码求一条边
	void calobjvalue();//解码计算目标函数值第N-1列
	void calfitvalue();//计算每个个体的适应度值第N列
	void calbest();//求种群中最小的目标值以及对应的prufer编码
	void calobj_sort();//计算目标函数值后进行排序
	
	void selection();//选择算子
	void crossover();//交叉算子
	void mutation();//变异算子
	
	void test_GA();//进行遗传算法求最小生成树
};