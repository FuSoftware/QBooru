#ifndef FONCTIONS_JSON
#define FONCTIONS_JSON

#include <iostream>
#include <fstream>

#include "fonctions.h"
#include "json/json.h"
#include "constantes.h"

void setLastVersionJSON();//Sets the last versions into the config file
void setAppVersionJSON();//Sets the current app's version into the configuration file
Json::Value saveAndLoad(Json::Value root, char* file);
Json::Value loadJSONFile(char* filePath);//Returns the JSON file's root as Json::Value
void saveJSONFile(char* filePath, std::string data);//Saves a JSON-formatted std::string to a file

#endif // FONCTIONS_JSON

