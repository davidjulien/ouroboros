#include <database.h>
#include <log.h>

int main()
{
   start_log("log");
   db_connect("ouroboros","ouroboros", "ouroboros_development");
   db_exec_query("SELECT * FROM users", 10);
   db_disconnect();

   return 1;
}
