#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <math.h>
#include <float.h>
#include <string.h>
#include <iostream>
#include <limits.h>
#include <eigen3/Eigen/Dense>
#include <armadillo>

#include "header/file.h"
#include "header/data_struct.h"

using namespace arma;

namespace file
{
  /*!
   * \brief ReadConfiguraion
   * \param file_name
   * \return
   */
  t_Configure ReadConfiguraion(char* file_name );

  /*!
   * \brief ReadData
   * \param file_name
   * \param data_matrix
   * \param label_vector
   */
  void ReadData(const char* file_name, mat &data_matrix,
                vec &label_vector);


  /*!
   * \brief WriteRareScore
   * \param file_name
   * \param src_set
   * \param anomaly_score
   * \return
   */
  bool WriteRareScore(char* file_name, std::vector<t_Data>* src_set,
                      std::vector<t_AnomalyScore>* anomaly_score);
}
#endif // FILE_H
