#ifndef GRABBERWIDGET_H
#define GRABBERWIDGET_H

#include <QtWidgets>

#include "../Workers/imagegrabber.h"
#include "../Workers/cookiejar.h"
#include "../config_file.h"

class Widget;

class GrabberWidget : public QWidget
{
    Q_OBJECT
public:
    GrabberWidget(Widget *parent = 0);

signals:

public slots:
    void updateProgress(int progress, int total);
    void updateStatus(QString status);
    void login(int booru_index);
    void startProcess();

private:
    QSignalMapper *mapper;

    ImageGrabber* grabber;
    ConfigFile *cfg;

    QList<QCheckBox*> checkBoxes;
    QList<QPushButton*> buttonsLogin;

    std::vector<CookieJar*> cookies;

    QLabel *labelStatus;
    QProgressBar *progressBar;
    QLineEdit *lineEditTags;
    QComboBox *searchRating;
    QLineEdit *lineEditLimit;


};

#endif // GRABBERWIDGET_H
