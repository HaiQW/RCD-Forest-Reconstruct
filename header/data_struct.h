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


/*!
 * \brief The t_Cnode struct
 */
struct t_Cnode
{
  int size_;  /*!< number of elements in this node */
  int par_dim_; /*!< partition dimension at this node */
  double par_point_;
  double variance_;
  t_Cnode *left_;
  t_Cnode *right_;
  t_Cnode *parent_;
};
/*!
 * \brief The t_Proportion struct
 */
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


/*!
 * \brief The t_Configure struct
 */
struct t_Configure
{
  int dimension_size_;
  int sample_size_; /*!< if the number of dataset exceed a limit, use this
                       sample size to randomly select a sub sample */
  int tree_num_; /*!< number of trees in the compact forest*/
  int cluster_num_;
  int class_num_;
  int data_size_;
  float bin_width_;
  char *data_file_;
  char *score_file_;
  char *cluster_file_;
  char *lof_file_1_;
  char *lof_file_2_;
  std::vector<t_Proportion> p_set;
};


struct t_Data
{
  int attribute_num_;
  //记录属性值的数组
  std::vector<double> attribute_;
  //该数据所属的类别
  int label_;
  int find_label_;
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

#endif // DATA_STRUCT_H
