#ifndef QBOORUPICTUREINFOWIDGET_H
#define QBOORUPICTUREINFOWIDGET_H

#include <QtWidgets>
#include "model/boorupicture.h"

class QBooruPictureInfoWidget : public QWidget
{
    Q_OBJECT
public:
    QBooruPictureInfoWidget(QWidget *parent = 0);
    void loadUI();

    void setLabel(int label, QString text);
    void setUploader(QString uploader);
    void setWebsite(QString website);
    void setDate(QString date);
    void setDimensions(int w, int h);
    void setFullUrl(QString url);
    void setId(int id);
    void setScore(int score);
    void setShowUrl(QString url);

    enum LABELS
    {
        LABEL_BOORU = 0,
        LABEL_SHOW_URL,
        LABEL_FULL_URL,
        LABEL_ID,
        LABEL_UPLOADER,
        LABEL_CREATION,
        LABEL_SCORE,
        LABEL_RATING,
        LABEL_DIMENSIONS,
        COUNT
    };

signals:

public slots:
    void loadPicture(BooruPicture* picture);

private:
    BooruPicture *picture = 0;
    QLabel *labels[LABELS::COUNT];
    QString titles[LABELS::COUNT];

};

#endif // QBOORUPICTUREINFOWIDGET_H
