
#include "fcgi_stdio.h"
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>
#include <errno.h>

#include "replace_plus.h"

#include "critbit.h"

#include "fill_critbit.h"

#define BUF_SZ 4096

#define emit_trouble(str) printf("Trouble with %s\n", str);

int output_responses(const char *str, void *extra) {

  char *rptr;
  
  if (str!=NULL) {

    rptr = str;

    while (rptr[0] != '-' && rptr[1] != '>') {
      rptr++;
    }

    rptr += 2;

    {

      char *rel_url;

      char *path_adj;

      char *link_name;
      
      rel_url = rptr;

      path_adj = "../";

      link_name = rel_url;
      
      printf("Result: <A HREF=\"%s/%s\">%s</a> <BR>\n", path_adj, rel_url, link_name); 

    }

    return 1;
    
  }
  
  return 0;
  
}

int extract_keyword(char *query_str, char *keyword) {

  char *rptr;

  int retval;
  
  rptr = query_str;

  retval = sscanf(query_str, "search=%[^&]", keyword);
  
  return 0;
  
}

int main(int argc, char *argv[]) {

  int retval;

  char *buf;
  char *adv_p;
  size_t remaining, len = BUF_SZ;
  ssize_t bytes_read;
  ssize_t bytes_written;
  
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  int log_fd = open("/tmp/websearch.log", O_RDWR | O_CREAT | O_APPEND, mode);

  critbit0_tree crit_kw;

  buf = malloc(BUF_SZ);
  if (buf == NULL) {
    perror("malloc");
    return -1;
  }

  crit_kw.root = NULL;
  
  retval = fill_critbit(&crit_kw, "sqlcrit.txt");
  if (retval == -1) {
    emit_trouble("fill_critbit");
    return -1;
  }

  while(FCGI_Accept() >= 0) {

    memset(buf, 0, BUF_SZ);

    remaining = len;
    adv_p = buf;
    while (remaining>0) {
      bytes_read = fread(adv_p + len - remaining, 1, remaining, stdin);
      if (bytes_read <= 0) break;
      bytes_written = write(log_fd, adv_p+len-remaining, bytes_read);
      if (bytes_written != bytes_read) {

      }
      remaining -= bytes_read;
    }

    retval = replace_plus(buf, strlen(buf));
    
    printf("Content-type: text/html\r\n"
	   "\r\n"
	   "<HTML><HEAD>\n"
	   "<title>Search results</title>"
	   "</HEAD>"
	   "<BODY BGCOLOR=\"#000000\" TEXT=\"#777777\">"
	   "<h1>Search results</h1>"
	   "<HR>\n");

    printf("<DIV ID=\"results\" STYLE=\"background-color: white;\"\n");
    
    printf("<pre>");

    {

      char strbuf[256];

      char search_keyword[128];

      {

	char *query_str;

	query_str = buf;

	memset(search_keyword, 0, sizeof(search_keyword));
	
	retval = extract_keyword(query_str, search_keyword);
	
      }

      retval = sprintf(strbuf, "%s->", search_keyword);
    
      retval = critbit0_allprefixed(&crit_kw, strbuf, output_responses, NULL);

    }
    
    printf("</pre>");

    printf("</DIV>\n");
    
    printf("</body></html>");

  }

  free(buf);
  
  return 0;

}
