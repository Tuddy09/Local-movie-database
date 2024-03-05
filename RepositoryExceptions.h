#pragma once
#include <exception>
#include <string>

class FileException : public std::exception
{
public:
	FileException(const std::string& msg) : message(msg) {}
	virtual const char* what();
protected:
	std::string message;

};
class RepositoryException : public std::exception
{
protected:
	std::string message;
public:
	RepositoryException();
	RepositoryException(const std::string& msg);
	virtual ~RepositoryException() {}
	virtual const char* what();

};
class DuplicateMovieException : public RepositoryException
{
	const char* what();
};