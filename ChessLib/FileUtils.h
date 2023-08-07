#pragma once

#include <string>

class FileUtils
{
public:
	static bool HasExtension(const std::string& filePath, const std::string& desiredExtension);
};
