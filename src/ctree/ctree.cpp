#include "header/ctree.h"


ctree::ctree(Eigen::MatrixXd &data_matrix, int height)
{
   if(data_matrix.cols()<= 0
      || height <= 0
      || data_matrix.rows() <= 0)
     {
       exit(-1);
     }

   height_ = height;
   data_matrix_ = data_matrix;
   root_ = NULL;
}

void ctree::BuildCTree()
{
  /* Normalize the data set*/
  BuildCtree(root_, data_matrix_, 0);

}

void ctree::BuildCtree(t_Cnode *root, Eigen::MatrixXd &data_set, int height)
{
  if(height >= height_ || data_set.rows() <= 1)
    {
      return;
    }
  else
    {
      double par_point = __DBL_MAX__;
      int par_dim = __INT_MAX__;
      bool par_flag = false;

      /*split the original data set*/

    }
}


