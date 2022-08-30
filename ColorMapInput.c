/*********************
**  Color Map generator
** Skeleton by Justin Yokota
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"


/**************
**This function reads in a file name colorfile.
**It then uses the information in colorfile to create a color array, with each color represented by an int[3].
***************/
uint8_t** FileToColorMap(char* colorfile, int* colorcount)
{
	//YOUR CODE HERE
  FILE* file = fopen(colorfile, "r");
  if(file == NULL){
    return NULL;
  }
  int line;
  uint8_t** result = NULL;
  if(fscanf(file, "%d", &line) == 0){
    return NULL;
  }else{
    result = malloc(3 * line);
    *colorfile = line;
  }
  int a, b, c;
  for(int i = 0; i < line; i++){
    if(fscanf(file, "%d %d %d", &a, &b, &c) == 0){
      free(result);
      return NULL;
    } 
    result[i][0] = a;
    result[i][1] = b;
    result[i][2] = c;
  }
  fclose(file);
  return result;
}


