#ifndef OPTIONTABCLASS_H
#define OPTIONTABCLASS_H

#define LAYOUT_NUMBER_OPTIONS 8 //Number of layouts in Options tab

#include <QtWidgets>

#include "../widget.h"

class Widget;

class OptionTab : public QWidget
{
    Q_OBJECT

public:
    OptionTab(Widget *parent = 0);
    ~OptionTab();

    void refreshTagTime();

public slots:
    void refreshCacheSize();
    void deleteCache();    
    void refreshTagLists();
    void runUpdater();
    void resetBoorusSettings();
    void resetBooruDownloadPath();
    void saveOptions();

private:

    ConfigFile *conf_file;

    QHBoxLayout *horizontalLayouts[LAYOUT_NUMBER_OPTIONS];

    QSpacerItem *spacer;
    Widget *parentWidget;

    QGroupBox *groupBoxSearchSettings;
    QVBoxLayout *layoutGroupBoxSearchSettings;

    QVBoxLayout *layoutMain;
        QLabel *credits;

            QPushButton *pushButtonUpdater;

        QGroupBox *groupBox;
        QVBoxLayout *layoutGroupBox;
        QGroupBox *groupBoxCredits;

                QPushButton *pushButtonCache;
                QPushButton *pushButtonReset;
                QLabel *labelCache;

                QPushButton *pushButtonTags;
                QLabel *labelTags;

                QPushButton *pushButtonResetAllDownloadPath;
                QLineEdit *lineEditDownloadPath;

            QCheckBox *checkBoxLoadingStartup;
            QLabel *labelDefaultRating;
            QComboBox *searchRating;
            QLabel *labelDefaultBooru;
            QComboBox *defaultBooru;
            QPushButton *pushButtonRefreshCacheSize;


            QHBoxLayout *layoutImages[2];
            QLabel *labelQuadrillageImages[2];
            QComboBox *nbImages[2];

        QTextBrowser *textBrowserChangelog;

        QPushButton *pushButtonSave;

    int imageHost;

};

#endif // OPTIONTABCLASS_H
