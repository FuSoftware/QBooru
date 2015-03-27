#include "fonctions_json.h"

void setLastVersionJSON()
{
    Json::Value rootConf; // will contains the root value after parsing
    Json::Value rootLast; // will contains the root value after parsing
    Json::StyledWriter writer;

    rootConf = loadJSONFile(CONF_FILE);
    rootLast = loadJSONFile(LAST_VERSION_FILE);

    rootConf["versions"]["viewer"]["last"] = rootLast["viewer"];
    rootConf["versions"]["updater"]["last"] = rootLast["updater"];

    saveJSONFile(CONF_FILE, writer.write(rootConf));
}

void setAppVersionJSON()
{
    Json::Value root; // will contains the root value after parsing
    Json::StyledWriter writer;

    root = loadJSONFile(CONF_FILE);

    root["versions"]["updater"]["local"] = APP_VERSION;

    saveJSONFile(CONF_FILE, writer.write(root));
}

Json::Value saveAndLoad(Json::Value root, char* file)
{
    /*
     * Saves the specified Json::Value to a file.
     * Loads the file and returns it's Json::Value root
     * */
    Json::StyledWriter writer;
    saveJSONFile(file, writer.write(root));
    root = loadJSONFile(file);
    return root;
}

Json::Value loadJSONFile(char* filePath)
{
    Json::Value root; // will contains the root value after parsing
    Json::Reader reader;
    std::ifstream test(filePath, std::ifstream::binary);
    bool parsingSuccessful = reader.parse(test, root) ;
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        outputInfo("JSON ERROR",
                   reader.getFormattedErrorMessages(),
                   LEVEL_TOP_WIDGET);
        return Json::nullValue;
    }

    test.close();

    return root;
}

void saveJSONFile(char* filePath, std::string data)
{
    std::ofstream mFile;
    mFile.open(filePath);
    mFile << data;
    mFile.close();
}
