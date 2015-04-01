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
  ///label
  int class_label_;
  ///数目
  int num_;
};


///
/// \brief The t_Cnode struct
///
struct t_Cnode
{
  int size_; /// number of elements in this node
  int par_dim_; /// partition dimension at this node
  double par_point_;
  double variance_;
  t_Cnode *left_;
  t_Cnode *right_;
  t_Cnode *parent_;
};

///
/// \brief The t_Proportion struct
///
struct t_Proportion
{
  int class_label_;
  ///类成员的个数
  int class_num_;
  ///类所占的比例
  double proportion_;
  ///计算r
  double r_;
  ///类是否被发现
  bool is_discovered_;
};


///
/// \brief The t_Configure struct
///
struct t_Configure
{
  int dimension_size_;
  int sample_size_; /// if the number of dataset exceed a limit, use this
                    /// sample size to randomly select a sub sample
  int tree_num_;    /// number of trees in the compact forest
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
  ///记录属性值的数组
  std::vector<double> attribute_;
  ///该数据所属的类别
  int label_;
  int find_label_;
};

struct t_Range
{
  ///该维度范围的左边界
  double left_margin_;
  ///该维度范围的右边界
  double right_margin_;
};





#endif // DATA_STRUCT_H
