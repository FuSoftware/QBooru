#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void initialize();
private:
};

#endif // MAINWIDGET_H
