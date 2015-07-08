#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#define LAST_CONF_FILE_VERSION 1

#include "fonctions_all.h"
#include "classBooruSite.h"


class ConfigFile
{
public:
    ConfigFile(bool loadOnly);
    ConfigFile(std::string path, bool loadOnly);
    ~ConfigFile();

    void loadFromPath(std::string path, bool loadOnly);
    void checkFile();
    void saveFile();
    void checkSoftwareVersions();

    void loadBooruSites();
    void resetBooruSites();

    void checkPreferredRating();
    void checkPreferredBooru();
    void checkLoadOnStartup();
    void checkDownloadPath();
    void checkWindowSize();
    void checkPictureGrid();
    void checkBoorusIntegrity();
    void ordonnerBoorus();

    void setDownloadPath(std::string downloadPath);
    void setBoorus(std::vector<BooruSite*> boorus);
    void setBooru(BooruSite *booru, int i);
    void setBooruNumber(int number);
    void setLoadingOnStartup(bool ok);
    void setPictureRow(int n);
    void setPictureColumns(int n);
    void setPictureNumber(int n);
    void setPreferredBooru(int b);
    void setPreferredRating(int r);
    void setWindowH(int h);
    void setWindowW(int w);

    void getVersion(char* versionChar, int versionInt[4]);

    std::vector<BooruSite*> getBoorus();
    BooruSite *getBooru(int i);
    int getBooruNumber();
    bool isLoadingOnStartup();
    int getPictureRow();
    int getPictureColumns();
    int getPictureNumber();
    int getPreferredBooru();
    int getPreferredRating();
    int getWindowH();
    int getWindowW();
    std::string getDownloadPath();


private:

    std::string file_path;

    Json::Value root;

    int config_file_version;

    std::vector<BooruSite*> boorus;

    std::string default_download_path;

    std::string api_key_derpibooru;
    int booru_number;
    int last_tag_refresh;
    bool load_on_startup;
    int picture_columns;
    int picture_rows;
    int picture_number;
    int preferred_booru;
    int preferred_rating;

    int window_h;
    int window_w;

    int version_updater_last[4];
    int version_updater_local[4];
    int version_viewer_last[4];
    int version_viewer_local[4];

    std::string version_updater_last_str;
    std::string version_updater_local_str;
    std::string version_viewer_last_str;
    std::string version_viewer_local_str;
};

#endif // CONFIGFILE_H

/*
"api_key_derpibooru" : "",
      "booru_number" : 5,
      "last_tag_refresh" : 1413756607,
      "load_on_startup" : false,
      "picture_columns" : 5,
      "picture_number" : 15,
      "picture_rows" : 3,
      "preferred_booru" : 0,
      "preferred_rating" : 0,
      "window_h" : 768,
      "window_w" : 1024
   },
   "temp" : null,
   "versions" : {
      "updater" : {
         "last" : "1.1.0.3",
         "local" : "1.1.0.3"
      },
      "viewer" : {
         "last" : "1.10.5.1",
         "local" : "1.10.5.2"
      }
   }
   */
