#include <mysql.h>

int db_connect(const char *login, const char *password, const char *database);
int db_exec_query(const char *query, int length);
MYSQL_RES *db_read_query(const char *query, int length);
MYSQL_ROW db_next(MYSQL_RES *res);
void db_disconnect();
