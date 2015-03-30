#ifndef NNDM_H
#define NNDM_H

#include <mlpack/methods/neighbor_search/neighbor_search.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>

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
class NNDM
{
public:

  /*!
   * \brief
   *
   * \param data_matrix  attribute-value of the data set
   * \param label_vector label-value of the data set
   * \param proportion proportion of class distribution
   */
  explicit NNDM(mat data_matrix, const std::vector<int> &label_vector,
       const std::vector<double> &proportion): data_matrix_(data_matrix),
    label_vector_(label_vector),proportion_(proportion)
  {

  }

  ~NNDM();

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
  colvec EstimateRadius();

private:

  mat data_matrix_;
  std::vector<int> label_vector_;
  std::vector<double> proportion_;
  std::vector<int> class_num_;
  Mat<size_t> neighbor_index_;



};
#endif // NNDM_H
