#ifndef ADDBOORUTABCLASS_H
#define ADDBOORUTABCLASS_H

#include <QtWidgets>

#include "widget.h"
#include "booruSettingsTabClass.h"

class BooruSettingsTab;

class BooruSettings : public QWidget
{
    Q_OBJECT

public:
    BooruSettings(BooruSettingsTab *parent = 0);
    ~BooruSettings();

    /*Objets publics*/
    QPushButton *saveButton;

public slots:
    void editBooru();
    void loadBooru(int index);

private:


    QSpacerItem *spacer;
    BooruSettingsTab *parentWidget;

    QVBoxLayout *layoutMain;

    QGroupBox *groupBoxMainSettings;
    QGridLayout *layoutGroupBoxMainSettings;

        QLabel *labelPreset;
        QComboBox *comboBoxPreset;
        QLabel *labelBooruName;
        QLineEdit *lineEditBooruName;
        QLabel *labelBooruURL;
        QLineEdit *lineEditBooruURL;
        QLabel *labelBooruType;
        QComboBox *comboBoxBooruType;

    QGroupBox *groupBoxOptionalSettings;
    QGridLayout *layoutGroupBoxOptionalSettings;

        QLabel *labelBooruDownloadPath;
        QLineEdit *lineEditBooruDownloadPath;

    QGroupBox *groupBoxAdvancedSettings;
    QGridLayout *layoutGroupBoxAdvancedSettings;

        QLabel *labelBooruSearchUrl;
        QLineEdit *lineEditBooruSearchUrl;

        QLabel *labelBooruShowIndexUrl;
        QLineEdit *lineEditBooruShowIndexUrl;

        QLabel *labelBooruTagsUrl;
        QLineEdit *lineEditBooruTagsUrl;

};

#endif // ADDBOORUTABCLASS_H
