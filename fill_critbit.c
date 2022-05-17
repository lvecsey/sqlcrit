
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "critbit.h"

int fill_critbit(critbit0_tree *c, char *filename) {

  FILE *fp = fopen(filename, "r");
  char *line = NULL;
  size_t len = 0;

  ssize_t bytes_read;

  char entry[80];

  char *rptr;
  
  if (fp==NULL) return -1;

  while (( bytes_read = getline(&line, &len, fp)) != -1) {

    if (len>0) {

      rptr = line;

      while (rptr[0] != '\n') {
	rptr++;
      }

      rptr[0] = 0;
      
      critbit0_insert(c, line);
      
    }
      
  }
  
  free(line);
  fclose(fp);
  
  return 0;
  
}

