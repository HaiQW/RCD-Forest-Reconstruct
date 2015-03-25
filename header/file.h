#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <math.h>
#include <float.h>
#include <string.h>
#include <iostream>
#include <limits.h>
#include <eigen3/Eigen/Dense>

#include "header/file.h"
#include "header/data_struct.h"

namespace file
{
  /*Read the configuration from a file*/
  t_Configure ReadConfiguraion(char* file_name );

  /* Read data from the input file*/
  void ReadData(char* file_name, Eigen::MatrixXd &data_matrix,
                Eigen::VectorXi &label_vector);

  /* Write Rare Score to output file*/
  bool WriteRareScore(char* file_name, std::vector<t_Data>* src_set,
                      std::vector<t_AnomalyScore>* anomaly_score);
}
#endif // FILE_H
