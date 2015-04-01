#ifndef KDD_H
#define KDD_H

#include <mlpack/methods/neighbor_search/neighbor_search.hpp>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include "header/easylogging++.h"

#include <header/data_struct.h>

using namespace arma;
using namespace mlpack;
using namespace mlpack::neighbor;
///
/// \brief The KDD class  KDD means kdistance discovery.  KDD select the
/// element with minimum k-distance as a rare category candidate.
///
class KDD
{

public:

  ///
  /// \brief KDD
  /// \param data_matrix  Attribute-value of the data set
  /// \param label_vector  Label-value of the data set
  /// \param size  Paramater k
  /// \param class_num  The number of class in the given massive data set
  ///
  explicit KDD(const mat &data_matrix, const colvec &label_vector,
                unsigned int size, unsigned int class_num):
    data_matrix_(data_matrix),label_vector_(label_vector),size_(size),
    class_num_(class_num)
  {
  }

  ~KDD();

public:

  void FitModel();

  ///
  /// \brief DiscoverClass  Find the rare class
  ///
  void DiscoverClass();

private:

  mat data_matrix_; /// attribute-value of data set and a column
                    /// represent a element
  colvec label_vector_; /// the label of a data element
  unsigned int size_; /// k
  unsigned int class_num_; /// number of class
  Mat<size_t> neighbor_index_; /// the index of k nearest neighbor
  mat neighbor_; /// the distance value of k nearest neighbor

};
#endif // NNDM_H
