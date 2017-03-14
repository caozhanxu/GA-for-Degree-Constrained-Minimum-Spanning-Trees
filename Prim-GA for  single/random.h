struct shortedge
{
	int lowcost;
	int adjvex;	
};


 class random   
{
public:
	
	bool**G;//G[i][j]=true��ʾ����i��j����
	int N;//ͼ�Ķ������
	int **D;//D[i][j]��ʾ��i��j�ľ���
    int **D2;//�Ľ�prim�㷨ʱ�����ڽӾ���
	int *d;//d[i]��ʾ����i��Ȩ��
	int *v;//�ڵ��Ƿ񱻷��ʹ�
	int *visited;//�жϽڵ��Ƿ�ѡ��,0=δѡ�У�1=��ѡ�У�2=��������
	int *L;//��ÿ���ڵ�Ķ������м���
	int sum;
	shortedge *shortEdge;//��ѡ��̱߼�������adjvex��lowcost
	
public:
    random(int num);//�вεĹ��캯��	
	random();//�޲εĹ��캯��	
	~random(); //��������
	void setN(int num);
	void  generate();//�����漴ͼ
	void PrintAM();//��ӡ�ڽӾ���
    void  DFS(int n);//��ȱ���
	void IsConnected();//�ж��Ƿ���ͨ��
	void adjust(int m);
	
	int MinEdge(shortedge *shortEdge, int N);//Ѱ����̱ߵ��ڽӵ�K
	void Prim();//prim �㷨
	void RePrim(int n);//�Ľ�prim �㷨
    void PrintDegree();//��ӡ����	
};

