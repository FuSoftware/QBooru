#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <fstream>

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

char *getFileExtension(char *filename);

bool fexists(const char *filename);

#endif

