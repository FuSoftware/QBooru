#include "fonctions_config.h"

void checkConfigFile()
{
    /*
     * Checks the config file's validity by checking :
     * - Versions
     * - All the variables
     * - Boorus
     * */

    int errorbuf;
    int lastVersion[4];
    int localVersion[4];
    bool newVersion = true;
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

    /*Checks current and last version*/
    getVersion(strdup(root["versions"]["viewer"]["local"].asCString()),localVersion);
    getVersion(strdup(root["versions"]["viewer"]["last"].asCString()),lastVersion);

    for(int i=0;i<4;i++)
    {
        if(localVersion[i] >= lastVersion[i])
        {
            newVersion = false;
        }
    }

    if(newVersion)
    {
        /*Updates if needed*/
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


    /*Checks all the variables in the config file*/

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

    /*Checks if boorus are valid*/
    root = checkBoorusIntegrity(root); //Boorus + booru_number
    root = saveAndLoad(root,CONF_FILE);

    outputInfo("INFO",std::string("Boorus checked"),LEVEL_TOP_WIDGET);

    root["settings"]["picture_number"] = root["settings"]["picture_columns"].asInt()*root["settings"]["picture_rows"].asInt();

    if(root["settings"]["preferred_booru"].asInt() >= root["settings"]["booru_number"].asInt()) root["settings"]["preferred_booru"] = 0;

    saveJSONFile(CONF_FILE, writer.write(root));
}

void getVersion(char* versionChar, int versionInt[4])
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
        resetBooruSites(root);
        outputInfo("INFO",std::string("Boorus Reset"),LEVEL_TOP_WIDGET);
    }

    return root;
}

void resetBooruSites(Json::Value root)
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

    BooruSite Danbooru("Danbooru", "http://danbooru.donmai.us", DANBOORU2_TYPE,4);
    Danbooru.saveBooruSite();
}

void loadBooruSites(BooruSite sites[], int BooruIndex)
{
    Json::Value root = loadJSONFile(CONF_FILE);
    int i = 0;
    while(i < BooruIndex)
    {
        sites[i].setName(root["boorus"][i]["name"].asString());
        outputInfo("INFO",
                   std::string("Loading ") + sites[i].getName(),
                   LEVEL_TOP_WIDGET);

        sites[i].setBaseUrl(        root["boorus"][i]["base_url"].asString());
        sites[i].setSearchUrl(      root["boorus"][i]["search_url"].asString());
        sites[i].setTagUrl(         root["boorus"][i]["tag_url"].asString());

        sites[i].setCachePath(      root["boorus"][i]["cache_path"].asString());
        sites[i].setDownloadPath(   root["boorus"][i]["download_path"].asString());
        sites[i].setSearchFilePath( root["boorus"][i]["search_file_path"].asString());
        sites[i].setTagFilePath(    root["boorus"][i]["tag_file_path"].asString());

        sites[i].setSiteType(       root["boorus"][i]["siteTypeInt"].asInt());

        sites[i].setShowIndexUrl(   root["boorus"][i]["show_index_url"].asString());

        sites[i].setIndex(          root["boorus"][i]["index"].asInt());

        checkFolder(sites[i].getCachePath());
        checkFolder(sites[i].getDownloadPath());

        i++;
    }
}

Json::Value ordonnerBoorus(Json::Value root)
{
    /*
     * Puts all the boorus in "configuration .json" (need to set it as input value) in the proper order.
     * It also ensures no blank values are left in the booru list
     * */
    int nombre_boorus = root["settings"]["booru_number"].asInt();//Gets the booru number
    int i,j;

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

void setAppVersionJSON()
{
    Json::Value root; // will contains the root value after parsing
    Json::Reader reader;
    Json::StyledWriter writer;

    root = loadJSONFile(CONF_FILE);

    root["versions"]["viewer"]["local"] = APP_VERSION;

    saveJSONFile(CONF_FILE, writer.write(root));
}
