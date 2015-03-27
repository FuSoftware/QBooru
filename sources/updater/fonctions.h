#ifndef FONCTIONS
#define FONCTIONS

#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <curl/easy.h>

#include <QString>
#include <QDir>


void runViewer();
int msleep(unsigned long milisec);

const std::string currentDateTime();

void outputInfo(std::string type, std::string data, int level);//Outputs formatted text to log

void getVersion(const char* versionChar, int versionInt[3]);//Extracts the version from "lastVersion.json"

void checkFolder(std::string path);//Checks if the specified folder exists, and creates it if it doesn't
QString readChangelog();//Returns the CHANGELOG_FILE's content

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
int cachingFile(char *url, char outfilename[4096], bool output, bool check_file_presence);//Saves a specified URL as a local file. Can ouput text and can check if file already exists

char *getFileExtension(char *filename);

/*Conversion*/
std::string intToString(int i);
char* stringToCString(std::string input);

#endif // FONCTIONS

