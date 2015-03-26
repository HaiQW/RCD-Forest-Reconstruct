#include<header/data_process.h>


void dataprocess::RandomSampling(const std::vector<t_Data> *src,
                                 std::vector<t_Data> *result, int size)
{

}


bool dataprocess::SemiBestPartition(Eigen::MatrixXd &source,
                                    Eigen::MatrixXd &left,
                                    Eigen::MatrixXd &right,
                                    int &par_dim, double &par_point)
{

  double semi_best_score = -__DBL_MAX__;
  int size = source.size();
  par_dim = random()%source.cols(); //randomly select a partition dimension

  /*sort the elements in the selected dimension, we get an sorted index*/
  Eigen::VectorXi order_index = utility::RowArgSort(source, par_dim);

  /* calculate semi-best score*/
  int i = 0;
  double sum = 0.0, right_avg = 0.0, right_avg_dis = 0.0;
  for(i = 0; i < size; i++)
    {
      double tmp_value = source(order_index(i), par_dim);
      sum += tmp_value;
      right_avg_dis += tmp * tmp_value;
    }
  right_avg = sum / size;
  right_avg_dis = right_avg_dis + (size * right_avg * right_avg) -
      (2 * right_avg * sum);

  int j = 0;
  double left_avg = 0.0, left_avg_dis = 0.0;
  for(j = 0; j < size; j++)
    {
      double tmp_value = source(order_index(i), par_dim);

      /* left side */
      double left_tmp_avg = (left_avg * j + tmp_value) / (j + 1);
      left_avg_dis = left_avg_dis + (tmp_value * tmp_value) +
          2 * (left_tmp_avg - left_avg) * j + left_tmp_avg * tmp_value +
          j * left_temp_avg * left_temp_avg - (j - 1) * left_avg * left_avg;

      /* right side */
      double right_tmp_avg = (right_avg * (size - j) - tmp_value) / (size - j -1)

      left_avg = left_tmp_avg;

    }
}
