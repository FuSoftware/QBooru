#ifndef FONCTIONSGELBOORU_H
#define FONCTIONSGELBOORU_H

#include <QString>
#include "generic_booru_image.h"
#include "constantes.h"

#include "tinyxml2/tinyxml2.h"

int chargementImagesGelbooru(BooruImage imagesAffichage[MAX_PICTURE_NUMBER], std::string searchFilePath);
int lectureXMLGelbooru(tinyxml2::XMLHandle hdl, BooruImage images[MAX_PICTURE_NUMBER]);

#endif // FONCTIONSGELBOORU_H
