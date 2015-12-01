#ifndef ADDBOORUTABCLASS_H
#define ADDBOORUTABCLASS_H

#include <QtWidgets>

#include "widget.h"
#include "booruSettingsTabClass.h"

enum Lines{
    L_NAME =0,
    L_URL,
    L_DOWNLOAD,
    L_SEARCH,
    L_SHOW,
    L_TAGS,
    L_SIZE
};

const QString label_strings[L_SIZE] = {"Name","Main URL","Download Path","Seach URL", "Show URL", "Tags URL"};

class BooruSettingsTab;

class BooruSettings : public QWidget
{
    Q_OBJECT

public:
    BooruSettings(BooruSettingsTab *parent = 0);
    ~BooruSettings();

    QList<QWidget*> generateInputs();

    /*Objets publics*/
    QPushButton *saveButton;

public slots:
    void editBooru();
    void loadBooru(int index);
    void loadPreset(int index);

private:

    ConfigFile *conf_file;
    QSpacerItem *spacer;
    BooruSettingsTab *parentWidget;

    QList<QLineEdit*> lineEdits;

    QVBoxLayout *layoutMain;

    QGroupBox *groupBoxMainSettings;
    QVBoxLayout *layoutGroupBoxMainSettings;

        QCheckBox *checkBoxPreset;
        QComboBox *comboBoxPreset;
        QLabel *labelBooruType;
        QComboBox *comboBoxBooruType;

    QGroupBox *groupBoxOptionalSettings;
    QVBoxLayout *layoutGroupBoxOptionalSettings;


    QGroupBox *groupBoxAdvancedSettings;
    QVBoxLayout *layoutGroupBoxAdvancedSettings;

};

#endif // ADDBOORUTABCLASS_H
