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
  ///
  /// \brief ReadConfiguraion
  /// \param file_name
  /// \return
  ///
  t_Configure ReadConfiguraion(char* file_name );

  ///
  /// \brief ReadData
  /// \param file_name
  /// \param data_matrix
  /// \param label_vector
  ///
  void ReadData(const char* file_name, mat &data_matrix,
                Col<size_t> &label_vector);

  ///
  /// \brief WirteCSV
  /// \param file_name
  /// \param data_matrix
  /// \return
  ///


namespace csv
{
  enum t_csvparser_state
  {
    line_start = 0,
    field_start,
    field_value,
    field_end,
    line_end_begin,
    line_end,
    error,
  };

  struct t_csvparser
  {
    t_csvparser_state state;
    unsigned row;
    unsigned col;
    uint32_t nread;
    void *data;
  };

  /// function pointer
  typedef int (*csvparser_field_callback)(t_csvparser *parser,
                                         const char* data,
                                         size_t length,
                                         int row,
                                         int col);
  struct t_csvparser_setting
  {
    char delimiter;
    csvparser_field_callback field_cb;
  };

  ///
  /// \brief csvparser_init
  /// \param parser
  ///
  void csvparser_init(t_csvparser *parser);

  ///
  /// \brief csv_parser_execute
  /// \param parser
  /// \param setting
  /// \param data
  /// \param data_len
  /// \return
  ///
  size_t csv_parser_execute(t_csvparser *parser,
                            const t_csvparser_setting *setting,
                            const char *data,
                            size_t data_len);
  bool WirteCSV(const char* file_name, const mat &data_matrix);

  ///
  /// \brief ReadCSV
  /// \param file_name
  /// \param data_matrix
  /// \return
  ///
  bool ReadCSV(const char* file_name, mat &data_matrix);
}

}
#endif // FILE_H
