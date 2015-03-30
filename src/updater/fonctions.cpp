#include "fonctions.h"

#include "constantes.h"

#include <QProcess>

void runViewer()
{
    outputInfo("INFO","Running Viewer",LEVEL_UPDATER);

    QString path = QString(VIEWER_MAIN_EXECUTABLE);

    QProcess *Process = new QProcess;
    Process->startDetached(path,QStringList());

    while(Process->waitForStarted(3000));

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
    /*
     * Outputs formatted messages  :
     * [TYPE][DATE]|-->DATA
     * */
    std::cout << "[" << type << "]"
              << "[" << currentDateTime() << "]"
              << "|";

    for(int i=0;i<level;i++)
    {
        std::cout <<"-";
    }

    std::cout << "> " << data << std::endl;
}

void getVersion(const char* versionChar, int versionInt[VERSION_CONTROL_DIGITS])
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
                outputInfo("ERROR",
                           std::string(std::string("cUrl error : ")+intToString(buf)),
                           LEVEL_CACHING);
            }

            return res;
        }
        else
        {
            outputInfo("ERROR",
                       std::string(std::string("cUrl init error ")),
                       LEVEL_CACHING);
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
