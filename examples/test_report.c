#define DEBUGLEVEL
#include <log.h>
#include <stdlib.h>
#include <report.h>
#include <database.h>

int main()
{
    INFO("Connexion");
    db_connect("ouroboros","ouroboros","ouroboros_development");

    INFO("Evaluation");
    generate_image_report(1,1,"../ouroboros/private/documents/", "./", 1);

    INFO("Déconnexion");
    db_disconnect();

    return 0;
}
