#include "repository.h"
#include <algorithm>
#include <sstream>
#include "utils.h"
#include "RepositoryExceptions.h"
using namespace std;

Repository::Repository(const std::string& filename) {
    this->filename = filename;
    this->readFromFile();
}


std::vector<Movie> Repository::getAllRepo() {
    return this->movies;
}

int Repository::getSizeRepo() {
    return this->movies.size();
}

void Repository::addRepo(const Movie& movie) {
    if(this->findByTitle(movie.getTitle()) != -1)
		throw DuplicateMovieException();
    this->movies.push_back(movie);
    this->writeToFile();
}

int Repository::findByTitle(std::string title) {
    int index = -1;
    auto iterator = std::find_if(this->movies.begin(), this->movies.end(), [&title](Movie& object) {return object.getTitle() == title; });
    if (iterator != this->movies.end()) {
        auto index = std::distance(this->movies.begin(), iterator);
        return index;
    }
    return index;
}

void Repository::removeRepo(int index) {
    this->movies.erase(movies.begin() + index);
    this->writeToFile();
}

void Repository::updateRepo(int index, const Movie& newMovie) {
    this->movies[index] = newMovie;
    this->writeToFile();
}

void Repository::readFromFile()
{
    ifstream file(this->filename);
    if(!file.is_open())
		throw FileException("The file could not be opened!");
    string line;
    Movie movie;
    while (file >> movie)
		this->movies.push_back(movie);
    file.close();
}

void Repository::writeToFile()
{
    ofstream file(this->filename);
	if (!file.is_open())
        throw FileException("The file could not be opened!");
	for (auto movie : this->movies)
		file << movie;
	file.close();
}

