#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <QString>
#include <QFile>

#include "recherche.h"
#include "fonctions.h"
#include "fonctionsImages.h"
#include "images.h"

int progress;

int setTags(QString recherche, QString page, QString apiKey, int checkBox, int checkBoxSafe)
{
        int operationState;
        char *url;
        char urlArray[512];
        char urlArrayCopy[512] = {};
        int i = 0;
        int j = 0;
        memset ( urlArrayCopy, 0, 512 );

        QByteArray ba1 = recherche.toLocal8Bit();
        url =  ba1.data();

        strcpy(urlArray, url);

        /*Debut de la requete de recherche*/
        if(checkBoxSafe == 0)
        {
            urlArrayCopy[j] = '?';
            j++;
            urlArrayCopy[j] = 'q';
            j++;
            urlArrayCopy[j] = '=';
            j++;
        }
        else
        {
            urlArrayCopy[j] = '?';
            j++;
            urlArrayCopy[j] = 'q';
            j++;
            urlArrayCopy[j] = '=';
            j++;
            urlArrayCopy[j] = 's';
            j++;
            urlArrayCopy[j] = 'a';
            j++;
            urlArrayCopy[j] = 'f';
            j++;
            urlArrayCopy[j] = 'e';
            j++;
            urlArrayCopy[j] = '%';
            j++;
            urlArrayCopy[j] = '2';
            j++;
            urlArrayCopy[j] = 'C';
            j++;
            urlArrayCopy[j] = '+';
        }


        if(checkBox == 2)
        {
            /*Ajout des tags*/
            for(i=0;i<ba1.size();i++)
            {
                if(urlArray[i] == ',' && urlArray[i+1] == ' ' && checkBoxSafe == 2)
                {
                        urlArrayCopy[j] = '&';
                        j++;
                        urlArrayCopy[j] = 'q';
                        j++;
                        urlArrayCopy[j] = '=';
                        j++;
                }
                else if(urlArray[i] == ' ' && urlArray[i-1] == ',')
                {

                }
                else if(urlArray[i] == ' ' && urlArray[i-1] != ',')
                {
                    urlArrayCopy[j] = '+';
                    j++;
                }
                else
                {
                    urlArrayCopy[j] = urlArray[i];
                    j++;
                }
            }
        }
        else if(checkBox == 0)
        {
            for(i=0;i<ba1.size();i++)
            {
                if(urlArray[i] == ' ')
                {
                    urlArrayCopy[j] = '+';
                    j++;
                }
                else if(urlArray[i] == ',')
                {
                    urlArrayCopy[j] = '%';
                    j++;
                    urlArrayCopy[j] = '2';
                    j++;
                    urlArrayCopy[j] = 'C';
                    j++;
                }
                else
                {
                    urlArrayCopy[j] = urlArray[i];
                    j++;
                }
            }
        }

        ba1 = page.toLocal8Bit();
        url =  ba1.data();

        /*Ajout des pages*/
        urlArrayCopy[j] = '&';
        j++;
        urlArrayCopy[j] = 'p';
        j++;
        urlArrayCopy[j] = 'a';
        j++;
        urlArrayCopy[j] = 'g';
        j++;
        urlArrayCopy[j] = 'e';
        j++;
        urlArrayCopy[j] = '=';
        j++;

        urlArray[0] = '\0';

        strcpy(urlArray, url);


        for(i=0;i<ba1.size();i++)
        {
          urlArrayCopy[j] = urlArray[i];
          j++;
        }

        /*Ajout de l'APIkey si existante*/
         urlArrayCopy[j] = '&';
         j++;
         urlArrayCopy[j] = 'k';
         j++;
         urlArrayCopy[j] = 'e';
         j++;
         urlArrayCopy[j] = 'y';
         j++;
         urlArrayCopy[j] = '=';
         j++;

         ba1 = apiKey.toLocal8Bit();
         url =  ba1.data();

         strcpy(urlArray, url);

         for(i=0;i<ba1.size();i++)
         {
              urlArrayCopy[j] = urlArray[i];
              j++;
         }

         std::cout << "Searching : " << urlArrayCopy << std::endl;

        operationState = rechercheTags(urlArrayCopy);

        return operationState;

}

int rechercheTags(char urlArray[512])
{
    /*Définition des variables*/
    char *url;
    int cacheState;
    char *outfilename;
    unsigned int i = 0;
    QString stringUrl = "";
    QString stringOutFilename = "";
    QString tagsUrl;

    for(i=0;i<512;i++)
    {
        tagsUrl += urlArray[i];
    }

    /*Création des chemins*/
    stringUrl = "https://derpibooru.org/search.json" + tagsUrl;
    stringOutFilename = QString(cachePath) + QString("search.json");

    QByteArray ba1 = stringUrl.toLocal8Bit();
    QByteArray ba2 = stringOutFilename.toLocal8Bit();

    url =  ba1.data();
    outfilename = ba2.data();

    /*Mise du json en cache*/
    //cout << "|---->" << "Caching image " << imageID << endl;
    cacheState = cachingFile(url, outfilename);
    //cout << "|---->" << "Image " << imageID << " cached successfully." << endl;

    return cacheState;
    /*Lecture du json et assignation des variables*/
}

void returnImagesTags(QString imagesID[15])
{
    int i;

    char *stringOutFilename = '\0';
    char outName[4096] = {'\0'};

    stringOutFilename = strcpy(outName, cachePath);
    stringOutFilename = strcat(outName, "search.json");

    FILE* jsonSearchFile;
    int nombre;

    jsonSearchFile = fopen(stringOutFilename,"r");

    for(i=0;i<15;i++)
    {
        nombre = 12;
        nombre = lectureVariableIntRecherche(jsonSearchFile, "id", i+1);
        imagesID[i] = QString::number(nombre);
    }

    fclose(jsonSearchFile);
}

int lectureVariableIntRecherche(FILE* fichier, QString nomVariable, int searchOffset)
{
    //std::cout << "|-->Variables : " << "Assignation " << nomVariable << std::endl;
    rewind(fichier);
    bool variableExistante;
    char lettre = 'n';
    char mot[256];
    QString comparaison;
    int nombre = 0;
    int i = 0;
    int j = 0;

    memset (mot, 0, 256);

    variableExistante = lectureNomVariable(fichier, nomVariable);

    while(j<searchOffset)
    {
        comparaison = "\0";
        while(comparaison != "\"id_number\"" && lettre != EOF)
        {
            comparaison = "\0";
            lettre = fgetc(fichier);
            if(lettre == '"')
            {
                comparaison += lettre;
                lettre = fgetc(fichier);
                if(lettre == 'i')
                {
                    do
                    {
                        comparaison += lettre;
                        lettre = fgetc(fichier);
                    }while(lettre != '"');
                }

            }
            comparaison += lettre;
        }
        j++;
    }

    i = 0;

    if(variableExistante && lettre != EOF)
    {

        lettre = fgetc(fichier);
        lettre = fgetc(fichier);

        while(lettre != ',' && lettre != EOF)
        {
            mot[i] = lettre;
            lettre = fgetc(fichier);
            i++;
        }
        nombre = atoi(mot);
        //std::cout << "|-->Variables : " << nomVariable << " = " << nombre << std::endl << std::endl;
        return nombre;
    }
    else
    {
        //std::cout << "|-->Variables : " << "Assignation " << nomVariable << " échouée."<< std::endl;
        return nombre;
    }
}
