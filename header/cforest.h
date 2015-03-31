#ifndef CFOREST_H
#define CFOREST_H

#include <eigen3/Eigen/Dense>
#include <vector>
#include <armadillo>

#include "header/assert.h"
#include "header/ctree.h"

using namespace arma;
/*!
 * \brief The cforest class
 */
class cforest
{
public:

  /*!
   * \brief cforest the construction function of The cforest class
   * \param data_matrix
   * \param ctree_num
   * \param sample_size
   */
  explicit cforest(mat &data_matrix, unsigned ctree_num,
          unsigned sample_size) : ctree_num_(ctree_num),
    sample_size_(sample_size), data_matrix_(data_matrix)
  {
    ctree_list_.resize(ctree_num);
  }

  ~cforest();

public:

  bool BuildForest(int leaf_size);

  /*!
   * \brief CalculateRareScore calcualte an rare score of a input elements
   * \param element_vector  vector of attribute-value
   *
   * \return rare score value in the compact forest
   */
  double CalculateRareScore(const rowvec &element_vector);

  /*!
   * \brief CalculateAllRareScore Calculate all rare score of elements in
   * member data_matrix_ from the cforest class
   *
   * \return a vector of rare score values
   */
  colvec CalculateAllRareScore();

private:
  unsigned int ctree_num_; /*!< number of ctree in this compact forest*/
  unsigned int sample_size_; /*!< if the data number is too large,use this
                               sample_size_ to sub sample */
  mat data_matrix_;
  std::vector<ctree*> ctree_list_;
};
#endif // CFOREST_H
