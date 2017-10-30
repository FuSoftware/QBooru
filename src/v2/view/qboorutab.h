#ifndef QBOORUTAB_H
#define QBOORUTAB_H

#include <QtWidgets>
#include "qsearchwidget.h"
#include "qmaingrid.h"

class QBooruTab : public QWidget
{
    Q_OBJECT
public:
    QBooruTab(BooruSite *site, QWidget *parent = nullptr);
    void loadUI();
    BooruSite* getBooru();

signals:
    void pictureClicked(BooruPicture *picture);

public slots:

private:
    QSearchWidget *search_widget = 0;
    QMainGrid *main_grid = 0;
    BooruSite *site = 0;

};

#endif // QBOORUTAB_H
