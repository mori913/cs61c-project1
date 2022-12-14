/*********************
**  Mandelbrot fractal
** clang -Xpreprocessor -fopenmp -lomp -o Mandelbrot Mandelbrot.c
** by Dan Garcia <ddgarcia@cs.berkeley.edu>
** Modified for this class by Justin Yokota and Chenyu Shi
**********************/

#include <stdio.h>
#include <stdlib.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include <sys/_types/_u_int64_t.h>
#include <sys/types.h>

/*
This function returns the number of iterations before the initial point >= the threshold.
If the threshold is not exceeded after maxiters, the function returns 0.
*/
u_int64_t MandelbrotIterations(u_int64_t maxiters, ComplexNumber * point, double threshold)
{
    //YOUR CODE HERE
  ComplexNumber* z = newComplexNumber(0,0);
  ComplexNumber* c = point;
  for(u_int64_t i = 1; i <= maxiters; i++){
    ComplexNumber* product = ComplexProduct(z, z);
    ComplexNumber* mandelbrot = ComplexSum(product, c);
    freeComplexNumber(z);
    freeComplexNumber(product);
    if(ComplexAbs(mandelbrot) >= threshold){
      freeComplexNumber(mandelbrot);
      return i;
    }
    z = mandelbrot;
  }
  freeComplexNumber(z);
  return 0;
}

/*
This function calculates the Mandelbrot plot and stores the result in output.
The number of pixels in the image is resolution * 2 + 1 in one row/column. It's a square image.
Scale is the the distance between center and the top pixel in one dimension.
*/
void Mandelbrot(double threshold, u_int64_t max_iterations, ComplexNumber* center, double scale, u_int64_t resolution, u_int64_t * output){
    //YOUR CODE HERE
  double grid_size = scale/resolution;
  double real_at_left_top_corner = Re(center) - scale;
  double imaginary_at_left_top_corner = Im(center) + scale;
  for(int i = 0; i < 2*resolution+1; i++){
    for(int j = 0; j < 2*resolution+1; j++){
      ComplexNumber* current_point = newComplexNumber(real_at_left_top_corner + grid_size * j, imaginary_at_left_top_corner - grid_size * i);
      output[(2*resolution + 1) * i + j] = MandelbrotIterations(max_iterations, current_point, threshold);
      freeComplexNumber(current_point);
    }
  }
}


