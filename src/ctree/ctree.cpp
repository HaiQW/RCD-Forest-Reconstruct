#include "header/ctree.h"


void ctree::BuildCtree()
{
  /* Normalize the data set*/
  BuildCtree(root_, data_matrix_, 0);

}

void ctree::BuildCtree(t_Cnode *root, mat &data_set, int height)
{
  if(height >= height_ || data_set.n_rows <= 1)
    {
      root->left_ = nullptr;
      root->right_ = nullptr;
      root->size_ = data_set.n_rows;
      return;
    }
  else
    {
      mat left, right;
      t_Cnode *left_node, *right_node;
      double par_point = __DBL_MAX__;
      int par_dim = __INT_MAX__;

      /*semi-partition the original data set*/
      dataprocess::SemiBestPartition(data_set,left,right,par_dim,par_point);
      root->par_dim_ = par_dim;
      root->par_point_ = par_point;
      root->size_ = data_set.n_rows;
      //variance

      left_node = new t_Cnode();
      right_node = new t_Cnode();
      root->left_ = left_node;
      root->right_ = right_node;

      BuildCtree(left_node,left,height+1);
      BuildCtree(right_node,right,height+1);
    }
}

double ctree::SearchElement(const rowvec &data_vector)
{
  return SearchHelp(root_,data_vector,0);
}

double ctree::SearchHelp(t_Cnode *root, const rowvec &data_vector, int height)
{
  if(root->left_ == nullptr && root->right_ == nullptr)//leaf node
    {
      return height;//have diffirent principles to calculate rare score
    }
  else
    {
      /* internal search */
      if( data_vector(root->par_dim_) < root->par_point_)
        {
          SearchHelp(root->left_, data_vector, height + 1);
        }
      else
        {
          SearchHelp(root->right_, data_vector, height + 1);
        }
    }

}

void ctree::PrintCtree()
{
  if(root_->left_ == nullptr && root_->right_ == nullptr)
    {
      LOG(ERROR)<<"THE COMPACT TREE HAS NOT BEEN CONSTRUCT!";
    }

  std::queue<t_Cnode*> node_list;
  node_list.push(root_);
  node_list.push(nullptr);
  LOG(INFO)<<"PRINT THE COMPACT TREE...";
  while(!node_list.empty())
    {
       t_Cnode *crr_node = node_list.front();
       node_list.pop();
       if(crr_node == nullptr)
         {
           std::cout << std::endl;
           if(node_list.empty()) return;
           node_list.push(nullptr);
         }
       else
         {
           if( crr_node->left_ != nullptr && crr_node->right_ != nullptr)
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

