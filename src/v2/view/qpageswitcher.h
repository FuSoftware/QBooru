#ifndef QPAGESWITCHER_H
#define QPAGESWITCHER_H

#include <QtWidgets>

class BooruSite;

#define PAGE_OFFSET 0

class QPageSwitcher : public QWidget
{
    Q_OBJECT
public:
    QPageSwitcher(BooruSite *booru, QWidget *parent = nullptr);
    void loadUI();

signals:
    void nextPage();
    void previousPage();
    void openPage(int page);

public slots:
    void setCurrentPage(int page);

private slots:
    void updatePageNumber();
    void setPage();
    void setNextPage();
    void setPreviousPage();

private:    
    QPushButton *pbNextPage = 0;
    QPushButton *pbPreviousPage = 0;
    QLineEdit *lePageNumber = 0;

    BooruSite *booru = 0;

    int page = 1;
};

#endif // QPAGESWITCHER_H
