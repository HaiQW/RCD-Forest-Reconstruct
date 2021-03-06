#include "header/kdd.h"



void KDD::FitModel()
{

}

void KDD::DiscoverClass()
{
  /// use mlpack ALLkNN range search
  AllkNN knn(data_matrix_);
  knn.Search(size_, neighbor_index_, neighbor_);

  /// sort the data elements by their k-distance
  inplace_trans(neighbor_);
  colvec kdis = neighbor_.col(size_ - 1);
  uvec kdis_index = sort_index(kdis);
  std::cout<<kdis_index;
  unsigned int find_num = 0;
  unsigned int pos = 0;
  unsigned int times = 0;
  uvec ask_flag(data_matrix_.n_cols);
  uvec find_class(class_num_);
  find_class.fill(0);
  ask_flag.fill(0);
  ///find the rare class
  while(find_num < class_num_ && pos < data_matrix_.n_cols)
    {
      int ask_index = kdis_index(pos);
      pos++;

      if( ask_flag(ask_index) == 1) continue;
      ask_flag(ask_index) = 1;
      int label = label_vector_(ask_index);
      times++;

      if( find_class(label) == 0)
        {
          find_class(label) = 1;
          find_num++;
          /// log information
          LOG(INFO)<<"CLASS "<<label<<" HAS BEEN DISCOVERED ASTER "<<times;
        }

      ///neighbour
      for(unsigned int i = 0; i < size_; i++)
        {
          ask_flag(neighbor_index_(i,ask_index)) = 1;
        }

    }

}
