#ifndef FONCTIONS_CONFIG_H
#define FONCTIONS_CONFIG_H

#include <iostream>
#include "../constantes.h"

#include "fonctions_all.h"

void checkConfigFile();
void getVersion(char* versionChar, int versionInt[4]);
Json::Value checkBoorusIntegrity(Json::Value root);
void resetBooruSites(Json::Value root);
void loadBooruSites(BooruSite sites[], int BooruIndex);
Json::Value ordonnerBoorus(Json::Value root);
void setAppVersionJSON();

#endif
