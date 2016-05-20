#include "jsonobject.h"

JSONObject::JSONObject(Json::Value value)
{
    this->root = value;
}

JSONObject::JSONObject(string str)
{
    loadString(str);
}

void JSONObject::loadString(string str)
{
    Json::Value root; // will contains the root value after parsing
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(str, root) ;
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        std::cerr << reader.getFormattedErrorMessages() << std::endl;
        this->root =  Json::nullValue;
    }

    this->root =  root;
}

string JSONObject::getString(string tag, string def)
{
    try
    {
        def = this->root[tag].asString();
    }
    catch(std::exception const& e)
    {
        cerr << "ERROR : " << e.what() << endl;
    }

    return def;
}

int JSONObject::getInt(string tag, int def)
{
    try
    {
        def = this->root[tag].asInt();
    }
    catch(std::exception const& e)
    {
        cerr << "ERROR : " << e.what() << endl;
    }

    return def;
}

double JSONObject::getDouble(string tag, double def)
{
    try
    {
        def = this->root[tag].asDouble();
    }
    catch(std::exception const& e)
    {
        cerr << "ERROR : " << e.what() << endl;
    }

    return def;
}

JSONObject* JSONObject::getObject(string tag)
{
    try
    {
        return new JSONObject(this->root[tag]);
    }
    catch(std::exception const& e)
    {
        cerr << "ERROR : " << e.what() << endl;
    }

    return 0;
}

void JSONObject::putString(string tag, string s){
    root[tag] = s;
}

void JSONObject::putInt(string tag, int i){
    root[tag] = i;
}

void JSONObject::putDouble(string tag, double d){
    root[tag] = d;
}
