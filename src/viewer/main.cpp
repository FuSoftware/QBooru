#include "widget.h"
#include "classBooruSite.h"
#include <QApplication>
#include <QObject>
#include <QEventLoop>
#include <QIcon>
#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "fonctions_all.h"

#include "config_file.h"
#include "BooruHeaders/boorutaglist.h"
#include "Workers/qnamredirect.h"


using namespace std;

int main(int argc, char *argv[])
{
    int exit_code = 0;

    srand(time(NULL));
    std::freopen(LOG_FILE, "a", stdout);

    clog << endl;

    std::cout << std::endl;

    /*Main loop*/
    do
    {
        QApplication *a = new QApplication(argc, argv);

        /*Config file*/
        ConfigFile  *conf = new ConfigFile(false);

        QIcon icone;
        icone.addFile(ICON_PATH);

        outputInfo(L_INFO,std::string("Generating Widget"));
        Widget *w = new Widget(conf,0);

        w->setWindowTitle(QString(APP_NAME) + QString(" ") + QString(OS_ID) + QString(" ") + QString(APP_VERSION));
        outputInfo(L_DEBUG,std::string("Showing Widget"));
        w->show();

        exit_code = a->exec();
    }while(exit_code == EXIT_CODE_REBOOT);

    return EXIT_SUCCESS;
}
