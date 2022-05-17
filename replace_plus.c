
#include "replace_plus.h"

int replace_plus(char *str, size_t len) {

  char *ptr;

  char *endptr;

  endptr = str + len;
  
  for (ptr = str; ptr < endptr; ptr++) {

    if (*ptr == '+') {
      *ptr = ' ';
    }

  }
  
  return 0;

}
