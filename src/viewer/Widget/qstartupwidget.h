#ifndef QSTARTUPWIDGET_H
#define QSTARTUPWIDGET_H

#include <QtWidgets>
#include "../config_file.h"
#include "../fonctions_all.h"

#include "qdownloadwidget.h"

class QStartupWidget : public QWidget
{
    Q_OBJECT
public:
    QStartupWidget(QWidget *parent = 0);

    void loadUI();
    void process();
    int checkVersions();
    void loadConfigFile();
    ConfigFile *getCfg();

signals:
    void finished();
    void processStatus(QString status);

public slots:
    void updateStatus(QString status);

private:
    ConfigFile *cfg;

    QProgressBar *progressBar;
    QLabel *labelStatus;
};

#endif // QSTARTUPWIDGET_H
