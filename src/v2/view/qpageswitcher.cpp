#include "qpageswitcher.h"

#include "model/boorusite.h"

QPageSwitcher::QPageSwitcher(BooruSite *booru, QWidget *parent) : QWidget(parent)
{
    this->booru = booru;
    loadUI();
}

void QPageSwitcher::loadUI()
{
    this->pbNextPage = new QPushButton("->", this);
    this->pbPreviousPage = new QPushButton("<-", this);
    this->lePageNumber = new QLineEdit(this);

    this->lePageNumber->setValidator(new QIntValidator(0, 1024, this));

    this->lePageNumber->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->pbNextPage->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->pbPreviousPage->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(this->pbPreviousPage);
    layout->addWidget(this->lePageNumber);
    layout->addWidget(this->pbNextPage);

    this->setLayout(layout);

    connect(this->pbNextPage, SIGNAL(clicked(bool)), this, SLOT(setNextPage()));
    connect(this->pbPreviousPage, SIGNAL(clicked(bool)), this, SLOT(setPreviousPage()));

    connect(this->lePageNumber, SIGNAL(returnPressed()), this, SLOT(setNextPage()));

    this->page = this->booru->getAPI()->getStartPage();
    this->updatePageNumber();
}

void QPageSwitcher::setCurrentPage(int page)
{
    if(page <= this->booru->getAPI()->getStartPage())
    {
        this->page = this->booru->getAPI()->getStartPage();
    }
    else
    {
        this->page = page;
    }

    updatePageNumber();
}

void QPageSwitcher::setPage()
{
    this->page = this->lePageNumber->text().toInt();
    updatePageNumber();

    emit openPage(this->page);
}

void QPageSwitcher::setNextPage()
{
    this->page++;
    updatePageNumber();

    emit nextPage();
    emit openPage(this->page);
}

void QPageSwitcher::setPreviousPage()
{
    this->page--;
    updatePageNumber();

    emit previousPage();
    emit openPage(this->page);
}

void QPageSwitcher::updatePageNumber()
{
    int offset = 1-this->booru->getAPI()->getStartPage();
    this->lePageNumber->setText(QString::number(this->page + offset));

    if(this->page <= this->booru->getAPI()->getStartPage())
    {
        this->pbPreviousPage->setDisabled(true);
    }
    else
    {
        this->pbPreviousPage->setEnabled(true);
    }
}
