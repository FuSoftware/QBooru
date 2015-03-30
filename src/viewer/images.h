#include <QString>
#include "constantes.h"

#ifndef IMAGES_H_INCLUDED
#define IMAGES_H_INCLUDED

class Image
{
    public:
        void Refresh(QString imageID);
        void EcritureVariables(char outfilename[4096]);


        QString id;
        int id_number;
        QString created_at;
        QString updated_at;
        QString duplicate_reports;
        QString file_name;
        QString description;
        QString uploader;
        QString image;
        int score;
        int upvotes;
        int downvotes;
        int comment_count;
        QString tags[128];
        QString tag_ids[128];
        int width;
        int height;
        double aspect_ratio;
        QString original_format;
        QString mime_type;
        char sha512_hash[512];
        char orig_sha512_hash[512];
        QString source_url;
        QString license;
        QString comments[64][4]; /** Body, Author, ImageID, Date **/
        QString favourited_by_users[256];
        QString representations[9][2];
        bool is_rendered;
        bool is_optimized;

        int connectionState;

    private:
};


#endif // IMAGES_H_INCLUDED
