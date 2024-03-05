#include "movie.h"
#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include "utils.h"
using namespace std;

Movie::Movie(std::string title, std::string genre, int yearOfRelease, int numberOfLikes, std::string trailer)
{
	this->title = std::move(title);
	this->genre = std::move(genre);
	this->yearOfRelease = yearOfRelease;
	this->numberOfLikes = numberOfLikes;
	this->trailer = std::move(trailer);
}

std::string Movie::getTitle() const
{
	return this->title;
}

std::string Movie::getGenre() const
{
	return this->genre;
}

int Movie::getYearOfRelease() const
{
	return this->yearOfRelease;
}

int Movie::getNumberOfLikes() const
{
	return this->numberOfLikes;
}

std::string Movie::getTrailer() const
{
	return this->trailer;
}

std::string Movie::toString() const
{	
	return this->title + " | " + this->genre + " | " + std::to_string(this->yearOfRelease) + " | " + 
		std::to_string(this->numberOfLikes) + " | " + this->trailer;
}

void Movie::play()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getTrailer().c_str(), NULL, SW_SHOWMAXIMIZED);
}


Movie::~Movie() = default;

std::istream& operator>>(std::istream& is, Movie& movie)
{
	std::string line;
	getline(is, line);
	std::vector<std::string> tokens = tokenize(line, ',');
	if (tokens.size() != 5)
		return is;
	movie.title = tokens[0];
	movie.genre = tokens[1];
	movie.yearOfRelease = stoi(tokens[2]);
	movie.numberOfLikes = stoi(tokens[3]);
	movie.trailer = tokens[4];
	return is;
}

std::ostream& operator<<(std::ostream& os, Movie& movie)
{
	os << movie.title << "," << movie.genre << "," << movie.yearOfRelease << "," << movie.numberOfLikes << "," << movie.trailer << "\n";
	return os;
}
