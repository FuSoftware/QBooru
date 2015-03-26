#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <QString>
#include <QFile>

#include "fonctions.h"
#include "fonctionsImages.h"
#include "images.h"


void Image::Refresh(QString imageID)
{
    /*Définition des variables*/
    char *url;
    char *outfilename;
    QString stringUrl = "";
    QString stringOutFilename = "";


    /*Création des chemins*/
    stringUrl = "https://derpibooru.org/" + imageID +".json";
    stringOutFilename = cachePath + imageID + ".json";

    QByteArray ba1 = stringUrl.toLocal8Bit();
    QByteArray ba2 = stringOutFilename.toLocal8Bit();

    url =  ba1.data();
    outfilename = ba2.data();

    /*Vérification existence fichier*/
    QFile Fout(stringOutFilename);

    if(url == "https://derpibooru.org/0.json")
    {

    }
    else
    {
        if(Fout.exists())
            {
                std::cout << "File : " << outfilename << " exists." << std::endl;
            }
            else
            {
                if(url == "https://derpibooru.org/0.json")
                {
                    std::cout << "File : " << outfilename  << "empty" << std::endl;
                }
                else
                {
                    std::cout << "Caching file : " << outfilename  << std::endl;
                    /*Mise du json en cache*/
                    //cout << "|---->" << "Caching image " << imageID << endl;
                    connectionState = cachingFile(url, outfilename);
                    //cout << "|---->" << "Image " << imageID << " cached successfully." << endl;
               }
            }

            /*Lecture du json et assignation des variables*/
            EcritureVariables(outfilename);
    }

}

void Image::EcritureVariables(char outfilename[FILENAME_MAX])
{
    FILE* jsonFile = NULL;

   // std::cout << "|--->" << "Opening file " << std::endl;
    jsonFile = fopen(outfilename, "r");

        //std::cout << "|--->" << "Assignation des variables" << std::endl;
        id               = lectureVariableString(jsonFile, "id");
        id_number        = lectureVariableInt(jsonFile, "id_number");
        created_at       = lectureVariableString(jsonFile, "created_at");
        updated_at       = lectureVariableString(jsonFile, "updated_at");
        duplicate_reports = lectureVariableString(jsonFile, "duplicate_reports");
        file_name        = lectureVariableString(jsonFile, "file_name");
        description      = lectureVariableString(jsonFile, "description");
        uploader         = lectureVariableString(jsonFile, "uploader");
        image            = lectureVariableString(jsonFile, "image");
        score         = lectureVariableInt(jsonFile, "score");
        upvotes       = lectureVariableInt(jsonFile, "upvotes");
        downvotes     = lectureVariableInt(jsonFile, "downvotes");
        comment_count = lectureVariableInt(jsonFile, "comment_count");
        lectureArrayString(jsonFile, tags, "tags");
        lectureArrayString(jsonFile, tag_ids, "tag_ids");
        width  = lectureVariableInt(jsonFile, "width");
        height = lectureVariableInt(jsonFile, "height");
        aspect_ratio = lectureVariableDouble(jsonFile, "aspect_ratio");
        original_format = lectureVariableString(jsonFile, "original_format");
        mime_type       = lectureVariableString(jsonFile, "mime_type");
        //char sha512_hash[512];
        //char orig_sha512_hash[512];
        source_url              = lectureVariableString(jsonFile, "source_url");
        license                 = lectureVariableString(jsonFile, "license");
        //lectureArrayString(jsonFile, comments, "comments");
        lectureArrayString(jsonFile, favourited_by_users, "favourited_by_users");
        lectureArrayString2D(jsonFile, representations, "representations");
        is_rendered             = lectureVariableBool(jsonFile, "is_rendered");
        is_optimized            = lectureVariableBool(jsonFile, "is_optimized");
        //std::cout << "|--->" << "Variables assignees " << std::endl;

    fclose(jsonFile);
    //std::cout << "|--->" << "File closed " << std::endl;

    std::cout << upvotes << std::endl;
    std::cout << downvotes << std::endl;
}
