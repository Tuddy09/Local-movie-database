#pragma once
#include "repository.h"
#include "FileWatchList.h"
#include "MovieValidator.h"
#include <algorithm>
class Service {
private:
	Repository repo;
	MovieValidator validator;
public:
	FileWatchList* watchList;
	Service(const Repository& repo, FileWatchList* watchlist, MovieValidator validator) : repo{ repo }, watchList{ watchlist }, validator{ validator } {}
	std::vector<Movie> getAllService();
	WatchList* getWatchList() const { return watchList; }
	void addMovieToWatchList(const Movie& movie);
	std::vector<Movie> listMoviesByGenre(std::vector<Movie> validMovies, std::string givenGenre, std::vector<Movie> repo);
	bool deleteMovieFromWatchList(std::string title);
	int getSizeService();
	bool addService(std::string title, std::string genre, int yearOfRelease, int numberOfLikes, std::string trailer);
	bool removeService(std::string title);
	bool updateService(std::string newTitle, std::string newGenre, int newYearOfRelease, int newNumberOfLikes, std::string newTrailer);
	void updateLikesService(std::string title);
	void startWatchList();
	void playMovie();
	void nextMovieWatchList();
	void saveWatchList();
	void openWatchList() const;
	int GetIndexByTitle(std::string title);
	~Service();

};