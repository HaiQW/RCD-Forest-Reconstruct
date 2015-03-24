#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <math.h>
#include <float.h>
#include <string.h>
#include <iostream>
#include "header/file.h"
#include "header/data_struct.h"

namespace file
{
  /*Read the configuration from a file*/
  t_Configure ReadConfiguraion(char* file_name );

  /* Read data from the input file*/
  bool ReadData(char* file_name, std::vector<t_Data>* des_set,int attribute_num);

  /* Write Rare Score to output file*/
  bool WriteRareScore(char* file_name, std::vector<t_Data>* src_set,
                      std::vector<t_AnomalyScore>* anomaly_score);
}
#endif // FILE_H
