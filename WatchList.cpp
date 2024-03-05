#include "WatchList.h"

WatchList::WatchList()
{
	this->current = 0;
}

void WatchList::add(const Movie& movie)
{
	this->movies.push_back(movie);
}

void WatchList::remove(int index)
{
	this->movies.erase(movies.begin() + index);
}

int WatchList::findByTitle(std::string title)
{
	int index = -1;
	auto iterator = std::find_if(this->movies.begin(), this->movies.end(), [&title](Movie& object) {return object.getTitle() == title; });
	if (iterator != this->movies.end()) {
		auto index = std::distance(this->movies.begin(), iterator);
		return index;
	}
	return index;

}

Movie WatchList::getCurrentMovie()
{
	if(this->current == this->movies.size())
		this->current = 0;
	return this->movies[this->current];
	return Movie{};
}

std::vector<Movie> WatchList::getAllWatchList()
{
	return this->movies;

}

void WatchList::play()
{
	if (this->movies.size() == 0)
		return;
	this->current = 0;
	Movie currentMovie = this->getCurrentMovie();
	currentMovie.play();
}

void WatchList::next()
{
	if (this->movies.size() == 0)
		return;
	this->current++;
	Movie currentMovie = this->getCurrentMovie();
	currentMovie.play();
}

bool WatchList::isEmpty()
{
	return this->movies.size() == 0;
}
