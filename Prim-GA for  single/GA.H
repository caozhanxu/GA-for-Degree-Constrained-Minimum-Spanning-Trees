
class GA
{
public:
	int **D;//D[i][j]��ʾ��i��j�ľ���

	int **pop;//pop[pop_size][N],��Ⱥ�Ĵ�С��ǰN-2Ϊprufer���룬
	//N-1��ΪĿ�꺯������N��Ϊ��Ӧ�Ⱥ���(��ѡ����ʺ��ۻ�����)

    int N;//�ڵ�ĸ���ΪN
	int deg;//�ȵ�������

	int pop_size;//20Ⱥ��Ĵ�С
	int gen;//100�Ŵ���������
	double p_crossover;//0.2�������
	double p_mutation;//0.1�������
	
	double best;//��СĿ��ֵ
	double worst;//���/��Ŀ��ֵ
	int *bestPrufer;//��СĿ��ֵ��Ӧ��pruferֵ
	double *objvalue;//Ŀ�꺯��ֵ
	double *fitvalue;//��Ӧ��ֵ
	
	
public:
	GA(int n,int degree);//�вι��캯��
	double myu(double a,double b);//��a��b֮���������һ��С��

	void PrintAM(); //��ӡ�ڽӾ���
	void PrintPop();//��ӡ��Ⱥ
	void PrintObjvalueAndFitvalue();//��ӡĿ�꺯��ֵ����Ӧ��ֵ
	
	void Check_Modify(int *b);//��prufer���м�����޸ĳ��ȵ���
	void Check_Chg(int *b);//��prufer���м���͸���prufer
	int checkDeg(int *a);//���prufer�����Ƿ񳬹���������n3����������1��û������0
	
	void decodeSide(int a[],int b[],int x,int y,int *A,int *B);//������һ����
	void calobjvalue();//�������Ŀ�꺯��ֵ��N-1��
	void calfitvalue();//����ÿ���������Ӧ��ֵ��N��
	void calbest();//����Ⱥ����С��Ŀ��ֵ�Լ���Ӧ��prufer����
	void calobj_sort();//����Ŀ�꺯��ֵ���������
	
	void selection();//ѡ������
	void crossover();//��������
	void mutation();//��������
	
	void test_GA();//�����Ŵ��㷨����С������
};