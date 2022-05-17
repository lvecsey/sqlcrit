
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>
#include <errno.h>

#include <sqlite3.h>

#define emit_trouble(str) printf("Trouble with %s\n", str);

int main(int argc, char *argv[]) {

  const char *sqlite_vers;

  sqlite3 *db;

  sqlite3_stmt *res;

  int rc;
  
  sqlite_vers = sqlite3_libversion();

  fprintf(stderr, "SQLite DB version %s\n", sqlite_vers);

  rc = sqlite3_open("sqlcrit.db", &db);
  if (rc != SQLITE_OK) {
    emit_trouble("sqlite3_open");
    return -1;
  }

  rc = sqlite3_prepare_v2(db, "SELECT * from keywords;", -1, &res, 0);    
  if (rc != SQLITE_OK) {
    emit_trouble("select statement");
    sqlite3_close(db);
    return 1;
  }      

  do {
  
    rc = sqlite3_step(res);
    if (rc == SQLITE_ROW) {
      printf("%s->%s\n", sqlite3_column_text(res, 0), sqlite3_column_text(res, 1));
    }

  } while (rc == SQLITE_ROW);
    
  sqlite3_finalize(res);

  sqlite3_close(db);  
  
  return 0;

}
