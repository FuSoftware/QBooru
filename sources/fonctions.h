#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#include <iostream>
#include <QString>
#include <QDir>
#include <QNetworkAccessManager>
#include <QLayout>
#include <QMessageBox>
#include <QWidget>
#include <QProcess>
#include <QThread>

#include "constantes.h"
#include "json/json.h"

#include "classBooruSite.h"

Json::Value saveAndLoad(Json::Value root, char* file);

Json::Value ordonnerBoorus(Json::Value root);
void runUpdaterFunction();
int msleep(unsigned long milisec);

const std::string currentDateTime();
void outputInfo(std::string type, std::string data, int level);

void checkConfigFile();
void getVersion(char* versionChar, int versionInt[3]);
Json::Value checkBoorusIntegrity(Json::Value root);
Json::Value resetBooruSites(Json::Value root);
void loadBooruSites(BooruSite sites[], int BooruIndex);

void criticalProgramError(QWidget *parent,int error);
void criticalCURLError(QWidget *parent, int error);
void criticalSDLError(QWidget *parent,char* errorCharArray);

int returnPostAgeSec(int postDate);
std::string returnTimeStringConvert(int time);

void clearLayout(QLayout *layout);
void clearLayoutSecond(QLayout *layout);

Json::Value loadJSONFile(char* filePath);
void saveJSONFile(char* filePath, std::string data);

void setAppVersionJSON();
void checkFolder(std::string path);
QString readChangelog();
int loadTags(std::string taglist, std::string tags[TAG_NUMBER]);
char *downloadPath();

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
int cachingFile(char *url, char outfilename[4096], bool output, bool check_file_presence);

char *getFileExtension(char *filename);

/*Conversion*/
std::string intToString(int i);
char* stringToCString(std::string input);

#endif // FONCTIONS_H_INCLUDED
