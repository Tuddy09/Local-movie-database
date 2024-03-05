#include "HTMLWatchList.h"
#include <fstream>
#include "RepositoryExceptions.h"
#include <Windows.h>

void HTMLWatchList::writeToFile()
{
	std::ofstream fileDescriptor(this->filename);
	if (!fileDescriptor.is_open())
		throw FileException("The file could not be opened!");
    const std::string header =  "<!DOCTYPE html>    <!-- write this exactly as it is here -->\n"
                                "<html> <!--write this exactly as it is here-->\n"
                                "<head> <!--write this exactly as it is here-->\n"
                                "\t<title>Watchlist</title> <!--replace “Playlist” with the title for your HTML-->\n"
                                "</head> <!--write this exactly as it is here(close head tag)-->\n"
                                "<body> <!--write this exactly as it is here-->\n"
                                "<table border = \"1\"> <!--write this exactly as it is here-->\n"
                                "\t<tr> <!--tr = table row; 1 row for each entity-->\n"
                                "\t\t<td>Title</td> <!--td = table data; 1 td for each attribute of the entity-->\n"
                                "\t\t<td>Genre</td>\n"
                                "\t\t<td>Year of release</td>\n"
                                "\t\t<td>Number of likes</td>\n"
                                "\t\t<td>Trailer</td>\n"
                                "\t</tr>\n";
    const std::string footer =  "</table>\n"
								"</body>\n"
								"</html>\n";
    fileDescriptor << header;
    for (auto movie : this->movies)
    {
        fileDescriptor << "\t<tr>\n";
        fileDescriptor << "\t\t<td>" << movie.getTitle() << "</td>\n";
        fileDescriptor << "\t\t<td>" << movie.getGenre() << "</td>\n";
        fileDescriptor << "\t\t<td>" << movie.getYearOfRelease() << "</td>\n";
        fileDescriptor << "\t\t<td>" << movie.getNumberOfLikes() << "</td>\n";
        fileDescriptor << "\t\t<td><a href = \"" << movie.getTrailer() << "\">Link</a></td>\n";
        fileDescriptor << "\t</tr>\n";
	}
    fileDescriptor << footer;
    fileDescriptor.close();
}

void HTMLWatchList::displayWatchList()
{
    ShellExecuteA(NULL, "open", this->filename.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
