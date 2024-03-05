#include "service.h"

std::vector<Movie> Service::getAllService()
{
	return this->repo.getAllRepo();
}

void Service::addMovieToWatchList(const Movie& movie)
{
	if (this->watchList == nullptr)
		return;
	this->watchList->add(movie);
}

std::vector<Movie> Service::listMoviesByGenre(std::vector<Movie> validMovies, std::string givenGenre, std::vector<Movie> repo)
{
	int counter = 0;
	auto iterator = std::copy_if(repo.begin(), repo.end(), validMovies.begin(), [&givenGenre, &counter](Movie& object) {if (object.getGenre() == givenGenre) { counter++; return true; } });
	validMovies.resize(counter);
	return validMovies;
}

bool Service::deleteMovieFromWatchList(std::string title)
{
	if (this->watchList == nullptr)
		return false;
	int index = this->watchList->findByTitle(title);
	if (index != -1) {
		this->watchList->remove(index);
		return true;
	}
	return false;
}

int Service::getSizeService()
{
	return this->repo.getSizeRepo();
}

bool Service::addService(std::string title, std::string genre, int yearOfRelease, int numberOfLikes, std::string trailer)
{
	Movie movie = Movie(title, genre, yearOfRelease, numberOfLikes, trailer);
	this->validator.validate(movie);
	if (this->repo.findByTitle(title) == -1) {
		this->repo.addRepo(movie);
		return true;
	}
	this->repo.addRepo(movie);
	return false;
}

bool Service::removeService(std::string title)
{
	int index = this->repo.findByTitle(title);
	if (index == -1)
		return false;
	else {
		this->repo.removeRepo(index);
	}
	return true;
}

bool Service::updateService(std::string newTitle, std::string newGenre, int newYearOfRelease, int newNumberOfLikes, std::string newTrailer)
{
	int index = this->repo.findByTitle(newTitle);
	if (index == -1)
		return false;
	Movie newMovie = Movie(newTitle, newGenre, newYearOfRelease, newNumberOfLikes, newTrailer);
	this->validator.validate(newMovie);
	this->repo.updateRepo(index, newMovie);
	return true;
}

void Service::updateLikesService(std::string title)
{
	int index = this->repo.findByTitle(title);
	Movie newMovie = Movie(title, this->repo.getAllRepo()[index].getGenre(), this->repo.getAllRepo()[index].getYearOfRelease(), this->repo.getAllRepo()[index].getNumberOfLikes() + 1, this->repo.getAllRepo()[index].getTitle());
	this->repo.updateRepo(index, newMovie);
}

void Service::startWatchList()
{
	if(this->watchList == nullptr)
		return;
	this->watchList->play();
}

void Service::playMovie()
{
	if (this->watchList == nullptr)
		return;
	this->watchList->play();
}

void Service::nextMovieWatchList()
{
	if (this->watchList == nullptr)
		return;
	this->watchList->next();
}

void Service::saveWatchList()
{
	if (this->watchList == nullptr)
		return;
	this->watchList->writeToFile();
}

void Service::openWatchList() const
{
	if (this->watchList == nullptr)
		return;
	this->watchList->displayWatchList();
}

int Service::GetIndexByTitle(std::string title)
{
	return this->repo.findByTitle(title);
}

Service::~Service() {

}