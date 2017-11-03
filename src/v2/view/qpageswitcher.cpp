#include "qpageswitcher.h"

QPageSwitcher::QPageSwitcher(QWidget *parent) : QWidget(parent)
{

}

void QPageSwitcher::loadUI()
{
    this->pbNextPage = new QPushButton("->", this);
    this->pbPreviousPage = new QPushButton("<-", this);
    this->lePageNumber = new QLineEdit(this);

    this->lePageNumber->setValidator(new QIntValidator(0, 1024, this));

    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(this->pbPreviousPage);
    layout->addWidget(this->lePageNumber);
    layout->addWidget(this->pbNextPage);

    this->setLayout(layout);
}

void QPageSwitcher::setPage(int page)
{

}
