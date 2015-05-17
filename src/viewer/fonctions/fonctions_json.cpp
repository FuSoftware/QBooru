#include "fonctions_json.h"

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
