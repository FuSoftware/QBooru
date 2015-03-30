#include "widget.h"
#include "constantes.h"
#include "fonctions.h"
#include "fonctions_json.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    cachingFile(LAST_VERSION_FILE_URL, LAST_VERSION_FILE, true, false);
    cachingFile(CHANGELOG_FILE_URL, CHANGELOG_FILE, true, false);
    setAppVersionJSON();
    setLastVersionJSON();

    Widget w;
    w.setWindowTitle(QString(APP_NAME) + QString(" ") + QString(OS_ID) + QString(" ") + QString(APP_VERSION));
    w.show();


    return a.exec();
}
