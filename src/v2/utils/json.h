#ifndef JSON_H
#define JSON_H

#include <iostream>
#include <fstream>

#include "../json/json.h"
#include "output.h"

Json::Value saveAndLoad(Json::Value root, const char* file);
Json::Value loadJSONString(std::string str);
Json::Value loadJSONFile(const char* filePath);
void saveJSONFile(Json::Value root, const char* filePath);


#endif // JSON_H
