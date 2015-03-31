#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>

#include "fonctions.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void runApplication();
    void runAndStopApplication();
    void updateSoftware();
    void refreshInterface();
private:
    QVBoxLayout *mainLayout;
    QTextBrowser *textBrowser;

    QHBoxLayout *layoutVersions;
    QLabel *labelLocalVersion;
    QLabel *labelLastVersion;

    QHBoxLayout *layoutButtons;
    QPushButton *pushButtonRunViewer;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonExit;

    int viewerVersions[2][4]; // viewerVersions[LOCAL/LAST][VERSION]
    bool updateNeeded;
};

#endif // WIDGET_H
