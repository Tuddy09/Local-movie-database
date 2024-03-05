#pragma once
#include <vector>
#include "Movie.h"

class WatchList
{
protected:
	std::vector<Movie> movies;
	int current;
public:
	WatchList();
	void add(const Movie& movie);
	void remove(int index);
	int findByTitle(std::string title);
	Movie getCurrentMovie();
	std::vector<Movie> getAllWatchList();
	void play();
	void next();
	bool isEmpty();
	virtual ~WatchList() {}
};