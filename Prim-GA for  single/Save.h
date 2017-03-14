class Save
{
  public:
	  int num;//实验次数
	  int *result;//保存实验结果
	  float no;//没有结果的个数
  public:
	   Save(int n);
	  void ratio();//计算没有结果所占的比例
	  void InsertSort(int *result,int num);//直接插入排序
	
};
