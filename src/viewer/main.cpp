#include "widget.h"
#include "classBooruSite.h"
#include <QApplication>
#include <QIcon>
#include <QMessageBox>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <QMessageBox>

#include "fonctions_all.h"

#include "Widget/imageTabClass.h"
#include "Widget/optionTabClass.h"
#include "Widget/searchTabClass.h"
#include "Widget/viewerTabClass.h"

#include "config_file.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication *a = new QApplication(argc, argv);
    std::freopen(LOG_FILE, "a", stdout);

    clog << endl;

    std::cout << std::endl;

    cachingFile(UPDATER_URL, UPDATER_MAIN_EXECUTABLE, false, false);

    cachingFile(BOORU_LIST_URL, BOORU_LIST, false, false);

    cachingFile(CONF_FILE_URL, CONF_FILE, false, true);

    ConfigFile confFile(false);

    QIcon icone;
    icone.addFile(ICON_PATH);

    outputInfo(L_INFO,std::string("Generating Widget"));
    Widget w;

    w.setWindowTitle(QString(APP_NAME) + QString(" ") + QString(OS_ID) + QString(" ") + QString(APP_VERSION));
    outputInfo(L_DEBUG,std::string("Showing Widget"));
    w.show();

    int ret = a->exec();
    w.deleteLater();
    a->deleteLater();

    return ret;
}
