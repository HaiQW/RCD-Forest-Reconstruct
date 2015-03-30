#include "header/NNDM.h"



void NNDM::FitModel()
{

}

colvec NNDM::EstimateRadius()
{
  /*! calculate the number of every class in the massive data set */
  colvec radius_;
  std::for_each(proportion_.begin(), proportion_.end(),
                [this](double p)
  {
      class_num_.push_back(p * data_matrix_.n_rows);
  });

  /*! use mlpack ALLkNN range search */
  //std::vector<double> vector_i = data_matrix_.row(1);
  //AllkNN knn();
}
