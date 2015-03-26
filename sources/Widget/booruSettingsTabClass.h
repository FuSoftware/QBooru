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

public slots:
    void deleteBooru();
    void refreshActiveBooru(int index);


private:

    QSpacerItem *spacer;
    Widget *parentWidget;

    QGridLayout *mainGridLayout;

    BooruSettings *addBooruWidget;
    BooruSettings *editBooruWidget;

    QPushButton *pushbuttonDeleteBooru;

};

#endif // BOORUSETTINGSTABCLASS_H
