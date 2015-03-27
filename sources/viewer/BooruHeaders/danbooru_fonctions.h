#ifndef FONCTIONSDANBOORU_H
#define FONCTIONSDANBOORU_H

#include <QString>
#include <QNetworkAccessManager>
#include "generic_booru_image.h"
#include "constantes.h"
#include "../json/json.h"

void chargementImagesDanbooru(BooruImage imagesAffichage[MAX_PICTURE_NUMBER], std::string searchFilePath, std::string baseSiteIndex);

int returnTagNumberDanbooru(Json::Value root);
int lectureTagsDanbooru(std::string input, std::string output[][3], Json::Value root);

#endif // FONCTIONSDANBOORU_H
