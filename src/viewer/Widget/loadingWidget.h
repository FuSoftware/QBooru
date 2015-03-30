#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include "../widget.h"


class LoadingWidget : public QWidget
{
    Q_OBJECT

public:
    LoadingWidget(QString title, QString text, Widget *parent=0);
    ~LoadingWidget();

    /*Objets publics*/
    Widget *parent;
    QVBoxLayout *layoutMain;
    QLabel *label1;
    QLabel *label2;
    QProgressBar *progressBar;

public slots:


private:

};

#endif // LOADINGWIDGET_H
