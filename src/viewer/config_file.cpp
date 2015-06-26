#include "config_file.h"

ConfigFile::ConfigFile(bool loadOnly)
{
    this->loadFromPath(CONF_FILE, loadOnly);
}

ConfigFile::ConfigFile(std::string path, bool loadOnly)
{
    file_path = path;
    this->loadFromPath(path, loadOnly);
}

ConfigFile::~ConfigFile()
{

}

void ConfigFile::loadFromPath(std::string path, bool loadOnly)
{
    root = loadJSONFile(path.c_str());

    checkFile();

    if(!loadOnly)
    {
        checkSoftwareVersions();
    }

    loadBooruSites();
    saveFile();
}

void ConfigFile::saveFile()
{
    Json::Value newRoot;
    Json::StyledWriter writer;

    for(int i=0;i<this->booru_number;i++)
    {
        newRoot["boorus"][i] = boorus.at(i);
    }

    newRoot["paths"]["default_download_path"] = default_download_path;

    newRoot["settings"]["config_file_version"] = config_file_version;
    newRoot["settings"]["api_key_derpibooru"] = api_key_derpibooru;
    newRoot["settings"]["booru_number"] = booru_number;
    newRoot["settings"]["last_tag_refresh"] = last_tag_refresh;
    newRoot["settings"]["load_on_startup"] = load_on_startup;
    newRoot["settings"]["picture_columns"] = picture_columns;
    newRoot["settings"]["picture_rows"] = picture_rows;
    newRoot["settings"]["picture_number"] = picture_number;
    newRoot["settings"]["preferred_booru"] = preferred_booru;
    newRoot["settings"]["preferred_rating"] = preferred_rating;
    newRoot["settings"]["window_h"] = window_h;
    newRoot["settings"]["window_w"] = window_w;

    newRoot["versions"]["updater"]["local"] = version_updater_local_str;
    newRoot["versions"]["updater"]["last"] = version_updater_last_str;
    newRoot["versions"]["viewer"]["local"] = version_viewer_local_str;
    newRoot["versions"]["viewer"]["last"] = version_viewer_last_str;

    saveJSONFile(file_path.c_str(),writer.write(root));
}

void ConfigFile::checkSoftwareVersions()
{
    bool newVersion = true;

    root["versions"]["viewer"]["local"] = APP_VERSION;

    int errorbuf = cachingFile(LAST_VERSION_FILE_URL, LAST_VERSION_FILE, false, false);

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
    root["versions"]["updater"]["local"] = rootVersions["updater"].asCString(); // Since it updates on its own, this is set to avoid errors

    root["versions"]["viewer"]["last"] = rootVersions["viewer"].asCString();

    version_updater_last_str = root["versions"]["updater"]["last"].asString();
    version_updater_local_str = root["versions"]["updater"]["local"].asString();
    version_viewer_last_str = root["versions"]["viewer"]["last"].asString();
    version_viewer_local_str = root["versions"]["viewer"]["local"].asString();


    /*Checks current and last version*/
    getVersion(strdup(root["versions"]["updater"]["local"].asCString()),version_updater_local);
    getVersion(strdup(root["versions"]["updater"]["last"].asCString()),version_updater_last);

    getVersion(strdup(root["versions"]["viewer"]["local"].asCString()),version_viewer_local);
    getVersion(strdup(root["versions"]["viewer"]["last"].asCString()),version_viewer_last);

    for(int i=0;i<4;i++)
    {
        if(version_viewer_local[i] >= version_viewer_last[i])
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
}

void ConfigFile::checkFile()
{
    bool save_pending = false;

    /*Loads the version of the file*/

    if (root["settings"]["config_file_version"].isInt())
    {
       this->config_file_version = root["settings"]["config_file_version"].asInt();
    }
    else
    {
        this->config_file_version = 0;
        save_pending = true;
    }

    /*Checks the data and loads it*/

    this->checkBoorusIntegrity();

    this->api_key_derpibooru = root["settings"]["api_key_derpibooru"].asString();

    if(config_file_version <= 1)
    {
        checkPreferredRating();

        checkWindowSize();
        checkPictureGrid();
    }

    if(root["paths"]["default_download_path"] == Json::nullValue) root["paths"]["default_download_path"] == downloadPath();
    root = saveAndLoad(root,CONF_FILE);

    if(root["settings"]["load_on_startup"] == Json::nullValue) root["settings"]["load_on_startup"] = false;
    root = saveAndLoad(root,CONF_FILE);
}

void ConfigFile::checkPreferredRating()
{
    if(root["settings"]["preferred_rating"].isInt())
    {
        if(root["settings"]["preferred_rating"].asInt() >= 4)
        {
            this->preferred_rating = 0;
        }
        else
        {
            this->preferred_rating = root["settings"]["preferred_rating"].asInt();
        }
    }
    else
    {
        this->preferred_rating = 0;
    }
}

void ConfigFile::checkPreferredBooru()
{
    if(root["settings"]["preferred_booru"].isInt())
    {
        if(root["settings"]["preferred_booru"].asInt() >= root["settings"]["booru_number"].asInt())
        {
            this->preferred_booru = 0;
        }
        else
        {
            this->preferred_rating = root["settings"]["preferred_booru"].asInt();
        }
    }
    else
    {
        this->preferred_rating = 0;
    }
}

void ConfigFile::checkLoadOnStartup()
{

}

void ConfigFile::checkWindowSize()
{
    if(root["settings"]["window_w"].isInt())
    {
        if(root["settings"]["window_w"].asInt() < 1024)
        {
            this->window_w = 1024;
        }
        else
        {
            this->window_w = root["settings"]["window_w"].asInt();
        }
    }
    else
    {
        this->window_w = 1024;
    }

    if(root["settings"]["window_h"].isInt())
    {
        if(root["settings"]["window_h"].asInt() < 768)
        {
            this->window_h = 768;
        }
        else
        {
            this->window_h = root["settings"]["window_h"].asInt();
        }
    }
    else
    {
        this->window_h = 768;
    }
}

void ConfigFile::checkPictureGrid()
{

    if(root["settings"]["picture_rows"].isInt())
    {
        if(root["settings"]["picture_rows"].asInt() < 3 || root["settings"]["picture_rows"].asInt() > 7)
        {
            this->picture_rows = 3;
        }
        else
        {
            this->picture_rows = root["settings"]["picture_rows"].asInt();
        }
    }
    else
    {
        this->picture_rows = 3;
    }

    if(root["settings"]["picture_columns"].isInt())
    {
        if(root["settings"]["picture_columns"].asInt() < 5 || root["settings"]["picture_columns"].asInt() > 9)
        {
            this->picture_columns = 5;
        }
        else
        {
            this->picture_columns = root["settings"]["picture_columns"].asInt();
        }
    }
    else
    {
        this->picture_columns = 5;
    }

    picture_number = picture_columns * picture_rows;
}

void ConfigFile::checkBoorusIntegrity()
{
    this->booru_number = 0;
    int j = 0;
    int i = 0;
    int indexArray[MAX_BOORU_NUMBER];

    do
    {
        if(root["boorus"][i].isObject())
        {
            indexArray[j] = root["boorus"][i]["index"].asInt();
            j++;
            i++;
            this->booru_number++;
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

    this->ordonnerBoorus();

    if(this->booru_number < 1)
    {
        resetBooruSites(root);
        outputInfo("INFO",std::string("Boorus Reset"),LEVEL_TOP_WIDGET);
    }
}

void ConfigFile::ordonnerBoorus()
{
    /*
     * Puts all the boorus in the config file in the proper order.
     * It also ensures no blank values are left in the booru list
     * */
    int i,j;

    for(j=0;j<this->booru_number - 1;j++)
    {
        for(i=0;i<this->booru_number - 1;i++)
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
}

void ConfigFile::loadBooruSites()
{
    BooruSite sites[this->booru_number];
    int i = 0;
    while(i < this->booru_number)
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

        boorus.push_back(sites[i]);

        i++;
    }
}

void ConfigFile::resetBooruSites()
{
    BooruSite Gelbooru("Gelbooru","http://gelbooru.com",GELBOORU_TYPE,1);
    BooruSite Yandere("Yandere","http://yande.re",MOEBOORU_TYPE,2);
    BooruSite Konachan("Konachan","http://konachan.com",MOEBOORU_TYPE,3);
    BooruSite Danbooru("Danbooru", "http://danbooru.donmai.us", DANBOORU2_TYPE,4);

    boorus.push_back(Gelbooru);
    boorus.push_back(Yandere);
    boorus.push_back(Konachan);
    boorus.push_back(Danbooru);

    this->booru_number = 4;
}

/*Getters*/

std::vector<BooruSite> ConfigFile::getBoorus()
{
    return boorus;
}

BooruSite ConfigFile::getBooru(int i)
{
    return boorus.at(i);
}

int ConfigFile::getBooruNumber()
{
    return this->booru_number;
}

bool ConfigFile::isLoadingOnStartup()
{
    return this->load_on_startup;
}
int ConfigFile::getPictureRow()
{
    return this->picture_rows;
}
int ConfigFile::getPictureColumns()
{
    return this->picture_columns;
}
int ConfigFile::getPictureNumber()
{
    return this->picture_number;
}
int ConfigFile::getPreferredBooru()
{
    return this->preferred_booru
}
int ConfigFile::getPreferredRating()
{
    return this->preferred_rating;
}
int ConfigFile::getWindowH()
{
    return this->window_h;
}
int ConfigFile::getWindowW()
{
    return this->window_w;
}

std::string ConfigFile::getDownloadPath()
{
    return this->default_download_path;
}

void ConfigFile::setDownloadPath(std::string downloadPath)
{
    this->default_download_path = downloadPath;
}

void ConfigFile::setBoorus(std::vector<BooruSite> boorus)
{
    this->boorus = boorus;
    this->booru_number = boorus.size();
}

void ConfigFile::setBooru(BooruSite booru, int i)
{
    this->boorus.at(i) = booru;
}

void ConfigFile::setBooruNumber(int number)
{
    this->booru_number = number;
}
void ConfigFile::setLoadingOnStartup(bool ok)
{
    this->load_on_startup = ok;
}
void ConfigFile::setPictureRow(int n)
{
    this->picture_rows = n;
}
void ConfigFile::setPictureColumns(int n)
{
    this->picture_columns = n;
}
void ConfigFile::setPictureNumber(int n)
{
    this->picture_number = n;
}
void ConfigFile::setPreferredBooru(int b)
{
    this->preferred_booru = b;
}
void ConfigFile::setPreferredRating(int r)
{
    this->preferred_rating = r;
}
void ConfigFile::setWindowH(int h)
{
    this->window_h = h;
}
void ConfigFile::setWindowW(int w)
{
    this->window_w = w;
}
