#ifndef RECHERCHE_H
#define RECHERCHE_H

#include <QString>
#include "constantes.h"

int setTagsDerpibooru(std::string recherche, std::string page, std::string apiKey, std::string cachePath, std::string searchIndex);
int rechercheTagsDerpibooru(std::string urlExtension, std::string cachePath, std::string searchIndex);

#endif // RECHERCHE_H
