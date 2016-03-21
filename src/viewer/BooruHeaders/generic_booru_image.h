#ifndef GENERIC_BOORU_IMAGE_H
#define GENERIC_BOORU_IMAGE_H

#include <iostream>
#include "constantes.h"

#include "../fonctions/fonctions.h"
#include "../fonctions/fonctions_json.h"

#include "../classBooruSite.h"


class BooruImage
{
public :

    /*Fonctions*/
    BooruImage();
    BooruImage(int booru_index);
    BooruImage(BooruSite *booru);
    ~BooruImage();

    void setBooru(int booru_index);
    void setBooru(BooruSite* booru);
    void loadData(int picture_index);
    void loadTags(std::string tags_str);
    void loadPaths();
    void loadPaths(std::string download_folder);
    void loadPaths(std::string download_folder,std::string prefix);

    void download_thumb();
    void download_medium();
    void download_full();

    std::string getThumbPath();
    std::string getMediumPath();
    std::string getFullPath();

    BooruSite* getBooru();

    /*Header*/
    int booru_type;

    /*Data*/
    int id;
    std::string created_at;
    std::string author;
    std::string source;

    int score;
    int file_size;

    std::vector<std::string> tags;

    std::string file_url;
    int width;
    int height;

    std::string preview_url;
    int preview_height;
    int preview_width;
    int actual_preview_height;
    int actual_preview_width;

    std::string sample_url;
    int sample_width;
    int sample_height;
    int sample_file_size;

    std::string full_url;
    int full_height;
    int full_width;
    int full_file_size;

    char rating;

    int tagNumber;

private:

    BooruSite* booru;

    /*Paths*/
    std::string thumb_path;
    std::string medium_path;
    std::string full_path;

};

#endif // GENERIC_BOORU_IMAGE_H
