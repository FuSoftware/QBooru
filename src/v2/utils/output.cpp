#include "output.h"

const string currentDateTime()
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

    string type_string;
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

    cout << "[" << type_string << "]";

    for(int i=0;i<level;i++){cout << " ";}

    cout << "[" << currentDateTime() << "]"
              << "|--> " << data << endl;
}
