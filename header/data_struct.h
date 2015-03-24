#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include<vector>
struct t_S
{
  std::vector<int> ts_;
  int n_;
};

struct t_Distance
{
  int node_a_;
  int node_b_;
  double distance_;
};

struct t_NN
{
  //label
  int class_label_;
  //数目
  int num_;
};

struct t_INode
{
  //t_INode中所容纳的数据点的个数
  int node_size_;
  //这个节点中用来分割数据集合的维度索引
  int dimension_index_;
  //用来划分最有两个子树的分割点
  double split_value_;
  //分割维度的方差
  double variance_;
  //左子树指针
  t_INode *left_node_;
  //右子树指针
  t_INode *right_node_;
  //父亲节点指针
  t_INode *parent_node_;
};

//配置文件
struct t_Proportion
{
  int class_label_;
  //类成员的个数
  int class_num_;
  //类所占的比例
  double proportion_;
  //计算r
  double r_;
  //类是否被发现
  bool is_discovered_;
};

struct t_Data
{
  //属性的个数
  int attribute_num_;
  //记录属性值的数组
  std::vector<double> attribute_;
  //该数据所属的类别
  int data_class_;
  int find_label_;
  //lof
  double lof_;
};

struct t_Range
{
  //该维度范围的左边界
  double left_margin_;
  //该维度范围的右边界
  double right_margin_;
};

struct t_CutPoint
{
  //波峰和波谷的密度概率差
  double distance;
  //波谷的位置
  double position;
};

struct t_Bin
{
  //t_Bin的最左界限
  double left_margin_;
  //t_Bin的最右界限
  double right_margin_;
  //t_Bin中的平均值
  double data_sum_;
  //t_Bin中里面instance的个数
  int data_num_;
};

struct t_KernelDensity
{
  //核密度的估计点
  double kernel_position_;
  //核密度的估计值
  double kernel_density_;
};


struct t_AnomalyScore
{
  //数据的打分
  double score_;
  //数据在vector中的索引序号
  int data_index_;
  int class_label_;
};

struct t_Cluster
{
  //属性的个数
  int attribute_num_;
  //该cluster里面数据id
  std::vector<int> data_set_index;
  //与cluster 中心点的距离
  double distance_;
};

struct t_Center
{
  //cluster的类编号
  int cluster_label_;
  std::vector<double> attribute_;
  int data_index_;
};
//configuration struct
struct t_Configure
{
  int dimension_size_;
  int sample_size_;
  int tree_num_;
  int cluster_num_;
  int class_num_;
  float bin_width_;
  char* data_file_;
  char* score_file_;
  char* cluster_file_;
  char* lof_file_1_;
  char* lof_file_2_;
  std::vector<t_Proportion>p_set;
};

#endif // DATA_STRUCT_H
