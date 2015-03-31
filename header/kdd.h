#ifndef KDD_H
#define KDD_H

#include <mlpack/methods/neighbor_search/neighbor_search.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include "header/easylogging++.h"

#include <header/data_struct.h>

using namespace arma;
using namespace mlpack;
using namespace mlpack::kmeans;
using namespace mlpack::neighbor;
/*!
 * \brief The NNDM class
 * NNDM the aim of NNDM is to find at least one example for every
 * class with the help of a tag library
 */
class KDD
{

public:

  /*!
   * \brief
   *
   * \param data_matrix  attribute-value of the data set
   * \param label_vector label-value of the data set
   * \param proportion proportion of class distribution
   */
  explicit KDD(const mat &data_matrix, const colvec &label_vector,
                unsigned int size, unsigned int class_num):
    data_matrix_(data_matrix),size_(size),label_vector_(label_vector),
    class_num_(class_num)
  {
  }

  ~KDD();

public:

  void FitModel();

  /*!
   * \brief DiscoverClass to find
   */
  void DiscoverClass();

public:

  /*!
   * \brief EstimateRadius Estimate the radius of every cluster by use of k
   * nearest neighbour
   * \return a vector of radius
   */
  //colvec EstimateRadius();

private:

  mat data_matrix_;
  colvec label_vector_;
  Mat<size_t> neighbor_index_;
  mat neighbor_;
  unsigned int size_;
  unsigned int class_num_;

};
#endif // NNDM_H
