#include <iostream>
#include <fstab.h>
#include <math.h>
#include <eigen3/Eigen/Dense>
#include <armadillo>

#include "header/easylogging++.h"
#include "header/data_struct.h"
#include "header/file.h"
#include "header/ctree.h"
#include "header/utility.h"
#include "header/data_process.h"
#include "header/cforest.h"
#include "header/NNDM.h"

using Eigen::MatrixXd;
using namespace arma;
INITIALIZE_EASYLOGGINGPP //log

int main()
{
  /* Set up log */
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
  mat data_matrix(cfg.data_size_,cfg.dimension_size_);
  vec label_vector(cfg.data_size_);
  file::ReadData("glass/glass.txt", data_matrix, label_vector);
  //dataprocess::SemiBestPartition(data_matrix,left,right,dim,point);
  LOG(INFO) << "Build a compact tree...";

  ctree *compact = new ctree(data_matrix,std::log2(data_matrix.n_rows));
  compact->BuildCtree();
  compact->PrintCtree();

  cforest *compact_forest = new cforest(data_matrix, cfg.tree_num_,
                                        cfg.sample_size_);
  compact_forest->BuildForest();
  colvec score = compact_forest->CalculateAllRareScore();
  //std::cout<<score;
  uvec index = sort_index(score);

  mat result(data_matrix.n_rows,2);
  for(int i = 0; i < data_matrix.n_rows; i++)
    {
      result(i,0) = score(index(i));
      result(i,1) = label_vector(index(i));
    }

  std::cout<<result;
  ///copy proportition
  std::vector<double> proportion;
  std::for_each(
        cfg.p_set.begin(),
        cfg.p_set.end(),
        [&proportion](t_Proportion &p){
    proportion.push_back(p.proportion_);

  });

  ///copy label
  std::vector<int> label;
  for( int i = 0; i < label_vector.size(); i++)
    {
      label.push_back(label_vector(i));
    }
 // std::cout << result;
  LOG(INFO)<<"TEST NNDM...";
  NNDM *nndm = new NNDM(data_matrix, label, proportion);
  nndm->EstimateRadius();
  return 0;
}
