#include "CSVWatchList.h"
#include <fstream>
#include "RepositoryExceptions.h"
#include <Windows.h>

void CSVWatchList::writeToFile()
{
	std::ofstream fileDescriptor(this->filename);
	if (!fileDescriptor.is_open())
		throw FileException("The file could not be opened!");
	for (auto movie : this->movies)
		fileDescriptor << movie;
	fileDescriptor.close();
}

void CSVWatchList::displayWatchList()
{
	ShellExecuteA(NULL, NULL, "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Excel.lnk", this->filename.c_str(), NULL, SW_SHOWMAXIMIZED);
}
