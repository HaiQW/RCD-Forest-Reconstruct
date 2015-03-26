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
   root_ = new t_Cnode();
   root_->left_ = NULL;
   root_->right_ =NULL;
}

void ctree::BuildCtree()
{
  /* Normalize the data set*/
  BuildCtree(root_, data_matrix_, 0);

}

void ctree::BuildCtree(t_Cnode *root, Eigen::MatrixXd &data_set, int height)
{
  if(height >= height_ || data_set.rows() <= 1)
    {
      root->left_ = NULL;
      root->right_ = NULL;
      root->size_ = data_set.rows();
      return;
    }
  else
    {
      Eigen::MatrixXd left, right;
      t_Cnode *left_node, *right_node;
      double par_point = __DBL_MAX__;
      int par_dim = __INT_MAX__;

      /*semi-partition the original data set*/
      dataprocess::SemiBestPartition(data_set,left,right,par_dim,par_point);
      root->par_dim_ = par_dim;
      root->par_point_ = par_point;
      root->size_ = data_set.rows();
      //variance

      left_node = new t_Cnode();
      right_node = new t_Cnode();
      root->left_ = left_node;
      root->right_ = right_node;

      BuildCtree(left_node,left,height+1);
      BuildCtree(right_node,right,height+1);
    }
}

void ctree::PrintCtree()
{
  if(root_->left_ == NULL && root_->right_ == NULL)
    {
      LOG(ERROR)<<"THE COMPACT TREE HAS NOT BEEN CONSTRUCT!";
    }

  std::queue<t_Cnode*> node_list;
  node_list.push(root_);
  node_list.push(NULL);
  LOG(INFO)<<"PRINT THE COMPACT TREE...";
  while(!node_list.empty())
    {
       t_Cnode *crr_node = node_list.front();
       node_list.pop();
       if(crr_node == NULL)
         {
           std::cout << std::endl;
           if(node_list.empty()) return;
           node_list.push(NULL);
         }
       else
         {
           if( crr_node->left_ != NULL && crr_node->right_ != NULL)
             {
               node_list.push(crr_node->left_);
               node_list.push(crr_node->right_);
               std::cout<<crr_node->size_<<":"<<crr_node->par_dim_
                       <<":"<<crr_node->par_point_<<" ";
             }
           else
             {
               std::cout<<crr_node->size_<<" ";
             }

         }
    }
}

