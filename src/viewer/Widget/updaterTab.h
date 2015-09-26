#ifndef UPDATER_TAB_H
#define UPDATER_TAB_H

#include <QWidget>
#include <QtWidgets>

#include <QDesktopServices>

#include "./widget.h"

#include "./fonctions/fonctions.h"
#include "./constantes.h"

class UpdaterTab : public QWidget
{
    Q_OBJECT

public:
    UpdaterTab(Widget *parent = 0);
    ~UpdaterTab();

    void checkQtChanges();

public slots:
    void updateSoftware();
    void refreshInterface();

signals:
    void rebootApp();
private:
    QVBoxLayout *mainLayout;
    QTextBrowser *textBrowser;

    QHBoxLayout *layoutVersions;
    QLabel *labelLocalVersion;
    QLabel *labelLastVersion;

    QHBoxLayout *layoutButtons;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonExit;

    int viewerVersions[2][4]; // viewerVersions[LOCAL/LAST][VERSION]
    int version_qt_local;
    int version_qt_last;
    bool updateNeeded;

    ConfigFile *conf_file;
};

#endif // UPDATER_TAB_H
