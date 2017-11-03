#ifndef QPAGESWITCHER_H
#define QPAGESWITCHER_H

#include <QtWidgets>

class QPageSwitcher : public QWidget
{
    Q_OBJECT
public:
    QPageSwitcher(QWidget *parent = nullptr);
    void loadUI();

signals:
    void nextPage();
    void previousPage();
    void openPage(int page);

public slots:
    void setPage(int page);

private:
    QPushButton *pbNextPage;
    QPushButton *pbPreviousPage;
    QLineEdit *lePageNumber;
};

#endif // QPAGESWITCHER_H
