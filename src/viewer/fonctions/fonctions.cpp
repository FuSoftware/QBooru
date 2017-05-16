#include "fonctions_all.h"

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

void outputInfo(int type, std::string data)
{
    /*
     * Outputs formatted messages  :
     * [TYPE][DATE]|-->DATA
     * */

    std::string type_string;
    int level;

    switch(type)
    {
    case L_DEBUG:
        type_string = "DEBUG";
        level = 2;
        break;
    case L_INFO:
        type_string = "INFO";
        level = 3;
        break;
    case L_WARNING:
        type_string = "WARNING";
        level = 0;
        break;
    case L_ERROR:
        type_string = "ERROR";
        level = 2;
        break;
    }

    std::cout << "[" << type_string << "]";

    for(int i=0;i<level;i++){std::cout << " ";}

    std::cout << "[" << currentDateTime() << "]"
              << "|--> " << data << std::endl;
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

char *downloadPath()
{
    /*
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
    */

    return "downloads/";
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

bool fexists(const char *filename)
{
  std::ifstream ifile(filename);

#if __linux || __APPLE__
  return ifile.is_open();
#else
  return ifile;
#endif
}
