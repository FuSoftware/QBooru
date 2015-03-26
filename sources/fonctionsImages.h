#include <QString>

#ifndef FONCTIONSIMAGES_H
#define FONCTIONSIMAGES_H

bool lectureNomVariable(FILE* fichier, QString variable);
QString lectureVariableString(FILE* fichier, QString nomVariable);
void lectureArrayString(FILE* fichier, QString tab[], QString nomVariable);
void lectureArrayString2D(FILE* fichier, QString tab[][2], QString nomVariable);
int lectureVariableInt(FILE* fichier, QString nomVariable);
bool lectureVariableBool(FILE* fichier, QString nomVariable);
double lectureVariableDouble(FILE* fichier, QString nomVariable);

#endif // FONCTIONSIMAGES_H
