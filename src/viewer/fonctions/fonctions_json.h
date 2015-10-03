#ifndef FONCTIONS_JSON_H
#define FONCTIONS_JSON_H

#include <iostream>
#include "../constantes.h"
#include "fonctions.h"

#include "fonctions_all.h"
#include "../json/json.h"

Json::Value saveAndLoad(Json::Value root, const char* file);
Json::Value loadJSONFile(const char* filePath);
void saveJSONFile(Json::Value root, const char* filePath);

#endif
