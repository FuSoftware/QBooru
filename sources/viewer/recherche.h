#include <QString>
#include "constantes.h"


#ifndef RECHERCHE_H
#define RECHERCHE_H

int setTags(QString recherche, QString page, QString apiKey, int checkBox, int checkBoxSafe);
int rechercheTags(char urlArray[512]);
void returnImagesTags(QString imagesID[12]);
int lectureVariableIntRecherche(FILE* fichier, QString nomVariable, int searchOffset);

#endif // RECHERCHE_H
