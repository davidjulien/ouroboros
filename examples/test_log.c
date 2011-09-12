#include <log.h>

int main()
{
    start_log("log");

    INFO("Bonjour");

    end_log();

    return 0;
}
