#include "FileUtils.h"

#include <fstream>
#include <sstream>

bool FileUtils::ReadFile(const std::string& filePath, std::string* targetString)
{
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open())
        return false;

    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    *targetString = buffer.str();
    return true;
}
