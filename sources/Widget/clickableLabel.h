#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <iostream>
#include <QLabel>

class ClickableLabel : public QLabel
{

Q_OBJECT

public:
    explicit ClickableLabel( const QString& text ="", QWidget * parent = 0 );
    ~ClickableLabel();

signals:
    void clicked();

protected:
    void mousePressEvent ( QMouseEvent * event ) ;
};

#endif // CLICKABLELABEL_H
