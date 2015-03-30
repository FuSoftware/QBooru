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

#include "fonctions.h"
#include "fonctionsImages.h"
#include "images.h"


bool lectureNomVariable(FILE* fichier, QString variable)
{
    char lettre = 'n';
    QString mot = "";

    while(lettre != EOF)
    {
        if(variable.compare(mot) == 0)
        {
            return true;
        }

        lettre = fgetc(fichier);
        if(lettre == '"')
        {
            lettre = fgetc(fichier);
            while(lettre != '"' && lettre != EOF)
            {
                mot += lettre;
                lettre = fgetc(fichier);
            }
        }

        if (variable.compare(mot) != 0)
        {
            mot = "";
        }
    }
    return false;
}

QString lectureVariableString(FILE* fichier, QString nomVariable)
{
    rewind(fichier);
    char lettre;
    QString mot = "";
    bool variableExistante;

    variableExistante = lectureNomVariable(fichier, nomVariable);

    if(variableExistante)
    {

        while(lettre != '"')
        {
            lettre = fgetc(fichier);
        }

        lettre = fgetc(fichier);

        while(lettre != '"')
        {
            mot += lettre;
            lettre = fgetc(fichier);
        }
        return mot;
    }
    else
    {
        exit(12);
    }
}

void lectureArrayString(FILE* fichier, QString tab[], QString nomVariable)
{
    //std::cout << "|-->Variables : " << "Assignation " << nomVariable << std::endl;
    rewind(fichier);
    char lettre = 'n';
    QString mot = "";
    int i = 0;
    //bool variableExistante;

    //variableExistante = lectureNomVariable(fichier, nomVariable);

    while(lettre != '"')
    {
        if(lettre != ',' && lettre != '"')
            mot += lettre;


        lettre = fgetc(fichier);
        if(lettre == ',')
        {
            tab[i] = mot;
            i++;
        }
    }
    //std::cout << "|-->Variables : " <<"Variables " << nomVariable << " assignees"<< std::endl<< std::endl;
}

void lectureArrayString2D(FILE* fichier, QString tab[][2], QString nomVariable)
{
    //std::cout << "|-->Variables : " << "Assignation " << nomVariable << std::endl;
    rewind(fichier);
    char lettre = 'n';
    QString mot = "";
    QString test;
    int i = 0;
    int j = 0;
    bool variableExistante;

    variableExistante = lectureNomVariable(fichier, nomVariable);

    if(variableExistante)
    {
        while(lettre != '{')
        {
            lettre = fgetc(fichier);
        }

        while(lettre != '}')
        {
            while(lettre != '"')
            {
                if(lettre != ',' && lettre != '"' && lettre != ':' && lettre != '}' && lettre != '{')
                {
                    mot += lettre;
                }
                else if(lettre == ',' || lettre == '\125')
                {
                    tab[j][i] = mot;
                    test = mot;
                    mot = "";
                    j++;
                    i=0;
                }
                else if(lettre == ':')
                {
                    tab[j][i] = mot;
                    test = mot;
                    mot = "";
                    i++;
                }
                else
                {
                    lettre = fgetc(fichier);
                }
                lettre = fgetc(fichier);
            }
            lettre = fgetc(fichier);
        }
    }
    else
    {
        //std::cout << "|-->Variables : " << "Assignation " << nomVariable << " échouée."<< std::endl << std::endl;
        //exit(13);
    }

    for(j=0;j<8;j++)
    {
        for(i=0;i<2;i++)
        {
             //std::cout << "|-->Variables : " << "Representation " << j << "," << i << " : " << tab[j][i] << std::endl;
        }
    }
    tab[7][1] = mot;
    std::cout << std::endl;
}

int lectureVariableInt(FILE* fichier, QString nomVariable)
{
    //std::cout << "|-->Variables : " << "Assignation " << nomVariable << std::endl;
    rewind(fichier);
    bool variableExistante;
    char lettre = 'n';
    char mot[256];
    int nombre = 0;
    int i = 0;

    memset(mot, 0, 256);

    variableExistante = lectureNomVariable(fichier, nomVariable);

    if(variableExistante)
    {
        lettre = fgetc(fichier);
        lettre = fgetc(fichier);

        while(lettre != ',')
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

double lectureVariableDouble(FILE* fichier, QString nomVariable)
{
    //std::cout << "|-->Variables : " << "Assignation " << nomVariable << std::endl;
    rewind(fichier);
    bool variableExistante;
    char lettre = 'n';
    char mot[256];
    double nombre = 0;
    int i = 0;

    variableExistante = lectureNomVariable(fichier, nomVariable);

    if(variableExistante)
    {
        lettre = fgetc(fichier);
        lettre = fgetc(fichier);

        while(lettre != ',')
        {
            mot[i] = lettre;
            lettre = fgetc(fichier);
            i++;
        }

        nombre = atof(mot);
        //std::cout << "|-->Variables : " << nomVariable << " = " << nombre << std::endl << std::endl;
        return nombre;
    }
    else
    {
        //std::cout << "|-->Variables : " << "Assignation " << nomVariable << " échouée."<< std::endl;
        return nombre;
    }
}

bool lectureVariableBool(FILE* fichier, QString nomVariable)
{
    //std::cout << "|-->Variables : " << "Assignation " << nomVariable << std::endl;
    rewind(fichier);
    char lettre = 'n';
    char mot[256];
    bool variableExistante;
    int i = 0;

    variableExistante = lectureNomVariable(fichier, nomVariable);


    if(variableExistante)
    {
        while(lettre != ':')
        {
            lettre = fgetc(fichier);
        }

        while(lettre != 'e')
        {
            lettre = fgetc(fichier);
            mot[i] = lettre;
            i++;
        }

        if(mot[0] == 't' && mot[3] == 'e')
        {
            return true;
        }
        else if(mot[0] == 'f' && mot[4] =='e')
        {
            return false;
        }
        else
        {
            std::cout << "Valeur erronnee" << std::endl;
            return true;
        }
    }
    else
    {
        return false;
    }
}
