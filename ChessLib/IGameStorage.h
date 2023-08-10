#pragma once


class IGameStorage
{
public:

	virtual bool SavePGN(const std::string& path) const = 0;
	virtual void SaveFEN(const std::string& path) const = 0;
	virtual bool LoadFromFormat(const std::string& path) = 0;
};