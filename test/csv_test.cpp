#include <iostream>
#include <header/easylogging++.h>
#include <armadillo>
#include <string>

#include "header/file.h"
#include <stdio.h>

using namespace std;
INITIALIZE_EASYLOGGINGPP //log
int main()
{

  el::Configurations defaultConf;
  defaultConf.setToDefault();
  defaultConf.set(el::Level::Info,
                  el::ConfigurationType::Format,
                  "%datetime %level %msg");

  el::Loggers::reconfigureLogger("default", defaultConf);

  char *cfg_file = "Random/data5_config.txt";
  t_Configure  cfg;
  cfg = file::ReadConfiguraion(cfg_file);
  mat data(cfg.data_size_,cfg.dimension_size_);
  Col<size_t> label_vector(cfg.data_size_);
  file::ReadData("Random/data5.txt", data, label_vector);
  file::csv::t_csvparser_setting setting;
  setting.delimiter=',';
  setting.field_cb = file::csv::field_cb;


  std::vector<string> col_name;
  col_name.push_back(string("x"));
  col_name.push_back(string("y"));
  file::csv::WirteCSV("csv_out.csv", col_name, data);
}
