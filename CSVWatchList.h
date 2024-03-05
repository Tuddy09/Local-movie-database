#pragma once
#include "FileWatchList.h"

class CSVWatchList : public FileWatchList
{
public:
	CSVWatchList(const std::string& filename) : FileWatchList(filename) {};
	~CSVWatchList() {};
	void writeToFile() override;
	void displayWatchList() override;
};