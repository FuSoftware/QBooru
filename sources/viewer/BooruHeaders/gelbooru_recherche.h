#ifndef RECHERCHEGELBOORU_H
#define RECHERCHEGELBOORU_H

#include "constantes.h"

int setTagsGelbooru(std::string recherche, int page, int image_count, std::string searchFile, std::string fileUrl);
int rechercheTagsGelbooru(std::string urlExtension, std::string searchFile, std::string url);

#endif // RECHERCHEGELBOORU_H
