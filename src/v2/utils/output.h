#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <ctime>

using namespace std;

enum LogLevel{
    L_DEBUG = 0,
    L_INFO,
    L_WARNING,
    L_ERROR
};

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const string currentDateTime();
void outputInfo(int type, string data);

#endif // OUTPUT_H
