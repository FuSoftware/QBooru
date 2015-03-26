#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>
#include <sstream>
#include "widget.h"

#include <QString>
#include <QDir>
#include <QNetworkAccessManager>

#include "tinyxml2/tinyxml2.h"

#include "fonctions.h"
#include "gelbooru_fonctions.h"
#include "generic_booru_image.h"
#include "filedownloader.h"

int chargementImagesGelbooru(BooruImage imagesAffichage[MAX_PICTURE_NUMBER], std::string searchFilePath)
{
    /// Return 0 = No error
    /// Return 1 = Read error
    /// Return X = Error nb X
    /*Variables*/
    QString stringOutFilename;
    char* outfilename;
    int errorbuf;

    /*Création des chemins*/
    stringOutFilename = QString(searchFilePath.c_str());

    QByteArray ba2 = stringOutFilename.toLocal8Bit();

    outfilename = ba2.data();

    /*Chargement du fichier*/
    tinyxml2::XMLDocument xmlDoc;
    xmlDoc.LoadFile(outfilename);

    if(xmlDoc.ErrorID() != 0)
    {
        errorbuf = xmlDoc.ErrorID();

        QString buf = QString("Erreur ouverture fichier XML : Erreur TinyXML ") + QString::number(errorbuf);
        outputInfo("ERROR",
                   buf.toStdString(),
                   LEVEL_SEARCH);

        return errorbuf;
    }
    else
    {
        outputInfo("INFO",
                   std::string("Ouverture fichier XML : ") + std::string(outfilename),
                   LEVEL_SEARCH);
    }

    /**TinyXML**/

    /*Création d'un Handle pour la sécurité (si le noeud n'existe pas, cela évite de pointer un objet nul*/
    tinyxml2::XMLHandle hdl(&xmlDoc);

    errorbuf = lectureXMLGelbooru(hdl, imagesAffichage);

    if(errorbuf)
    {
        return errorbuf;
    }
    else
    {
        return 0;
    }

}

int lectureXMLGelbooru(tinyxml2::XMLHandle hdl, BooruImage images[MAX_PICTURE_NUMBER])
{
    int i = 0;
    tinyxml2::XMLElement *elem = hdl.FirstChildElement().FirstChildElement().ToElement();

    /*Lecture du noeud et de ses attributs*/
    if(!elem)
    {
        outputInfo("ERROR",
                   std::string("Erreur : Le noeud à atteindre n'existe pas"),
                   LEVEL_SEARCH);
        return 1000;
    }

    while(elem)
    {
        images[i].score         = atoi(elem->Attribute("score"));
        images[i].file_url      = std::string(elem->Attribute("file_url"));
        images[i].sample_url    = std::string(elem->Attribute("sample_url"));
        images[i].sample_width  = atoi(elem->Attribute("sample_width"));
        images[i].sample_height = atoi(elem->Attribute("sample_height"));
        images[i].preview_url   = std::string(elem->Attribute("preview_url"));
        images[i].rating        = *strdup(elem->Attribute("rating"));

        images[i].tagNumber     = loadTags(std::string(elem->Attribute("tags")), images[i].tags);

        images[i].id            = atoi(elem->Attribute("id"));
        images[i].height        = atoi(elem->Attribute("height"));
        images[i].width         = atoi(elem->Attribute("width"));

        images[i].author    = elem->Attribute("creator_id");

        images[i].created_at    = std::string(elem->Attribute("created_at"));
        images[i].source        = std::string(elem->Attribute("source"));         
        images[i].preview_width = atoi(elem->Attribute("preview_width"));
        images[i].preview_height = atoi(elem->Attribute("preview_height"));

        images[i].file_size = 0;

        /**
          Useless for now :
          images[i].change        = atoi(elem->Attribute("change"));
          images[i].has_children  = strdup(elem->Attribute("has_children"));
          images[i].status        = std::string(elem->Attribute("status"));
          images[i].has_notes     = strdup(elem->Attribute("has_notes"));
          images[i].has_comments  = strdup(elem->Attribute("has_comments"));
          images[i].parent_id     = atoi(elem->Attribute("parent_id"));
          */


        elem = elem->NextSiblingElement(); // iteration
        i++;
    }
    return 0;
}
