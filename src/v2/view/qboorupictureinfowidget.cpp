#include "qboorupictureinfowidget.h"

#include "model/boorupicture.h"

QBooruPictureInfoWidget::QBooruPictureInfoWidget(QWidget *parent) : QWidget(parent)
{
    loadUI();
}

void QBooruPictureInfoWidget::loadUI()
{
    //Labels
    this->titles[LABELS::LABEL_UPLOADER] = "Uploader";
    this->titles[LABELS::LABEL_BOORU] = "Website";
    this->titles[LABELS::LABEL_CREATION] = "Created on";
    this->titles[LABELS::LABEL_DIMENSIONS] = "Dimensions";
    this->titles[LABELS::LABEL_FULL_URL] = "Picture URL";
    this->titles[LABELS::LABEL_ID] = "ID";
    this->titles[LABELS::LABEL_RATING] = "Rating";
    this->titles[LABELS::LABEL_SCORE] = "Score";
    this->titles[LABELS::LABEL_SHOW_URL] = "Website URL";

    //UI
    QVBoxLayout *bLayout = new QVBoxLayout();
    QGroupBox *b = new QGroupBox("Information", this);
    b->setLayout(bLayout);

    for(int i=0;i<LABELS::COUNT;i++)
    {
        this->labels[i] = new QLabel(this->titles[i], this);
        this->labels[i]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        bLayout->addWidget(this->labels[i]);
    }

    b->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    this->labels[LABEL_SHOW_URL]->setOpenExternalLinks(true);
    this->labels[LABEL_FULL_URL]->setOpenExternalLinks(true);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(b);
    this->setLayout(layout);
}

void QBooruPictureInfoWidget::loadPicture(BooruPicture* picture)
{
    setWebsite(QString::fromStdString(picture->getWebsite()->getName()));
    setUploader(QString::fromStdString(picture->getAuthor()));
    setDimensions(picture->getW(), picture->getH());
    setDate(QString::fromStdString(picture->getCreationDate()));
    setFullUrl(QString::fromStdString(picture->getURL(PictureType::FULL)));
    setId(picture->getID());
    setScore(picture->getScore());
    setShowUrl(QString::fromStdString(picture->getShowUrl()));

    this->picture = picture;
}

void QBooruPictureInfoWidget::setLabel(int label, QString text)
{
    this->labels[label]->setText(this->titles[label] + " : " + text);
}

void QBooruPictureInfoWidget::setUploader(QString uploader)
{
    setLabel(LABELS::LABEL_UPLOADER, uploader);
}

void QBooruPictureInfoWidget::setWebsite(QString website)
{
    setLabel(LABELS::LABEL_BOORU, website);
}

void QBooruPictureInfoWidget::setDate(QString date)
{
    setLabel(LABELS::LABEL_CREATION, date);
}

void QBooruPictureInfoWidget::setDimensions(int w, int h)
{
    QString s = QString::number(w) + "x" + QString::number(h);
    setLabel(LABELS::LABEL_DIMENSIONS, s);
}

void QBooruPictureInfoWidget::setFullUrl(QString url)
{
    QString html = QString("<a href=\"") + url + QString("\">Link</a>");
    setLabel(LABELS::LABEL_FULL_URL, html);
}

void QBooruPictureInfoWidget::setId(int id)
{
    setLabel(LABELS::LABEL_ID, QString::number(id));
}

void QBooruPictureInfoWidget::setScore(int score)
{
    setLabel(LABELS::LABEL_SCORE, QString::number(score));
}

void QBooruPictureInfoWidget::setShowUrl(QString url)
{
    QString html = QString("<a href=\"") + url + QString("\">Link</a>");
    setLabel(LABELS::LABEL_SHOW_URL, html);
}
