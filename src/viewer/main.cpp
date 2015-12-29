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

#include "Widget/qstartupwidget.h"
#include "Workers/imagegrabber.h"


using namespace std;

int main(int argc, char *argv[])
{
    int exit_code = 0;

    srand(time(NULL));
    std::freopen(LOG_FILE, "a", stdout);

    clog << endl;

    std::cout << std::endl;

    /*Main loop*/
    QApplication *a = new QApplication(argc, argv);

    /*Config file*/
    QStartupWidget *s = new QStartupWidget(0);
    s->process();
    ConfigFile *cfg = s->getCfg(); 

    s->updateStatus("Loading the main software");

    /* Main Widget*/
    QIcon icone;
    icone.addFile(ICON_PATH);

    outputInfo(L_INFO,std::string("Generating Widget"));
    Widget *w = new Widget(cfg,0);

    w->setWindowTitle(QString(APP_NAME) + QString(" ") + QString(OS_ID) + QString(" ") + QString(APP_VERSION));
    outputInfo(L_DEBUG,std::string("Showing Widget"));

    s->close();
    w->show();

    exit_code = a->exec();

    if(exit_code == EXIT_CODE_UPDATE)
    {
        //Updates the software
        QFile old_file(QString(EXECUTABLE));
        QFile new_file(QString(EXECUTABLE_DL));

        old_file.rename(QString(EXECUTABLE) + QString(".old"));
        new_file.rename(EXECUTABLE);
    }

    return exit_code;
}
