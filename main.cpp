#include <iostream>
#include <fstab.h>
#include <math.h>
#include <eigen3/Eigen/Dense>
#include <armadillo>

#include "mlpack/methods/pca/pca.hpp"
#include <mlpack/methods/kmeans/kmeans.hpp>
#include <mlpack/methods/neighbor_search/neighbor_search.hpp>

#include "header/easylogging++.h"
#include "header/data_struct.h"
#include "header/file.h"
#include "header/ctree.h"
#include "header/utility.h"
#include "header/data_process.h"
#include "header/cforest.h"
#include "header/kdd.h"
#include "header/assert.h"

using Eigen::MatrixXd;
//using namespace arma;
using namespace mlpack::pca;
using namespace mlpack::kmeans;
using namespace mlpack::neighbor;

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
  char *cfg_file = "Random/data5_config.txt";

  t_Configure  cfg;
  LOG(INFO) << "Reading configuration file...";
  cfg = file::ReadConfiguraion(cfg_file);

  LOG(INFO) << "Reading Data file...";
  mat data_matrix(cfg.data_size_,cfg.dimension_size_);
  Col<size_t> label_vector(cfg.data_size_);
  file::ReadData("Random/data5.txt", data_matrix, label_vector);

  LOG(INFO) << "Build a compact tree...";
  inplace_trans(data_matrix);
  mat result1;
  vec eigval;
  mat eigvec;
  PCA pca_test;
  pca_test.Apply(data_matrix, result1, eigval, eigvec);
  inplace_trans(data_matrix);
  mat datas (data_matrix.n_rows, 2);
  datas.col(0) = data_matrix.col(0);
  datas.col(1) = data_matrix.col(1);
  //datas.col(2) = data_matrix.col(2);
  //datas.col(3) = data_matrix.col(3);
  cforest *compact_forest = new cforest(datas, cfg.tree_num_,
                                        cfg.sample_size_);
  compact_forest->BuildForest(20);
  colvec score = compact_forest->CalculateAllRareScore();
  uvec index = sort_index(score);

  unsigned candidate_size = 18458;
  mat kdd_data(candidate_size,2);
  colvec label(candidate_size);
  for(int i = 0; i < candidate_size; i++)
    {

       label(i) = label_vector(index(i));
       kdd_data.row(i) = datas.row(i);
    }
  std::cout<<label;

  inplace_trans(kdd_data);

  LOG(INFO)<<"TEST NNDM...";/*! transpose the matrix */
  KDD *kdd = new KDD(kdd_data, label, 5, 20);
  //kdd->DiscoverClass();
  return 0;
}
