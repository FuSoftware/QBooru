/*
 * fonctions.h
 *
 * Contains all the generic functions for the program such as :
 * - Downloading
 * - Outputing formatted messages
 * - Save and Load JSON files
 *
 * Will be cut in several parts soon to separate:
 * - JSON manipulation
 * - Conversions between types
 * - Generic functions
 */

#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <ctime>
#include <string.h>
#include <fstream>
#include <sstream>

#include <curl/curl.h>
#include <curl/easy.h>

#include <QString>
#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>
#include <QLayout>
#include <QMessageBox>
#include <QWidget>
#include <QProcess>
#include <QThread>

#include "tinyxml2/tinyxml2.h"
#include "classBooruSite.h"
#include "constantes.h"
#include "json/json.h"

#include "widget.h"
#include "classBooruSite.h"

Json::Value saveAndLoad(Json::Value root, char* file);

Json::Value ordonnerBoorus(Json::Value root);
void runUpdaterFunction();
int msleep(unsigned long milisec);

const std::string currentDateTime();

void outputInfo(std::string type, std::string data, int level);//Outputs formatted text to log

void checkConfigFile();//Checks if the configuration file is valid
void getVersion(char* versionChar, int versionInt[4]);//Extracts the version from "lastVersion.json"
Json::Value checkBoorusIntegrity(Json::Value root);//Checks if the boorus are valid
Json::Value resetBooruSites(Json::Value root);//Reset the boorus to the default ones
void loadBooruSites(BooruSite sites[], int BooruIndex);//Loads an array with the Booru sites informations from configuration.json

/*Not used, should pop a QMessageBox on error*/
void criticalProgramError(QWidget *parent,int error);
void criticalCURLError(QWidget *parent, int error);
void criticalSDLError(QWidget *parent,char* errorCharArray);

int returnPostAgeSec(int postDate);//Returns the image's timestamp
std::string returnTimeStringConvert(int time);//Converts timestamp to readable text

/*Clears sub-layouts of the input layout and their objects, 2 methods here*/
void clearLayout(QLayout *layout);
void clearLayoutSecond(QLayout *layout);

Json::Value loadJSONFile(char* filePath);//Returns the JSON file's root as Json::Value
void saveJSONFile(char* filePath, std::string data);//Saves a JSON-formatted std::string to a file

void setAppVersionJSON();//Sets the current app's version into the configuration file
void checkFolder(std::string path);//Checks if the specified folder exists, and creates it if it doesn't
QString readChangelog();//Returns the CHANGELOG_FILE's content
int loadTags(std::string taglist, std::string tags[TAG_NUMBER]);//Returns an array containing all of an images's tags
char *downloadPath();//Generate a download root path in the User's folder.

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
int cachingFile(char *url, char outfilename[4096], bool output, bool check_file_presence);//Saves a specified URL as a local file. Can ouput text and can check if file already exists

char *getFileExtension(char *filename);

/*Conversion*/
std::string intToString(int i);
char* stringToCString(std::string input);

#endif // FONCTIONS_H_INCLUDED
