#include <iostream>
#include <fstab.h>
#include <math.h>

#include "header/easylogging++.h"
#include "header/data_struct.h"
#include "header/file.h"
#include "header/ctree.h"
#include "header/utility.h"
#include "header/data_process.h"
#include "eigen3/Eigen/Dense"

using Eigen::MatrixXd;

INITIALIZE_EASYLOGGINGPP //log

int main()
{
  /* Set Up Log*/
  el::Configurations defaultConf;
  defaultConf.setToDefault();
  defaultConf.set(el::Level::Info,
                  el::ConfigurationType::Format,
                  "%datetime %level %msg");

  el::Loggers::reconfigureLogger("default", defaultConf);

  std::vector<t_Data> data_set;
  char *cfg_file = "glass/glass_config.txt";

  t_Configure  cfg;
  LOG(INFO) << "Reading configuration file...";
  cfg = file::ReadConfiguraion(cfg_file);

  LOG(INFO) << "Reading Data file...";
  Eigen::MatrixXd data_matrix(cfg.data_size_, cfg.dimension_size_);
  Eigen::VectorXi label_vector(cfg.data_size_);
  file::ReadData("glass/glass.txt", data_matrix, label_vector);

 // dataprocess::SemiBestPartition(data_matrix,left,right,dim,point);
  LOG(INFO) << "Build a compact tree...";
  ctree *compact = new ctree(data_matrix,std::log2(data_matrix.rows()));
  compact->BuildCtree();
  compact->PrintCtree();


  return 0;
}
