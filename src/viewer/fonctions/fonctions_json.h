#ifndef FONCTIONS_JSON_H
#define FONCTIONS_JSON_H

#include <iostream>
#include "../constantes.h"
#include "fonctions.h"

#include "fonctions_all.h"
#include "../json/json.h"

Json::Value saveAndLoad(Json::Value root, char* file);
Json::Value loadJSONFile(char* filePath);
void saveJSONFile(Json::Value root, char* filePath);

#endif
