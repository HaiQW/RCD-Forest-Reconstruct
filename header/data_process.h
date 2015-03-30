#ifndef DATA_PROCESS_H
#define DATA_PROCESS_H
#include <vector>
#include <eigen3/Eigen/Dense>
#include <random>
#include <time.h>
#include <armadillo>

#include "header/data_struct.h"
#include "header/utility.h"

using namespace arma;

namespace dataprocess
{

  /*!
   * \brief RandomSampling RandomSampling randomly select a sub data
   * set from the original
   *
   * \param src
   * \param result
   * \param size
   */
  void RandomSampling(const std::vector<t_Data> *src,
                      std::vector<t_Data>*result, int size);


  /*!
   * \brief NormalizeData NormalizeData Normalize the massive data set,
   * set all attribute to range(0,1)
   *
   * \param data_set
   */
  void NormalizeData(std::vector<t_Data>*data_set);

  /*!
   * \brief SemiBestPartition SemiBestPartition DeterministicSplitDataSet
   * This partition strategy is that randomly select a partition dimension
   * and select the best partition point in the selected dimension.
   *
   * \param source
   * \param left
   * \param right
   * \param par_dim
   * \param par_point
   *
   * \return
   */
  bool SemiBestPartition(mat &source, mat &left, mat &right, int &par_dim,
                         double &par_point);


  /*!
   * \brief DeterministicSplitDataSet
   * \param target_left_set
   * \param target_right_set
   * \param dimension_index
   * \param split_value
   * \param source_data
   * \return
   */
  bool DeterministicSplitDataSet(std::vector<t_Data> *target_left_set,
                                 std::vector<t_Data> *target_right_set,
                                 int &dimension_index, double &split_value,
                                 const std::vector<t_Data> *source_data);

  /*!
   * \brief CalculateVariance
   * \param data_set
   * \return
   */
  double CalculateVariance(std::vector<t_Data> *data_set);

  /*!
   * \brief SplitDataSet
   * \param left_data_set
   * \param right_data_set
   * \param split_point
   * \param dimension_index
   * \param source_data_set
   * \return
   */
  bool SplitDataSet(std::vector<t_Data> *left_data_set,
                    std::vector<t_Data> *right_data_set,
                    double split_point,
                    int dimension_index,
                    std::vector<t_Data> *source_data_set);

  /*!
   * \brief CalculateSplitScore
   * \param split_score
   * \param split_point
   * \param data_set
   * \param dimension_index
   */
  void CalculateSplitScore(double &split_score, double split_point,
                           std::vector<t_Data>*data_set,int dimension_index);


}

#endif // DATA_PROCESS_H
