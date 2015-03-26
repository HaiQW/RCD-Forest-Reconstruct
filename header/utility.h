#ifndef UTILITY_H
#define UTILITY_H
#include <eigen3/Eigen/Core>
#include "header/utility.h"

using namespace Eigen;

namespace utility
{

//   template <typename Derived>
//   struct ColComparator
//   {
//     const Derived& matrix;
//     const int row;

//     ColComparator(const MatrixBase<Derived> &m, int r)
//       :matrix(m.derived()),row(r)
//     {}

//     bool operator()(int i, int j)const
//     {
//       return matrix(row,i) < matrix(row,j);
//     }
//   };

  /**
   * RowComparator used in Sorting with row in a Matrix.
   */
  template <typename Derived>
  struct RowComparator
  {
    const Derived& matrix;
    const int col;

    RowComparator(const MatrixBase<Derived>& m, int c)
      :matrix(m.derived()),col(c)
    {}

    bool operator()(int i, int j)const
    {
      return matrix(i, col) < matrix(j, col);
    }
  };


//   template<typename Derived>
//   VectorXi ColumnArgSort(const MatrixBase<Derived>& matrix, int row)
//   {
//     /* Start with indices[0 1 2 3... n-1]*/
//     VectorXi indexes = VectorXi::LinSpaced(matrix.cols(), 0, matrix.cols() - 1);

//     /* Sort using custom comparator ,that will compare matrix values
//      * indirectly
//      */
//     std::sort(indexes.data(), indexes.data()+indexes.size(),
//               ColComparator<Derived>(matrix,row));

//     return indexes;
//   }

  /**
   * Sort the Data Matrix by row according to the value in col
   */
  template <typename Derived>
  VectorXi RowArgSort(const MatrixBase<Derived>& matrix, int col)
  {
    /* Start with indices [0 1 2 ... N-1] */
    VectorXi indexes = VectorXi::LinSpaced(matrix.rows(), 0, matrix.rows()-1);

    /* Sort using custome comparator, that will compare matrix values
      * indirectly
      */
    std::sort(indexes.data(), indexes.data() + indexes.size(),
              RowComparator<Derived>(matrix,col));

    return indexes;
  }
}

#endif // UTILITY_H
