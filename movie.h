#pragma once
#include <string>
#include <iostream>
#include <Windows.h>

class Movie {
private:
	std::string title;
	std::string genre;
	int yearOfRelease;
	int numberOfLikes;
	std::string trailer;
public:
	Movie(std::string title = "empty", std::string genre = "empty", int yearOfRelease = 0, int numberOfLikes = 0, std::string trailer = "empty");
	std::string getTitle() const;
	std::string getGenre() const;
	int getYearOfRelease() const;
	int getNumberOfLikes() const;
	std::string getTrailer() const;
	std::string toString() const;
	void play();
	friend std::istream& operator>>(std::istream& is, Movie& movie);
	friend std::ostream& operator<<(std::ostream& os, Movie& movie);
	~Movie();
};