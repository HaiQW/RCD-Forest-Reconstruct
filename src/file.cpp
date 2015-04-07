#include "header/file.h"

t_Configure file::ReadConfiguraion(char *file_name)
{
  std::fstream cfg_file(file_name, std::ios::in);
  ///cfg_file.open();
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

      ///Read all class proportion
      if(std::string(status) == std::string("PROPORTION_NUM"))
      {
          for(int i = 0; i < config.class_num_; i++)
          {
              t_Proportion proportion;
              cfg_file>>proportion.class_label_>>proportion.proportion_;
              proportion.class_num_ = 0;
              proportion.r_ = DBL_MAX;///set r_ DBL_MAX
              proportion.is_discovered_ = false;
              config.p_set.push_back(proportion);
          }
      }
      delete[] status;
    }

  ///cfg_file.close();
  return config;
}



void file::ReadData(const char *file_name, mat &data_matrix,
                   Col<size_t> &label_vector)
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


file::csv::t_csvparser &file::csv::ReadCSV(const char *file_name,
                                           const file::csv::t_csvparser_setting *setting)
{
  std::fstream csv_file(file_name, std::ios::in);
  if(!csv_file.is_open())
    {
      std::cerr<<"could not open the file : "<<file_name<<std::endl;
      exit(1);
    }

  file::csv::t_csvparser parser;
  file::csv::t_csv csv;
  ssize_t nread;
  const char *buffer;
  std::string line;

  csv.head = nullptr;
  csv.tail = nullptr;
  file::csv::csvparser_init(&parser);
  parser.data = &csv;

  while(!csv_file.eof())
    {
      /// read a line from the csv file and parse this line
      std::getline(csv_file,line);
      buffer = line.c_str();
      nread = line.size();
      file::csv::csvparser_execute(&parser, setting, buffer, nread);
      line.clear();
    }

  return parser;
}


void file::csv::csvparser_init(file::csv::t_csvparser *parser)
{
  assert(parser);
  parser->state = line_start;
  parser->row = -1;
  parser->col = -1;
  parser->nread = 0;
  parser->data = nullptr;
}


size_t file::csv::csvparser_execute(file::csv::t_csvparser *parser,
                                    const file::csv::t_csvparser_setting *setting,
                                    const char *data, size_t data_len)
{
  assert(parser);
  assert(setting);
  assert(data);

  const char *cursor = data;
  const char *value = data;
  const char *data_end = data + data_len;
  int r;
  parser->nread = 0;

  if( data_len < 1)
    {
      return 0;
    }

  while( cursor < data_end )
    {
      char ch = *cursor;
      switch(parser->state)
        {
        case line_start:
          value = cursor;
          parser->row += 1;
          parser->col = -1;
          parser->state = field_start;
          break;
        case field_start:
          parser->col += 1;
          parser->state = field_value;
          value = cursor;
          break;
        case field_value:
          if( ch == setting->delimiter)
            {
              parser->state = field_end;
            }
          else
            {
              cursor++;
              if(value == nullptr) value = cursor;
              if(cursor == data_end)
                {
                  if(setting->field_cb && value)
                    {
                      r = setting->field_cb(parser,
                                            value,
                                            cursor - value,
                                            parser->row,
                                            parser->col);
                      ASSERT_CSV_READ(r,parser);
                    }
                }
              parser->nread++;
            }
          break;
        case field_end:
          /// callback
          if(setting->field_cb && value)
            {
              r = setting->field_cb(parser,
                                    value,
                                    cursor - value,
                                    parser->row,
                                    parser->col);
              ASSERT_CSV_READ(r,parser);
            }
          parser->state = field_start;
          cursor++;
          parser->nread++;
          break;
        case error:
          return parser->nread;
          break;
        default:
          assert(0 && " invalid parser state ");
          break;
        }
    }
  parser->state = line_start;
  return parser->nread;
}


bool file::csv::field_cb(file::csv::t_csvparser *parser, const char *data,
                        size_t length, int row, int col)
{
  file::csv::t_csv *csv = (file::csv::t_csv*)parser->data;
  file::csv::t_field *field = nullptr;

  field = file::csv::new_field(data, length, row, col);
  if(field == nullptr) return false;

  if(!csv->tail)///first assignment
    {
      csv->tail = field;
      csv->head = field;
    }
  else
    {
      csv->tail->next = field;
      csv->tail = field;
    }

  return true;
}


file::csv::t_field *file::csv::new_field(const char *data,
                                         size_t length,
                                         int row, int col)
{
  file::csv::t_field *field = (file::csv::t_field*)malloc
      (sizeof(file::csv::t_field));
  memset(field, 0, sizeof(file::csv::t_field));
  field->row = row;
  field->col = col;
  strncpy(field->data, data, length);

  return field;
}


bool file::csv::WirteCSV(const char *file_name,
                         const std::vector<std::string> &col_name,
                         const mat &data_matrix)
{

  if((col_name.size() != 0) && col_name.size() != data_matrix.n_cols )
    {
      std::cerr<<"the col_name number is not match with the data "
                 "attribute number."<<std::endl;
      return false;
    }

  std::ofstream csv_file(file_name);
  if(!csv_file.is_open())
    {
      std::cerr<<"could not init the "<<file_name<< " ."<<std::endl;
    }

  /// write csv columns at the first line in the csv file
  for(unsigned int i = 0; i < col_name.size(); i++)
    {
      if(i == col_name.size() - 1)
        {
          csv_file << col_name.at(i) << std::endl;
        }
      else
        {
          csv_file << col_name.at(i)<<",";
        }
    }

  /// write data matrix into the csv file
  for(unsigned int i = 0; i < data_matrix.n_rows; i++)
    {
      for(unsigned int j = 0; j < data_matrix.n_cols; j++)
        {
          if(j == data_matrix.n_cols - 1)
            {
              csv_file << data_matrix(i,j)<<endl;
            }
          else
            {
              csv_file << data_matrix(i,j)<<",";
            }
        }
    }

  csv_file.close();
  return true;
}


void file::csv::ReadCSV(const char *file_name,
                        const file::csv::t_csvparser_setting *setting,
                        arma::mat &data_matrix,
                        colvec &label)
{
  t_csvparser parser = ReadCSV(file_name,setting);
  file::csv::t_csv *data = (file::csv::t_csv*)parser.data;
  t_field *f = data->head;
  while(f)
    {
       std::cout<<f->data<<","<<std::endl;
    }
}
