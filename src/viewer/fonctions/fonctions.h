#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <fstream>

#include <curl/curl.h>
#include <curl/easy.h>

#include "classBooruSite.h"
#include "constantes.h"

int msleep(unsigned long milisec);

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime();
void outputInfo(int type, std::string data);

std::string returnTimeStringConvert(int time);

int returnPostAgeSec(int postDate);

int loadTags(std::string taglist, std::string tags[TAG_NUMBER]);

char *downloadPath();

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
/*Read image with cUrl*/
int cachingFile(char *url, char outfilename[4096], bool output, bool check_file_presence);

char *getFileExtension(char *filename);

bool fexists(const char *filename);

#endif

