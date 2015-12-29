#include "grabberwidget.h"

#include "../widget.h"

GrabberWidget::GrabberWidget(Widget *parent) : QWidget(parent)
{
    this->cfg = parent->getConfigFile();
    mapper = new QSignalMapper(this);
    connect(mapper,SIGNAL(mapped(int)),this,SLOT(login(int)));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    //Booru selection
    QGroupBox *groupBoxBoorus = new QGroupBox("Booru selection",this);
    QVBoxLayout *layoutBoorus = new QVBoxLayout;

    for(int i=0;i<cfg->getBoorus().size();i++)
    {
        cookies.push_back(new CookieJar(QString(cfg->getBoorus().at(i)->getName().c_str())));

        QHBoxLayout *layout = new QHBoxLayout;
        checkBoxes.push_back(new QCheckBox(this));
        buttonsLogin.push_back(new QPushButton("Login",this));

        if(cfg->getBoorus().at(i)->getSiteTypeInt() != GELBOORU_TYPE)
        {
            //Don't show the button
            buttonsLogin.at(i)->hide();
        }
        else
        {
            cookies.at(i)->load();
            if(!cookies.at(i)->isEmpty())
            {
                buttonsLogin.at(i)->setText("Login OK");
            }

            connect(buttonsLogin.at(i),SIGNAL(clicked()),mapper,SLOT(map()));
        }

        layout->addWidget(checkBoxes.at(i));
        layout->addWidget(new QLabel(cfg->getBoorus().at(i)->getName().c_str()));
        layout->addWidget(buttonsLogin.at(i));


        layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        layoutBoorus->addLayout(layout);
    }
    groupBoxBoorus->setLayout(layoutBoorus);

    //Search
    QGroupBox *groupBoxSearch = new QGroupBox("Search",this);
    QVBoxLayout *layoutGBSearch = new QVBoxLayout;

    QHBoxLayout *layoutSearch = new QHBoxLayout;
    QPushButton *pushButtonSearch = new QPushButton("Grab",this);
    lineEditTags = new QLineEdit(this);

    searchRating = new QComboBox(this);
    searchRating->addItem("All");
    searchRating->addItem("Safe");
    searchRating->addItem("Questionnable");
    searchRating->addItem("Explicit");

    layoutSearch->addWidget(pushButtonSearch);
    layoutSearch->addWidget(searchRating);
    layoutSearch->addWidget(lineEditTags);

    QHBoxLayout *layoutSearch2 = new QHBoxLayout;
    lineEditLimit = new QLineEdit(this);
    lineEditLimit->setValidator( new QIntValidator(0, 500, this) );

    layoutSearch2->addWidget(new QLabel("Limit :"));
    layoutSearch2->addWidget(lineEditLimit);
    layoutSearch2->addWidget(new QLabel("results per booru"));
    layoutSearch2->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    layoutGBSearch->addLayout(layoutSearch);
    layoutGBSearch->addLayout(layoutSearch2);
    groupBoxSearch->setLayout(layoutGBSearch);

    connect(pushButtonSearch,SIGNAL(clicked()),this,SLOT(startProcess()));

    //Status
    QGroupBox *groupBoxProcess = new QGroupBox("Process",this);

    labelStatus = new QLabel("Start a grab operation",this);
    progressBar = new QProgressBar(this);

    QVBoxLayout *layoutProgress = new QVBoxLayout;

    layoutProgress->addWidget(progressBar);
    layoutProgress->addWidget(labelStatus);
    groupBoxProcess->setLayout(layoutProgress);

    //Other operations

    mainLayout->addWidget(groupBoxBoorus);
    mainLayout->addWidget(groupBoxSearch);
    mainLayout->addWidget(groupBoxProcess);

    mainLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    setLayout(mainLayout);
}

void GrabberWidget::updateProgress(int progress, int total)
{
    progressBar->setMaximum(total);
    progressBar->setValue(progress);
}

void GrabberWidget::updateStatus(QString status)
{
    labelStatus->setText(status);
}

void GrabberWidget::login(int booru_index)
{
    /*Login test*/

    BooruSite *booru = cfg->getBoorus().at(booru_index);

    QString user = QInputDialog::getText(this, "UserID", "Please input your Username (needed to log in to Gelbooru)", QLineEdit::Normal, QString());
    QString pass = QInputDialog::getText(this, "Pass", "Please input your Password (needed to log in to Gelbooru)", QLineEdit::Normal, QString());

    QList<QNetworkCookie> cookie = getLoginCookie("http://gelbooru.com/index.php?page=account&s=login&code=00",user,pass);

    cookies.at(booru_index)->setCookiesFromUrl(cookie,QString(booru->getBaseUrl().c_str()));

    if(cookies.at(booru_index)->isEmpty())
    {
        QMessageBox::warning(this,"Warning","Login cookies could not be retrieved. Please check your username/password");
    }
    else
    {
        grabber->setCookie(booru_index, cookies.at(booru_index));
        qDebug() << "Loaded" << QString(booru->getName().c_str()) << "cookie" << cookies.at(booru_index)->getAllCookies();
        buttonsLogin.at(booru_index)->setText("Login OK");
    }
}

void GrabberWidget::startProcess()
{
    std::vector<BooruSite*> boorus;
    std::vector<CookieJar*> cookies;

    int limit = lineEditLimit->text().toInt();

    for(int i=0;i<cfg->getBoorus().size();i++)
    {
        if(checkBoxes.at(i)->isChecked())
        {
            boorus.push_back(cfg->getBoorus().at(i));
            cookies.push_back(this->cookies.at(i));
        }
    }

    QThread* thread = new QThread(this);
    grabber = new ImageGrabber(boorus,cookies,lineEditTags->text().toStdString(),searchRating->currentIndex(),limit,this);

    grabber->moveToThread(thread);

    connect(thread, SIGNAL(started()), grabber, SLOT(search()));
    connect(grabber,SIGNAL(search_completed()),grabber,SLOT(dump()));
    connect(grabber, SIGNAL(finished()), thread, SLOT(quit()));
    connect(grabber, SIGNAL(finished()), grabber, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(grabber, SIGNAL(status(QString)), this, SLOT(updateStatus(QString)));
    connect(grabber, SIGNAL(progress(int,int)), this, SLOT(updateProgress(int,int)));

    thread->start();
}

