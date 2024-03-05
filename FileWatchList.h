#pragma once
#include "WatchList.h"

class FileWatchList : public WatchList
{
protected:
	std::string filename;
public:
	FileWatchList(const std::string& filename)
	{
		this->filename = filename;
	}
	virtual void writeToFile() = 0;
	virtual void displayWatchList() = 0;
	virtual ~FileWatchList() {}
};;