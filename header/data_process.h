#ifndef DATA_PROCESS_H
#define DATA_PROCESS_H
#include <vector>
#include <eigen3/Eigen/Dense>
#include <random>

#include "header/data_struct.h"
#include "header/utility.h"

namespace dataprocess
{

  /*randomly subsampling the massive data set*/
  void RandomSampling(const std::vector<t_Data> *src, std::vector<t_Data>*result, int size);

  /*Normalize the massive data set, set all attribute to range(0,1)*/
  void NormalizeData(std::vector<t_Data>*data_set);

  bool SemiBestPartition(Eigen::MatrixXd &source, Eigen::MatrixXd &left,
                         Eigen::MatrixXd &right, int &par_dim,
                         double &par_point);
  /*Semi-Best Partition*/
  bool DeterministicSplitDataSet(std::vector<t_Data> *target_left_set,
                                 std::vector<t_Data> *target_right_set,
                                 int&dimension_index, double &split_value,
                                 std::vector<t_Data> *source_data);

  double CalculateVariance(std::vector<t_Data> *data_set);

  bool SplitDataSet(std::vector<t_Data> *left_data_set,
                    std::vector<t_Data> *right_data_set,
                    double split_point,
                    int dimension_index,
                    std::vector<t_Data> *source_data_set);

  void CalculateSplitScore(double &split_score,double split_point,
                           std::vector<t_Data>*data_set,int dimension_index);


}
#endif // DATA_PROCESS_H
