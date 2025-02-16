#pragma once

#include <string>

class FileUtils
{
public:
	static bool ReadFile(const std::string& filePath, std::string* targetString);
};