#ifndef GENERIC_BOORU_IMAGE_H
#define GENERIC_BOORU_IMAGE_H

#include <iostream>
#include "constantes.h"

class BooruImage
{
public :

    /*Fonctions*/

    /*Header*/
    int booru_type;

    /*Data*/
    int id;
    std::string created_at;
    std::string author;
    std::string source;

    int score;
    int file_size;

    std::string tags[TAG_NUMBER];

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
};

#endif // GENERIC_BOORU_IMAGE_H
