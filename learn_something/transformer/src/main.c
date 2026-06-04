#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Tensor
{
  int shape[2];
  int ndim;
  double data_buffer[1024];
  struct Tensor* children[2];
  void (*backward)(struct Tensor*);

} Tensor;

// round1
// i < 4  i = 0
// k = 0 k < 2
// print 0 1
// round 2
// k = 1 k <

void show_matrix(Tensor* a)
{
  int row = a->shape[0];
  int col = a->shape[1];

  for (int i = 0; i < row * col; i++) {
    printf("%lf ", a->data_buffer[i]);

    if ((i + 1) % col == 0) {
      printf("\n");
    }
  }
}

Tensor* init_tensor(double data_buffer[], int ndim, int row, int col)
{
  Tensor* res = malloc(sizeof(Tensor));
  res->ndim = ndim;
  res->shape[0] = row;
  res->shape[1] = col;
  for (int i = 0; i < row * col; i++) {
    res->data_buffer[i] = data_buffer[i];
  }
  return res;
}

Tensor* tensor_mul(Tensor* a, Tensor* b)
{
  double res_buffer[1024] = {0};
  int res_ndim = 0;
  int res_row = 0;
  int res_col = 0;
  if (a->ndim == 0) {
    for (int i = 0; i < b->shape[0] * b->shape[1]; i++) {
      res_buffer[i] = b->data_buffer[i] * a->data_buffer[0];
      res_ndim = b->ndim;
      res_row = b->shape[0];
      res_col = b->shape[1];
    }

    return init_tensor(res_buffer, res_ndim, res_row, res_col);
  }

  if (b->ndim == 0) {
    for (int i = 0; i < a->shape[0] * a->shape[1]; i++) {
      res_buffer[i] = a->data_buffer[i] * b->data_buffer[0];
      res_ndim = a->ndim;
      res_row = a->shape[0];
      res_col = a->shape[1];
    }

    return init_tensor(res_buffer, res_ndim, res_row, res_col);
  }

  if (a->shape[1] != b->shape[0]) {
    return NULL;
  }
  // a->row * b->col
  // index = i * C + j (i,j)
  // 首先确定，我们最终需要的是res_buffer对吧，也就是最终的矩阵
  // 那么我们就遍历最终矩阵的行和列，那因为我们知道index = i * C + j (可以得到希望的坐标)
  // 前行乘后列，所以是a的row b的col, 然后我们知道，如果矩阵能相乘，那必须是MxN * N * P的一个格式
  // 所以我们用这个N来当共同变化量k，就能算出需要的目标index
  // 类似于什么 res_buffer[0][0] = a[0][0] * b[0][0] + a[0][1] * a[1][0] .... + a[0][k] * a[k][0] == for k in a_col res_buffer[0][0] += a[0][k] * a[k][0]

  // 所以我们要求res_buffer的 (i, j) 的值，一个道理，先求出
  // res_index = i * res_col + j
  // a_index = i * a_col + k;
  // b_index = k * a_col + j;
  res_row = a->shape[0];
  res_col = b->shape[1];
  res_ndim = a->ndim;
  for (int i = 0; i < res_row; i++) {
    for (int j = 0; j < res_col; j++) {
      int res_index = i * res_col + j;
      for (int k = 0; k < a->shape[1]; k++) {
        int a_index = i * a->shape[1] + k;
        // b 和 a 是相反的，因为矩阵乘法的前行乘后列
        int b_index = k * b->shape[1] + j;
        res_buffer[res_index] += a->data_buffer[a_index] * b->data_buffer[b_index];
      }
    }
  }
  return init_tensor(res_buffer, res_ndim, res_row, res_col);
}

void safe_softmax(double data_buffer[], int size)
{
  double max_val = data_buffer[0];

  double sum = 0;
  for (int i = 0; i < size; i++) {
    max_val = fmax(max_val, data_buffer[i]);
  }

  for (int i = 0; i < size; i++) {
    double exp_val = exp(data_buffer[i] - max_val);
    sum += exp_val;
    data_buffer[i] = exp_val;
  }

  for (int i = 0; i < size; i++) {
    data_buffer[i] /= sum;
    printf("%lf\n", data_buffer[i]);
  }
}

int main(int argc, char* argv[])
{
  double data[] = {1, 1, 1, 1};
  Tensor* a = init_tensor(data, 2, 2, 2);
  Tensor* b = init_tensor(data, 2, 2, 2);
  Tensor* c = tensor_mul(a, b);
  safe_softmax(data, 4);
  // show_matrix(c);

  return 0;
}
