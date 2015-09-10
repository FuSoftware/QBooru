#ifndef BOORUSETTINGSTABCLASS_H
#define BOORUSETTINGSTABCLASS_H

#include <QtWidgets>

#include "../widget.h"
#include "BooruSettingsWidgetClass.h"

class BooruSettings;

class BooruSettingsTab : public QWidget
{
    Q_OBJECT

public:
    BooruSettingsTab(Widget *parent = 0);
    ~BooruSettingsTab();

    /*Objets publics*/
    QComboBox *comboBoxBooru;
    int selectedBooru;
    ConfigFile *getConfigFile();

public slots:
    void deleteBooru();
    void refreshActiveBooru(int index);
    void loadBoorus();


private:
    ConfigFile *conf_file;

    QSpacerItem *spacer;
    Widget *parentWidget;

    QGridLayout *mainGridLayout;

    BooruSettings *editBooruWidget;

    QPushButton *pushbuttonDeleteBooru;

};

#endif // BOORUSETTINGSTABCLASS_H
