#include <iostream>
#include <fstab.h>

#include "header/easylogging++.h"
#include "header/data_struct.h"
#include "header/file.h"
#include "header/ctree.h"

#include "eigen3/Eigen/Dense"

using Eigen::MatrixXd;

INITIALIZE_EASYLOGGINGPP //log
//using namespace std;

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

  LOG(INFO) << "Build a compact tree...";
  ctree* compact_tree = new ctree(data_matrix,10);
  compact_tree->BuildCTree();

   return 0;
}
