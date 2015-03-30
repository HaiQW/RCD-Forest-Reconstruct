#include "header/file.h"

t_Configure file::ReadConfiguraion(char *file_name)
{
  std::fstream cfg_file(file_name, std::ios::in);
  //cfg_file.open();
  if(!cfg_file.is_open())
    {
      std::cerr<<"error:could not open"<<file_name<<"!"<<
      std::endl;
      exit(-1);
    }

  t_Configure config;
  while(!cfg_file.eof())
    {
      char* status = new char[20];
      cfg_file>>status;
      if(std::string(status) == std::string("CONFIGURATION_NUM"))
        {
          std::string discared1, discared2, file_name;
          cfg_file>>discared1>>discared2>>file_name;
          config.data_file_ = new char(strlen(file_name.c_str()) + 1);
          strcpy(config.data_file_,file_name.c_str());

          file_name.clear();
          cfg_file>>discared1>>discared2>>file_name;
          config.score_file_ = new char(strlen(file_name.c_str()) + 1);
          strcpy(config.score_file_,file_name.c_str());

          file_name.clear();
          cfg_file>>discared1>>discared2>>file_name;
          config.cluster_file_ = new char(strlen(file_name.c_str()) + 1);
          strcpy(config.cluster_file_,file_name.c_str());

          file_name.clear();
          cfg_file>>discared1>>discared2>>file_name;
          config.lof_file_1_ = new char(strlen(file_name.c_str()) + 1);
          strcpy(config.lof_file_1_,file_name.c_str());

          file_name.clear();
          cfg_file>>discared1>>discared2>>file_name;
          config.lof_file_2_ = new char(strlen(file_name.c_str()) + 1);
          strcpy(config.lof_file_2_,file_name.c_str());

          cfg_file>>discared1>>discared2>>config.class_num_;
          cfg_file>>discared1>>discared2>>config.dimension_size_;
          cfg_file>>discared1>>discared2>>config.data_size_;
          cfg_file>>discared1>>discared2>>config.sample_size_;
          cfg_file>>discared1>>discared2>>config.tree_num_;
          cfg_file>>discared1>>discared2>>config.cluster_num_;
          cfg_file>>discared1>>discared2>>config.bin_width_;
        }

      /*Read all class proportion*/
      if(std::string(status) == std::string("PROPORTION_NUM"))
      {
          for(int i = 0; i < config.class_num_; i++)
          {
              t_Proportion proportion;
              cfg_file>>proportion.class_label_>>proportion.proportion_;
              proportion.class_num_ = 0;
              proportion.r_ = DBL_MAX;//set r_ DBL_MAX
              proportion.is_discovered_ = false;
              config.p_set.push_back(proportion);
          }
      }
      delete[] status;
    }

  //cfg_file.close();
  return config;
}



void file::ReadData(const char *file_name, mat &data_matrix,
                    vec &label_vector)
{
  std::fstream data_file(file_name, std::ios::in);

  if(!data_file.is_open())
    {
      std::cerr<<"error:could not open the file!"
          <<file_name<<std::endl;
      exit(-1);
    }

  /*read data file by line*/
  int rows = data_matrix.n_rows;
  int cols = data_matrix.n_cols;
  int i;
  for(i = 0; i < rows; i++)
    {
      double label = DBL_MAX;

      int j;
      for(j = 0; j < cols; j++)
        {
          double attribute = DBL_MAX;
          data_file>>attribute;
          data_matrix(i,j) = attribute;
        }

      /* Read the class label*/
      data_file>>label;
      label_vector(i,0) = label;
    }
  data_file.close();
}
