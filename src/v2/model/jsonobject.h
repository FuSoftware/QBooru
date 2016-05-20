#ifndef JSONOBJECT_H
#define JSONOBJECT_H

/*
 * This classes is a wrapper for the Json::Value class from JSONCPP
 * It allows for more error control than the native one
 *
 * You can see it a simplified Java JSONObject
 */

#include <iostream>
#include <exception>
#include "../json/json.h"

using namespace std;

class JSONObject
{
public:
    JSONObject();
    JSONObject(Json::Value value);
    JSONObject(string str);

    void loadString(string str);

    string getString(string tag, string def);
    int getInt(string tag, int def);
    double getDouble(string tag, double def);
    JSONObject* getObject(string tag);

    void putString(string tag, string s);
    void putInt(string tag, int i);
    void putDouble(string tag, double d);

private:
    Json::Value root;
};

#endif // JSONOBJECT_H
