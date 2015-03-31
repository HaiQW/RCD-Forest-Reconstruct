#include "header/cforest.h"


bool cforest::BuildForest(int leaf_size)
{
  int i;
  for(i = 0; i < ctree_num_; i++)
    {
      ctree* crr_ctree = new ctree(data_matrix_, leaf_size,
                                   std::log2(data_matrix_.n_rows));
      ctree_list_[i] = crr_ctree;
      crr_ctree->BuildCtree();
      LOG(INFO)<< "COMPACT TREE "<<i<<" HAS BEEN CONSTRUCTED.";
    }
}


double cforest::CalculateRareScore(const rowvec &element_vector)
{
  unsigned int i;
  double sum_score = 0.0;
  for(i = 0; i < ctree_num_; i++)
    {
      sum_score += ctree_list_[i]->SearchElement(element_vector);
    }
  return sum_score/ctree_num_;
}

colvec cforest::CalculateAllRareScore()
{
  unsigned int i;
  colvec score_vector(data_matrix_.n_rows);
  for(i = 0; i < data_matrix_.n_rows; i++)
    {
      score_vector(i) = CalculateRareScore(data_matrix_.row(i));
    }

  return score_vector;
}
