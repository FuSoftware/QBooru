#ifndef RECHERCHEDANBOORU_H
#define RECHERCHEDANBOORU_H

#include "constantes.h"

int setTagsDanbooru2(std::string recherche, std::string page, int image_count, std::string cachePath, std::string searchIndex);
int rechercheTagsDanbooru2(char *url, char* cachePath, char* searchIndex);

#endif // RECHERCHEDANBOORU2_H
