#include <stdio.h>
#include <string.h>

#include "database.h"

#include "log.h"

//------------------------------------------------------------
//static void exiterr(int exitcode);

//------------------------------------------------------------
MYSQL     *mysql;

int db_connect(const char *login, const char *password, const char *database)
{
    INFO("ENTER (%s,%s,%s)", login, password, database);

    mysql = mysql_init(NULL);
    if (mysql == NULL) {
        ERROR("LEAVE ERROR");
        return 0;
    } 
    INFO("init ok");

    mysql_options(mysql, MYSQL_READ_DEFAULT_GROUP, "ouroboros");
    INFO("options ok");

    if (!(mysql_real_connect(mysql, "localhost", login, password, database, 0, NULL, 0))) {
        ERROR("LEAVE ERROR (%s)", mysql_error(mysql));
        return 0;
    }

    INFO("LEAVE");
    return 1;
}

int db_exec_query(const char *query, int length)
{
    INFO("ENTER (%s, %d)", query, length);
    if (mysql_real_query(mysql,query,length)) {
        ERROR("LEAVE ERROR (%s)", mysql_error(mysql));
        return 0;
    } else {
        INFO("LEAVE OK");
        return 1;
    }
}

void db_disconnect()
{
    INFO("ENTER");
    mysql_close(mysql);
    INFO("LEAVE");
}

MYSQL_RES *db_read_query(const char *query, int length)
{
    MYSQL_RES *res;

    INFO("Query = %s", query);
    if (!db_exec_query(query, length)) {
        return NULL;
    } else if (!(res = mysql_store_result(mysql))) {
        ERROR("LEAVE ERROR (%s)", mysql_error(mysql));
        return NULL;
    }

    return res;
}

MYSQL_ROW db_next(MYSQL_RES *res)
{
    MYSQL_ROW row = mysql_fetch_row(res);

    if (row != NULL) {
        return row;
    } else {
        if (!mysql_eof(res)) {
            return NULL;
        } else {
            mysql_free_result(res);
            return NULL;
        }
    }
}
