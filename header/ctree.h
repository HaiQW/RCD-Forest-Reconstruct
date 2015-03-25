#ifndef CTREE_H
#define CTREE_H

#include <vector>
#include <iostream>
#include <eigen3/Eigen/Dense>

#include "header/data_struct.h"

class ctree
{
public:
  ctree(Eigen::MatrixXd &data_set, int height);
  ~ctree();

public:

  void BuildCTree();

  /* class member */
  void BuildCtree(t_Cnode *root, Eigen::MatrixXd &data_set, int height_);

  /* Search */
  double SearchElement(t_Cnode* root, t_Data element, int height);


  void PrintCtree();

private:
  int height_;
  t_Cnode* root_;
  Eigen::MatrixXd data_matrix_;

};
#endif // CTREE_H
