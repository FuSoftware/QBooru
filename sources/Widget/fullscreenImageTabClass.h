#ifndef FULLSCREENIMAGETABCLASS_H
#define FULLSCREENIMAGETABCLASS_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QScrollArea>

class FullScreenImageTab : public QWidget
{
    Q_OBJECT

    public:
    FullScreenImageTab(QWidget *parent = 0, QString imagePath = "");
    ~FullScreenImageTab();

    private:
    QScrollArea *scrollAreaTags;
    QLabel *image;

};

#endif // FULLSCREENIMAGETABCLASS_H
