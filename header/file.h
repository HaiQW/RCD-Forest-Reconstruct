#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <math.h>
#include <float.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <limits.h>
#include <eigen3/Eigen/Dense>
#include <armadillo>

#include "header/file.h"
#include "header/data_struct.h"
#include "header/assert.h"

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
    void *data; /// void pointer
  };

  struct t_field
  {
    char data[32];
    int row;
    int col;
    t_field *next;
  };

  struct t_csv
  {
    t_field *head;
    t_field *tail;
  };

  /// function pointer
  typedef bool (*csvparser_field_callback)(t_csvparser *parser,
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
  size_t csvparser_execute(t_csvparser *parser,
                           const t_csvparser_setting *setting,
                           const char *data,
                           size_t data_len);
  ///
  /// \brief new_field
  /// \param data
  /// \param length
  /// \param row
  /// \param col
  /// \return
  ///
  t_field *new_field(const char *data, size_t length, int row, int col);

  ///
  /// \brief field_cb
  /// \param paser
  /// \param data
  /// \param length
  /// \param row
  /// \param col
  /// \return
  ///
  bool field_cb(t_csvparser *parser, const char *data, size_t length,
               int row, int col);


  ///
  /// \brief WirteCSV  Write data matrix to a csv format file.
  /// \param file_name  The name of the written csv file.
  /// \param col_name  The attribute name of the csv file.
  /// \param data_matrix  Attribute-value.
  /// \return
  ///
  bool WirteCSV(const char *file_name, const std::vector<std::string> &col_name,
                const mat &data_matrix);

  ///
  /// \brief ReadCSV
  /// \param file_name
  /// \param setting
  /// \return
  ///
  t_csvparser &ReadCSV(const char* file_name, const t_csvparser_setting *setting);

  ///
  /// \brief ReadCSV Read data from a csv data file and store the attribute into
  /// a matrix and label to a vector.
  ///
  /// \param file_name
  /// \param setting
  /// \param data_matrix
  ///
  void ReadCSV(const char* file_name, const t_csvparser_setting *setting,
               mat &data_matrix, colvec &label);
}

}
#endif // FILE_H
