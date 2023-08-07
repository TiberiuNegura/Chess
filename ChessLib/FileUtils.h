#pragma once

#include <string>
#include <vector>

class FileUtils
{
public:
	template <typename... Args>
	static bool HasAnyExtension(const std::string& filePath, Args... desiredExtensions) {
		size_t dotPos = filePath.find_last_of(".");

		if (dotPos != std::string::npos) {
			std::string actualExtension = filePath.substr(dotPos + 1);

			// Convert actualExtension to lowercase for case-insensitive comparison
			for (char& c : actualExtension)
				c = std::tolower(c);

			// Convert each desired extension to lowercase and compare
			std::vector<std::string> extensions = { desiredExtensions... };
			for (const std::string& desiredExt : extensions) {
				std::string copyDesiredExtension = desiredExt;
				for (char& c : copyDesiredExtension)
					c = std::tolower(c);

				if (actualExtension == copyDesiredExtension)
					return true; // Found a matching extension
			}
		}

		return false; // No extension found in the path or no matching extension
	}
};
