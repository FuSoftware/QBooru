#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>

#include "loadingWidget.h"
#include "../widget.h"

LoadingWidget::LoadingWidget(QString title, QString text, Widget *parent)
{
    setWindowTitle(title);
    setFixedSize(250,1);
    layoutMain = new QVBoxLayout;
    label1 = new QLabel(text,this);
    progressBar = new QProgressBar(this);

    layoutMain->addWidget(label1);
    layoutMain->addWidget(progressBar);
    setLayout(layoutMain);
}

LoadingWidget::~LoadingWidget()
{

}
