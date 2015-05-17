/*
 * widget.h
 *
 * Contains the main Widget class.
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <iostream>

#include <QtWidgets>
#include <qtconcurrentrun.h>
#include <QThread>

#include "BooruHeaders/headers.h"

#include "Widget/imageTabClass.h"
#include "Widget/optionTabClass.h"
#include "Widget/searchTabClass.h"
#include "Widget/viewerTabClass.h"
#include "Widget/booruSettingsTabClass.h"

#include "classBooruSite.h"
#include "fonctions_all.h"
#include "fileutils.h"

class SearchTab;
class ViewerTab;
class OptionTab;
class BooruSettingsTab;
class LoadingWidget;


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setupHosts(BooruSite boorus[], int index);
    void loadTag(QString tag, int imageHostInt);
    void setTab(int tab);

    /*Public Objects*/
    int booruNumber;
    int viewerIndex;

    ViewerTab *viewerTab;
    SearchTab *searchtabs[16];
    QLabel *loadingLabel;

public slots:
    void on_tab_changed(int tabIndex);
    void refresh();

private:
    QVBoxLayout *mainLayout; 
    OptionTab *optionTab;
    QTabWidget *tabWidgetMain;
    BooruSettingsTab *settingTabs;

    QString hostNames[16];

    QThread *thread[16];
};

#endif // WIDGET_H
