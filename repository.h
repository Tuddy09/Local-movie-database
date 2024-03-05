#pragma once
#include <vector>
#include "movie.h"
#include <fstream>
#include <string>
class Repository {
protected:
	std::vector<Movie> movies;
	std::string filename;

public:
	Repository(const std::string& filename);
	~Repository() {};
	std::vector<Movie> getAllRepo();
	int getSizeRepo();
	void addRepo(const Movie& movie);
	virtual int findByTitle(std::string title);
	void removeRepo(int index);
	void updateRepo(int index,const Movie& newMovie);
private:
	void readFromFile();
	void writeToFile();
};