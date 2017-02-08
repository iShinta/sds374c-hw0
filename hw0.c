#include <stdio.h>
#include <stdlib.h>
#define N 10

//Use single precision float/real variables throughout the excercise.
public void initialize(double *x, double n){
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      x[i*n + j] = (double)(rand() / (float)RAND_MAX);
    }
  }
}

public void smooth(double *x, double*y, int n, double a, double b, double c){
  for(i = 1; i < n - 1; i++){
    for(j = 1; j < n - 1; j++){
      y[i*n + j] = a * (x[(i-1)*n+(j-1)] + x[(i-1)*n+(j+1)] + x[(i+1)*n+(j-1)] + x[(i+1)*n+(j+1)])
                  + b * (x[(i-1)*n+(j)] + x[(i+1)*n+(j)] + x[(i)*n+(j-1)] + x[(i)*n+(j+1)])
                  + c * (x[i*n+j]);
    }
  }
}

public void count(double *y, int n, double t, int res){
  for(i = 1; i < n - 1; i++){
    for(j = 1; j < n - 1; j++){
      if(y[i*n + j] < t){
        res++;
      }
    }
  }
}

int main(){
  int i, j;
  int res;
  const double a = 0.05;
  const double b = 0.1;
  const double c = 0.4;

  double t = 0.1; //threshold
  int n = 16384+2; //the 2 elements are the border of the array

  //Declare two arrays, using malloc
  //Allocate the arrays of n in each direction
  //2D arrays have to be contiguous in memory
  double *x, *y;

  x = (double *) malloc(n * n * sizeof(double)); //allocate n*n doubles
  y = (double *) malloc(n * n * sizeof(double)); //allocate n*n doubles

  initialize(x, n);
  smooth(x, y, n, a, b, c);
  count(y, n, t, res);
}
