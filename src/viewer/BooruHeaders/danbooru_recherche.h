#ifndef RECHERCHEDANBOORU_H
#define RECHERCHEDANBOORU_H

#include "constantes.h"

int setTagsDanbooru(std::string recherche, std::string page, int image_count, std::string cachePath, std::string searchIndex);
int rechercheTagsDanbooru(char *url, char* cachePath, char* searchIndex);

#endif // RECHERCHEDANBOORU_H
