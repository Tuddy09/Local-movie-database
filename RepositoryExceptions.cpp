#include "RepositoryExceptions.h"

RepositoryException::RepositoryException() : exception(), message("")
{
}

RepositoryException::RepositoryException(const std::string& message) : message(message)
{
}
const char* RepositoryException::what()
{
	return this->message.c_str();
}

const char* FileException::what()
{
	return this->message.c_str();
}

const char* DuplicateMovieException::what()
{
	return "There is another movie with the same title and release year!";
}
