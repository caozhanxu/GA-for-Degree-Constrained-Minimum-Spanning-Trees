struct shortedge
{
	int lowcost;
	int adjvex;	
};


 class random   
{
public:
	
	bool**G;//G[i][j]=true表示顶点i和j相邻
	int N;//图的顶点个数
	int **D;//D[i][j]表示点i和j的距离
    int **D2;//改进prim算法时备份邻接矩阵
	int *d;//d[i]表示顶点i的权重
	int *v;//节点是否被访问过
	int *visited;//判断节点是否被选中,0=未选中，1=被选中，2=度数已满
	int *L;//对每个节点的度数进行计数
	int sum;
	shortedge *shortEdge;//候选最短边集，包括adjvex和lowcost
	
public:
    random(int num);//有参的构造函数	
	random();//无参的构造函数	
	~random(); //析构函数
	void setN(int num);
	void  generate();//生成随即图
	void PrintAM();//打印邻接矩阵
    void  DFS(int n);//深度遍历
	void IsConnected();//判断是否连通；
	void adjust(int m);
	
	int MinEdge(shortedge *shortEdge, int N);//寻找最短边的邻接点K
	void Prim();//prim 算法
	void RePrim(int n);//改进prim 算法
    void PrintDegree();//打印度数	
};

