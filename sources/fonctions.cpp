#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <cstring>
#include <ctime>
#include <string.h>
#include <fstream>
#include <sstream>
#include "widget.h"

#include <QFile>

#include "tinyxml2/tinyxml2.h"

#include "fonctions.h"
#include "filedownloader.h"
#include "classBooruSite.h"

Json::Value saveAndLoad(Json::Value root, char* file)
{
    Json::StyledWriter writer;
    saveJSONFile(file, writer.write(root));
    root = loadJSONFile(file);
    return root;
}

Json::Value ordonnerBoorus(Json::Value root)
{
    Json::StyledWriter writer;
    int nombre_boorus = root["settings"]["booru_number"].asInt();
    int i,j;
    int max_temp;
    int max = nombre_boorus - 1;

    for(j=0;j<nombre_boorus - 1;j++)
    {
            for(i=0;i<nombre_boorus - 1;i++)
            {
                if(root["boorus"][i]["index"].asInt() > root["boorus"][i+1]["index"].asInt())
                {
                    root["temp"] = root["boorus"][i];
                    root["boorus"][i] = root["boorus"][i+1];
                    root["boorus"][i+1] = root["temp"];
                }
            }
    }

    root["temp"] = Json::nullValue;

    return root;
}

void runUpdaterFunction()
{
    outputInfo("INFO","Running Updater",LEVEL_UPDATER);

    QString path = QString(UPDATER_MAIN_EXECUTABLE);

    QProcess *Process = new QProcess;
    Process->startDetached(path,QStringList());

    while(Process->waitForStarted(3000))

    while(Process->waitForFinished(3000))

    outputInfo("INFO",Process->program().toStdString() + std::string(" Running"),LEVEL_UPDATER);
    outputInfo("INFO",Process->errorString().toStdString(),LEVEL_UPDATER);
    exit(0);
}

int msleep(unsigned long milisec)
{
    struct timespec req={0};
    time_t sec=(int)(milisec/1000);
    milisec=milisec-(sec*1000);
    req.tv_sec=sec;
    req.tv_nsec=milisec*1000000L;
    while(nanosleep(&req,&req)==-1)
        continue;
    return 1;
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d | %X", &tstruct);

    return buf;
}

void outputInfo(std::string type, std::string data, int level)
{
    std::cout << "[" << type << "]"
              << "[" << currentDateTime() << "]"
              << "|";

    for(int i=0;i<level;i++)
    {
        std::cout <<"-";
    }

    std::cout << "> " << data << std::endl;
}

void checkConfigFile()
{
    int errorbuf;
    int lastVersion[3];
    int localVersion[3];
    bool newVersion = false;
    Json::Value root = loadJSONFile(CONF_FILE);
    Json::StyledWriter writer;


    errorbuf = cachingFile(LAST_VERSION_FILE_URL, LAST_VERSION_FILE, false, false);

    Json::Value rootVersions = loadJSONFile(LAST_VERSION_FILE);

    if(errorbuf == 0)
    {
        outputInfo("INFO",std::string("Last versions cached"),LEVEL_TOP_WIDGET);
    }
    else
    {
        std::stringstream ss;
        ss << errorbuf;
        outputInfo("ERROR",std::string("Error ") + ss.str(),LEVEL_TOP_WIDGET);
    }

    root["versions"]["updater"]["last"] = rootVersions["updater"].asCString();
    root["versions"]["viewer"]["last"] = rootVersions["viewer"].asCString();

    /*Vérification des versions*/
    getVersion(strdup(root["versions"]["viewer"]["local"].asCString()),localVersion);
    getVersion(strdup(root["versions"]["viewer"]["last"].asCString()),lastVersion);

    for(int i=0;i<3;i++)
    {
        if(lastVersion[i] > localVersion[i])
        {
            newVersion = true;
        }
    }

    if(newVersion)
    {
        int reponse = QMessageBox::question(0, "Update", "A new update is available : " + QString(root["versions"]["viewer"]["last"].asCString()) + ". Do you want to update ?", QMessageBox ::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes)
        {
            runUpdaterFunction();
        }
        else if (reponse == QMessageBox::No)
        {
        }
    }
    else
    {
        outputInfo("INFO",std::string("You have the latest version"),LEVEL_TOP_WIDGET);
    }


    /*Vérification des variables de configuration*/

    if(root["settings"]["preferred_rating"].asInt() >= 4) root["settings"]["preferred_rating"] = 0;
    root = saveAndLoad(root,CONF_FILE);

    if(root["paths"]["default_download_path"] == Json::nullValue) root["paths"]["default_download_path"] == downloadPath();
    root = saveAndLoad(root,CONF_FILE);

    if(root["settings"]["load_on_startup"] == Json::nullValue) root["settings"]["load_on_startup"] = false;
    root = saveAndLoad(root,CONF_FILE);

    if(root["settings"]["window_w"].asInt() < 1024 || root["settings"]["window_w"] == Json::nullValue) root["settings"]["window_w"] = 1024;
    root = saveAndLoad(root,CONF_FILE);

    if(root["settings"]["window_h"].asInt() < 768 || root["settings"]["window_w"] == Json::nullValue) root["settings"]["window_h"] = 768;
    root = saveAndLoad(root,CONF_FILE);

    if(root["settings"]["picture_rows"].asInt() < 3 || root["settings"]["picture_rows"].asInt() > 7) root["settings"]["picture_rows"] = 3;
    root = saveAndLoad(root,CONF_FILE);
    if(root["settings"]["picture_columns"].asInt() < 5 || root["settings"]["picture_columns"].asInt() > 9) root["settings"]["picture_rows"] = 5;
    root = saveAndLoad(root,CONF_FILE);

    outputInfo("INFO",std::string("Initial variables checked"),LEVEL_TOP_WIDGET);

    root = checkBoorusIntegrity(root); //Boorus + booru_number
    root = saveAndLoad(root,CONF_FILE);

    outputInfo("INFO",std::string("Boorus checked"),LEVEL_TOP_WIDGET);

    root["settings"]["picture_number"] = root["settings"]["picture_columns"].asInt()*root["settings"]["picture_rows"].asInt();

    if(root["settings"]["preferred_booru"].asInt() >= root["settings"]["booru_number"].asInt()) root["settings"]["preferred_booru"] = 0;

    saveJSONFile(CONF_FILE, writer.write(root));
}

void getVersion(char* versionChar, int versionInt[3])
{
    unsigned int i = 0;
    int j = 0;
    char lettre;
    std::string mot = "";

    for(i=0;i<strlen(versionChar);i++)
    {
        lettre = *(versionChar+i);

        if(lettre == '.')
        {
            versionInt[j] = atoi(mot.c_str());
            j++;
            mot = "";
        }
        else
        {
            mot += lettre;
        }
    }
    versionInt[j] = atoi(mot.c_str());
    j++;
    mot = "";
}

Json::Value checkBoorusIntegrity(Json::Value root)
{
    int booruNumber = 0;
    int j = 0;
    int i = 0;
    int indexArray[MAX_BOORU_NUMBER];

    outputInfo("INFO",std::string("Rearranging boorus in config file"),LEVEL_TOP_WIDGET);

    do
    {
        if(root["boorus"][i].isObject())
        {
            indexArray[j] = root["boorus"][i]["index"].asInt();
            j++;
            i++;
            booruNumber++;
        }
        else if(root["boorus"][i].isNull() && !root["boorus"][i+1].isNull())
        {
            root["boorus"][i] = root["boorus"][i+1];
            root["boorus"][i+1] = Json::nullValue;
        }
        else
        {
            root["boorus"][i] = 0;
        }

    }while(root["boorus"][i].isObject() == 1 || root["boorus"][i].isNull() == 1);

    root["settings"]["booru_number"] = booruNumber;

    root = ordonnerBoorus(root);

    outputInfo("INFO",std::string("Boorus now set up"),LEVEL_TOP_WIDGET);

    if(root["settings"]["booru_number"].asInt() < 1)
    {
        root = resetBooruSites(root);
        outputInfo("INFO",std::string("Boorus Reset"),LEVEL_TOP_WIDGET);
    }

    return root;
}

Json::Value resetBooruSites(Json::Value root)
{
    Json::StyledWriter writer;
    root["boorus"].clear();
    root["settings"]["booru_number"] = 4;
    std::string output = writer.write(root);
    saveJSONFile(CONF_FILE, output);

    BooruSite Gelbooru("Gelbooru","http://gelbooru.com",GELBOORU_TYPE,1);
    Gelbooru.saveBooruSite();

    BooruSite Yandere("Yandere","http://yande.re",MOEBOORU_TYPE,2);
    Yandere.saveBooruSite();

    BooruSite Konachan("Konachan","http://konachan.com",MOEBOORU_TYPE,3);
    Konachan.saveBooruSite();

    BooruSite Danbooru("Danbooru", "http://danbooru.donmai.us", DANBOORU_TYPE,4);
    Danbooru.saveBooruSite();
}

void loadBooruSites(BooruSite sites[], int BooruIndex)
{
    Json::Value root = loadJSONFile(CONF_FILE);
    int i = 0;
    while(i < BooruIndex)
    {
        sites[i].name = root["boorus"][i]["name"].asString();
        outputInfo("INFO",
                   std::string("Loading ") + sites[i].name,
                   LEVEL_TOP_WIDGET);

        sites[i].site_type_string = root["boorus"][i]["site_type_string"].asString();

        sites[i].base_url = root["boorus"][i]["base_url"].asString();
        sites[i].search_url = root["boorus"][i]["search_url"].asString();
        sites[i].tag_url = root["boorus"][i]["tag_url"].asString();

        sites[i].cache_path = root["boorus"][i]["cache_path"].asString();
        sites[i].download_path = root["boorus"][i]["download_path"].asString();
        sites[i].search_file_path = root["boorus"][i]["search_file_path"].asString();
        sites[i].tag_file_path = root["boorus"][i]["tag_file_path"].asString();

        sites[i].siteTypeInt = root["boorus"][i]["siteTypeInt"].asInt();

        sites[i].show_index_url = root["boorus"][i]["show_index_url"].asString();

        sites[i].index = root["boorus"][i]["index"].asInt();

        checkFolder(sites[i].cache_path);
        checkFolder(sites[i].download_path);

        i++;
    }
}

void criticalSDLError(QWidget *parent,char* errorCharArray)
{
    QString titre;
    QString errorString;

    titre = QString("SDL Error");

    outputInfo("ERROR",
               std::string(errorCharArray),
               LEVEL_TOP_WIDGET);

    errorString = QString("Error : ") + QString(errorCharArray);

    parent->show();
    QMessageBox::critical(parent, titre, errorString);
    exit(-1);
}

void criticalCURLError(QWidget *parent, int error)
{
    QString titre;
    QString errorString;

    titre = QString("cUrl error");

    errorString = QString("cUrl error : ") + QString::number(error);

    outputInfo("ERROR",
               errorString.toStdString(),
               LEVEL_TOP_WIDGET);

    //parent->show();
    //QMessageBox::critical(parent, titre, errorString);
    //exit(error);
}

void criticalProgramError(QWidget *parent, int error)
{
    QString titre;
    QString errorString;

    titre = QString("Error : ") + QString::number(error);

    switch(error)
    {
    default:
        errorString = QString("Unknown error : ") + QString::number(error);
        break;
    case 28:
        errorString = QString("Error initializing cUrl, maybe libcurl.dll is missing ? Error ") + QString::number(error);
        break;
    }

    outputInfo("ERROR",
               errorString.toStdString(),
               LEVEL_TOP_WIDGET);

    parent->show();
    QMessageBox::critical(parent, titre, errorString);
    exit(error);
}

std::string returnTimeStringConvert(int time)
{
    int i=0;
    std::string timeUnit;
    std::string timeString;
    stringstream ss;

    while(time >= 60 && i<2)
    {
        time /= 60;
        i++;
    }

    switch(i)
    {
    case 0:
        if(time == 1){timeUnit = " sec ago";}
        else{timeUnit = " secs ago";}
        break;
    case 1:
        if(time == 1){timeUnit = " min ago";}
        else{timeUnit = " mins ago";}
        break;
    case 2:
        if(time == 1){timeUnit = " hour ago";}
        else{timeUnit = " hours ago";}
        break;
    }

    if(time >=24)
    {
        time /= 24;
        if(time == 1){timeUnit = " day ago";}
        else{timeUnit = " days ago";}

        if(time >=365)
        {
            time /= 365;
            if(time == 1){timeUnit = " year ago";}
            else{timeUnit = " years ago";}
        }
        else if(time >=30)
        {
            time /= 30;
            if(time == 1){timeUnit = " month ago";}
            else{timeUnit = " months ago";}
        }
    }

    ss << time;

    timeString = ss.str() + timeUnit;

    return timeString;
}

int returnPostAgeSec(int postDate)
{
    int age;
    age = time(NULL) - postDate;
    return age;
}

void clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget())
        {
            delete item->widget();
        }
        if (QSpacerItem *SpacerItem = item->spacerItem())
        {
            delete SpacerItem;
        }
        delete item;
    }
}

void clearLayoutSecond(QLayout *layout)
{
    int i = 0;

    for (i = 0; i < layout->count(); ++i)
    {
        QLayoutItem *layoutItem = layout->itemAt(i);

        if (layoutItem->spacerItem())
        {
            if(layoutItem->isEmpty())
            {
                layout->removeItem(layoutItem);
            }
            else
            {
                layout->removeItem(layoutItem);
                delete layoutItem;
            }
            --i;
        }
        if (layoutItem->layout())
        {
            layout->removeItem(layoutItem);
            delete layoutItem;
            --i;
        }
        if (layoutItem->widget())
        {
            if(i>-1)
            {
                if(layoutItem->isEmpty())
                {
                    layout->removeItem(layoutItem);
                }
                else
                {
                    layout->removeItem(layoutItem);
                    delete layoutItem;
                }
                --i;
            }
        }
    }
}

Json::Value loadJSONFile(char* filePath)
{   
    Json::Value root; // will contains the root value after parsing
    Json::Reader reader;
    std::ifstream test(filePath, std::ifstream::binary);
    bool parsingSuccessful = reader.parse(test, root) ;
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        outputInfo("JSON ERROR",
                   reader.getFormattedErrorMessages(),
                   LEVEL_TOP_WIDGET);
        return Json::nullValue;
    }

    test.close();

    return root;
}

void saveJSONFile(char* filePath, std::string data)
{
    std::ofstream mFile;
    mFile.open(filePath, ios::trunc);
    mFile << data;
    mFile.close();
}

void setAppVersionJSON()
{
    Json::Value root; // will contains the root value after parsing
    Json::Reader reader;
    Json::StyledWriter writer;

    root = loadJSONFile(CONF_FILE);

    root["versions"]["viewer"]["local"] = APP_VERSION;

    saveJSONFile(CONF_FILE, writer.write(root));
}

QString readChangelog()
{
    QString changelog;
    FILE* fp;
    char lettre;
    fp = fopen(CHANGELOG_FILE, "r");

    lettre = fgetc(fp);

    while(lettre != EOF)
    {
        changelog += lettre;
        lettre = fgetc(fp);
    }

    return changelog;
}

void checkFolder(std::string path)
{
    QDir dirCache1(path.c_str());
    if (!dirCache1.exists()) {
        dirCache1.mkpath(".");
    }
}

int loadTags(std::string taglist, std::string tags[TAG_NUMBER])
{
    char lettre;
    std::string mot = "";
    unsigned int i;
    unsigned int j = 0;

    for(i=0;i<strlen(taglist.c_str());i++)
    {
        lettre = *(taglist.c_str()+i);
        if(isspace(lettre))
        {
            tags[j] = mot;
            j++;
            mot = "";
        }
        else
        {
            mot += lettre;
        }
    }

    tags[j] = mot;
    j++;
    mot = "";
    return j;
}

char *downloadPath()
{
    std::string downloadPath;
    #ifdef _WIN32
        char* usrName;
        usrName = getenv("USERNAME");
        std::string usrNameString(usrName);

        downloadPath = "C:\\Users\\" + usrNameString + "\\Pictures\\QBooru\\";
        return strdup(downloadPath.c_str());
    #endif

    #ifdef __linux
        downloadPath = "/home/Pictures/Qbooru/";
        return strdup(downloadPath.c_str());
    #endif

    //return linux paths
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

/*Read image with cUrl*/
int cachingFile(char *url, char outfilename[4096], bool output, bool check_file_presence)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;
    int buf = 0;

    QFile Fout;
    Fout.setFileName(outfilename);

    if(Fout.exists() && check_file_presence)
    {
       return 0;
    }
    else
    {
        if(output)
        {
            outputInfo("INFO",
                               std::string(std::string("Caching : ")+std::string(url)),
                               LEVEL_CACHING);
        }

        curl = curl_easy_init();
        if (curl)
        {
            fp = fopen(outfilename,"wb");
            curl_easy_setopt(curl, CURLOPT_INTERFACE, NULL);
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
            curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, buf);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            fclose(fp);

            if(buf != 0)
            {
                QWidget *errorWidget;
                criticalCURLError(errorWidget,buf);
            }

            return res;
        }
        else
        {
            QWidget *errorWidget;
            criticalProgramError(errorWidget,28);
        }
    }

}

char *getFileExtension(char *filename)
{
    char *formatChar;
    std::string format;
    std::string fileName;

    /*Récupération de l'extension*/
    fileName     = filename;
    format = fileName.substr(fileName.find_last_of(".") + 1);
    formatChar = strdup(format.data());

    return formatChar;
}

/*Conversion*/
std::string intToString(int i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();

    return s;
}

char* stringToCString(std::string input)
{
    char* output = strdup(input.c_str());
    return output;
}
