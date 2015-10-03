#include "widget.h"
#include "classBooruSite.h"
#include <QApplication>
#include <QIcon>
#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "fonctions_all.h"

#include "Widget/imageTabClass.h"
#include "Widget/optionTabClass.h"
#include "Widget/searchTabClass.h"
#include "Widget/viewerTabClass.h"

#include "config_file.h"

#include "BooruHeaders/boorutaglist.h"


using namespace std;

int main(int argc, char *argv[])
{
    int exit_code = 0;

    srand(time(NULL));
    std::freopen(LOG_FILE, "a", stdout);

    clog << endl;

    std::cout << std::endl;

    do
    {
        QApplication *a = new QApplication(argc, argv);
        cachingFile(BOORU_LIST_URL, BOORU_LIST, false, false);
        cachingFile(CONF_FILE_URL, CONF_FILE, false, true);
        cachingFile(CHANGELOG_FILE_URL, CHANGELOG_FILE, false, false);
        ConfigFile confFile(false);

        QIcon icone;
        icone.addFile(ICON_PATH);

        outputInfo(L_INFO,std::string("Generating Widget"));
        Widget w;

        w.setWindowTitle(QString(APP_NAME) + QString(" ") + QString(OS_ID) + QString(" ") + QString(APP_VERSION));
        outputInfo(L_DEBUG,std::string("Showing Widget"));
        w.show();

        exit_code = a->exec();
    }while(exit_code == EXIT_CODE_REBOOT);

    return EXIT_SUCCESS;
}
