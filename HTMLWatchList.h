#pragma once
#include "FileWatchList.h"

class HTMLWatchList : public FileWatchList
{
public:
	HTMLWatchList(const std::string& filename) : FileWatchList(filename) {};
	~HTMLWatchList() {};
	void writeToFile() override;
	void displayWatchList() override;
};