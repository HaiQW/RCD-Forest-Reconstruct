#include<header/data_process.h>


void dataprocess::RandomSampling(const std::vector<t_Data> *src,
                                 std::vector<t_Data> *result, int size)
{

}


bool dataprocess::SemiBestPartition(mat &source,
                                    mat &left,
                                    mat &right,
                                    int &par_dim, double &par_point)
{
  if(source.n_rows <= 1)
    {
      return false;
    }
  double semi_best_score = __DBL_MAX__;
  int size = source.n_rows;
  int semi_best_index = -1;

  std::srand((unsigned)time(NULL));
  par_dim = random()%source.n_cols; /*!< randomly select a partition dimension*/

  /*! sort the elements in the selected dimension, we get an sorted index*/
  uvec order_index = sort_index(source.col(par_dim));

  /* calculate semi-best score*/
  int i = 0;
  double sum = 0.0, right_avg = 0.0, right_dis = 0.0;
  for(i = 0; i < size; i++)
    {
      double tmp_value = source(order_index(i), par_dim);
      sum += tmp_value;
      right_dis += tmp_value * tmp_value;
    }
  right_avg = sum / size ;
  right_dis = right_dis + (size * right_avg * right_avg) -
      (2 * right_avg * sum);

  int j;
  double left_avg = 0.0, left_dis = 0.0;
  for(j = 0; j < size - 1; j++)
    {
      double tmp_value = source(order_index(j), par_dim);

      /* calculate the left side average distance */
      double left_tmp_avg = (left_avg * j + tmp_value) / (j + 1);
      left_dis = left_dis + (tmp_value - left_tmp_avg) * (tmp_value - left_tmp_avg)-
          2 * (left_tmp_avg - left_avg) * left_avg * j +
          left_tmp_avg * left_tmp_avg * j - left_avg * left_avg * j;

      /* calculate the right side average distance */
      double right_tmp_avg = ((right_avg * (size - j) - tmp_value)) /
          (size - j -1);
      right_dis = right_dis - ( tmp_value - right_avg) * (tmp_value - right_avg) -
          2 * (right_tmp_avg - right_avg) * right_tmp_avg * (size - j - 1) +
          (size - j - 1) * right_tmp_avg * right_tmp_avg - (size - j - 1) * right_avg * right_avg;

      if((left_dis + right_dis) < semi_best_score)
        {
          semi_best_score = left_dis + right_dis;
          par_point = tmp_value;
          semi_best_index = j;
        }

      left_avg = left_tmp_avg;
      right_avg = right_tmp_avg;
    }

  /* Assign the elements to each sub set */
  left.set_size(semi_best_index + 1, source.n_cols);
  right.set_size(size - semi_best_index - 1, source.n_cols);
  for( int k = 0; k < size; k++)
    {
      if(k <= semi_best_index)
        {
          left.row(k) = source.row(order_index(k));
        }
      else
        {
          right.row(k - semi_best_index -1) = source.row(order_index(k));
        }
    }

  return true;
}
