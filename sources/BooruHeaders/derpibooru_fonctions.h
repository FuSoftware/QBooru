#ifndef FONCTIONSDERPIBOORU_H
#define FONCTIONSDERPIBOORU_H

#include <QString>
#include <QNetworkAccessManager>
#include "generic_booru_image.h"
#include "constantes.h"

void chargementImagesDerpibooru(BooruImage imagesAffichage[MAX_PICTURE_NUMBER], std::string searchFilePath);

char* loadAPIKey();

#endif // FONCTIONSDERPIBOORU_H
