#include "FileUtils.h"

bool FileUtils::HasExtension(const std::string& filePath, const std::string& desiredExtension)
{
	size_t dotPos = filePath.find_last_of(".");

	if (dotPos != std::string::npos) {
		std::string actualExtension = filePath.substr(dotPos + 1);
		std::string copyDesiredExtension = desiredExtension;

		// Convert actualExtension and desiredExtension to lowercase for case-insensitive comparison
		for (char& c : actualExtension)
			c = std::tolower(c);

		for (char& c : copyDesiredExtension)
			c = std::tolower(c);

		return actualExtension == copyDesiredExtension;
	}

	return false; // No extension found in the path
}
