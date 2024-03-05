#include "MovieValidator.h"

using namespace std;

MovieException::MovieException(std::vector<std::string> _errors) : errors{_errors}
{
}

std::vector<std::string> MovieException::getErrors() const
{
	return this->errors;
}

void MovieValidator::validate(const Movie& movie)
{
	vector<string> errors;
	if (movie.getTitle().size() < 3)
		errors.push_back("The title name cannot be less than 3 characters!\n");
	if (movie.getGenre().size() < 3)
		errors.push_back("The genre name cannot be less than 3 characters!\n");
	if (movie.getYearOfRelease() < 1900)
		errors.push_back("The year of release cannot be less than 1900!\n");
	if (movie.getNumberOfLikes() < 0)
		errors.push_back("The number of likes cannot be less than 0!\n");
	size_t posWww = movie.getTrailer().find("www");
	size_t posHttp = movie.getTrailer().find("http");
	if (posWww != 0 && posHttp != 0)
		errors.push_back("The trailer link must start with one of the following: \"www\" or \"http\"!\n");
	if (errors.size() > 0)
		throw MovieException(errors);

}
