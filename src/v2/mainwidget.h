#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets>

#include "view/qboorutab.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void loadUI();

public slots:
    void loadBoorus(QVector<BooruSite*> sites);
    void addBooru(BooruSite* site);

private:
    QTabWidget *tab_widget;
    QVector<BooruSite*> loaded_sites;
};

#endif // MAINWIDGET_H
