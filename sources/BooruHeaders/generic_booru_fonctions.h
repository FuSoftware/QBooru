#ifndef GENERIC_BOORU_FONCTIONS_H
#define GENERIC_BOORU_FONCTIONS_H

#include <QString>

#include "generic_booru_image.h"
#include "constantes.h"
#include "../json/json.h"
#include "../Workers/caching_thread.h"
#include "../Widget/searchTabClass.h"

QString cacheImageGeneric(BooruImage imageCache, std::string cachePath);

QString cacheImageMediumGeneric(BooruImage imageCache, std::string cachePath, bool keepCache);
QString saveImageFullGeneric(BooruImage imageCache, std::string downloadPath);

#endif // GENERIC_BOORU_FONCTIONS_H
