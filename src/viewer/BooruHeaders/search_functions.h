#ifndef SEARCH_FUNCTIONS_H
#define SEARCH_FUNCTIONS_H

#include <iostream>
#include "../fonctions_all.h"

int setTagsDanbooru2(std::string recherche, std::string page, int image_count, std::string cachePath, std::string searchIndex);
int rechercheTagsDanbooru2(char *url, char* cachePath, char* searchIndex);

int setTagsDerpibooru(std::string recherche, std::string page, std::string apiKey, std::string cachePath, std::string searchIndex);
int rechercheTagsDerpibooru(std::string urlExtension, std::string cachePath, std::string searchIndex);

int setTagsGelbooru(std::string recherche, int page, int image_count, std::string searchFile, std::string fileUrl);
int rechercheTagsGelbooru(std::string urlExtension, std::string searchFile, std::string url);

int setTagsMoebooru(std::string recherche, std::string page, int image_count, std::string cachePath, std::string searchIndex);
int rechercheTagsMoebooru(std::string recherche, std::string cachePath, std::string searchIndex);

#endif // SEARCH_FUNCTIONS_H
