#ifndef FONCTIONSMoebooru_H
#define FONCTIONSMoebooru_H

#include <QString>
#include <QNetworkAccessManager>
#include "generic_booru_image.h"
#include "constantes.h"
#include "../json/json.h"
#include "../Workers/caching_thread.h"
#include "../Widget/searchTabClass.h"

void chargementImagesMoebooru(BooruImage imagesAffichage[MAX_PICTURE_NUMBER], std::string searchFilePath);

int returnTagNumberMoebooru(Json::Value root);
int lectureTagsMoebooru(std::string input, std::string output[][3], Json::Value root);

#endif // FONCTIONSMoebooru_H
