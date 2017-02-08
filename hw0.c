#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Use single precision float/real variables throughout the excercise.
void initialize(double *x, int n){
  int i, j;
  double random;
  int nest;
  double temp;
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      //temp = (double)((float)rand() / (float)RAND_MAX);
      //temp = (double)rand() / (double)((unsigned)RAND_MAX);
      // temp = (double)((rand()%10000)/(double)10000);
      // x[i*n + j] = temp;
      // printf("%d\n", temp);

      random = (double)((rand()%10000)/(double)10000);
      //printf("%9.7f\n", random);
      x[i*n + j] = random;
      //printf("%9.7f\n", random);
      //printf("%9.7f\n", x[i*n + j]);
    }
  }
}

void smooth(double *x, double*y, int n, double a, double b, double c){
  int i, j;
  for(i = 1; i < n - 1; i++){
    for(j = 1; j < n - 1; j++){
      y[i*n + j] = a * (x[(i-1)*n+(j-1)] + x[(i-1)*n+(j+1)] + x[(i+1)*n+(j-1)] + x[(i+1)*n+(j+1)])
                  + b * (x[(i-1)*n+(j)] + x[(i+1)*n+(j)] + x[(i)*n+(j-1)] + x[(i)*n+(j+1)])
                  + c * (x[i*n+j]);
    }
  }
}

void count(double *y, int n, double t, int res){
  int i, j;
  for(i = 1; i < n - 1; i++){
    for(j = 1; j < n - 1; j++){
      if(y[i*n + j] < t){
        res++;
      }
    }
  }
}

int main(){
  //struct timeval t1;
  //gettimeofday(&t1, NULL);
  //srand(t1.tv_usec * t1.tv_sec);
  //srand(time(0));
  //srand(unsigned int seed);
  srand(time(NULL));

  int resx, resy;
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
  count(x, n, t, resx);
  count(y, n, t, resy);

  printf("Summary\n");
  printf("-------\n");
  printf("Number of elements in a row/column        ::              %i\n", n);
  printf("Number of inner elements in a row/column  ::              %i\n", n-2);
  printf("Total number of elements                  ::              %i\n", n*n);
  printf("Total number of inner elements            ::              %i\n", (n-2)*(n-2));
  printf("Memory (GB) used per array)               ::              %d\n", sizeof(double));
  printf("Threshold                                 ::              %d\n", t);
  printf("Smoothing constants (a, b, c)             :: %d %d %d\n", a, b, c);
  printf("Number    of elements below threshold (X) ::              %i\n", resx);
  printf("Fraction  of elements below threshold     ::              %d\n", (double)(resx/(n*n)));
  printf("Number    of elements below threshold (Y) ::              %i\n", resy);
  printf("Fraction  of elements below threshold     ::              %d\n", (double)(resy/((n-2)*(n-2))));

  return 0;
}
