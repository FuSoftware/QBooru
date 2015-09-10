#include "fonctions_qt.h"

void checkFolder(std::string path)
{
    QDir dirCache1(path.c_str());
    if (!dirCache1.exists()) {
        dirCache1.mkpath(".");
    }
}

void runUpdaterFunction()
{
    outputInfo(L_INFO,"Running Updater");

    QString path = QString(UPDATER_MAIN_EXECUTABLE);

    QProcess *Process = new QProcess;
    Process->startDetached(path,QStringList());

    while(Process->waitForStarted(3000))

    while(Process->waitForFinished(3000))

    outputInfo(L_INFO,Process->program().toStdString() + std::string(" Running"));
    outputInfo(L_INFO,Process->errorString().toStdString());
    exit(0);
}

void criticalCURLError(QWidget *parent, int error)
{
    QString titre;
    QString errorString;

    titre = QString("cUrl error");

    errorString = QString("cUrl error : ") + QString::number(error);

    outputInfo(L_ERROR,errorString.toStdString());

    //parent->show();
    //QMessageBox::critical(parent, titre, errorString);
    //exit(error);
}

void criticalProgramError(QWidget *parent, int error)
{
    QString titre;
    QString errorString;

    titre = QString("Error : ") + QString::number(error);

    switch(error)
    {
    default:
        errorString = QString("Unknown error : ") + QString::number(error);
        break;
    case 28:
        errorString = QString("Error initializing cUrl, maybe libcurl.dll is missing ? Error ") + QString::number(error);
        break;
    }

    outputInfo(L_ERROR,errorString.toStdString());

    parent->show();
    QMessageBox::critical(parent, titre, errorString);
    exit(error);
}

void clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget())
        {
            delete item->widget();
        }
        if (QSpacerItem *SpacerItem = item->spacerItem())
        {
            delete SpacerItem;
        }
        delete item;
    }
}

void clearLayoutSecond(QLayout *layout)
{
    int i = 0;

    for (i = 0; i < layout->count(); ++i)
    {
        QLayoutItem *layoutItem = layout->itemAt(i);

        if (layoutItem->spacerItem())
        {
            if(layoutItem->isEmpty())
            {
                layout->removeItem(layoutItem);
            }
            else
            {
                layout->removeItem(layoutItem);
                delete layoutItem;
            }
            --i;
        }
        if (layoutItem->layout())
        {
            layout->removeItem(layoutItem);
            delete layoutItem;
            --i;
        }
        if (layoutItem->widget())
        {
            if(i>-1)
            {
                if(layoutItem->isEmpty())
                {
                    layout->removeItem(layoutItem);
                }
                else
                {
                    layout->removeItem(layoutItem);
                    delete layoutItem;
                }
                --i;
            }
        }
    }
}

QString readChangelog()
{
    QString changelog;
    FILE* fp;
    char lettre;
    fp = fopen(CHANGELOG_FILE, "r");

    lettre = fgetc(fp);

    while(lettre != EOF)
    {
        changelog += lettre;
        lettre = fgetc(fp);
    }

    return changelog;
}
