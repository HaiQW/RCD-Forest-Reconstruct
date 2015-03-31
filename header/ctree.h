#ifndef CTREE_H
#define CTREE_H

#include <vector>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <queue>
#include <armadillo>

#include "header/easylogging++.h"
#include "header/data_struct.h"
#include "header/assert.h"
#include "header/data_process.h"

using namespace arma;

/*!
 * \brief The ctree class
 */
class ctree
{
public:

  /*!
   * \brief ctree
   * \param data_set
   * \param height
   */
  explicit ctree(mat &data_set,int size, int height):data_matrix_(data_set),
    height_(height),size_(size)
  {
    root_ = new t_Cnode();
    root_->left_ = nullptr;
    root_->right_ = nullptr;
  }

  ~ctree();

public:

  /*!
   * \brief BuildCtree
   */
  void BuildCtree();

  /*!
   * \brief BuildCtree
   * \param root
   * \param data_set
   * \param height
   */
  void BuildCtree(t_Cnode *root, mat &data_set, int height);

  /*!
   * \brief SearchElement
   * \param data_vector
   * \return
   */
  double SearchElement(const rowvec &data_vector);

  /*!
   * \brief PrintCtree
   */
  void PrintCtree();

protected:

  /*!
   * \brief SearchHelp
   * \param root
   * \param data_vector
   * \param height
   * \return
   */
  double SearchHelp(t_Cnode* root, const rowvec &data_vector, int height);

private:

  int size_; /*!< the maximum size of a leaf node */
  int height_;  /*!< the maximum height of the compact tree. */
  t_Cnode* root_;
  mat data_matrix_;


};
#endif // CTREE_H
