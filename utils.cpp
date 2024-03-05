#include "utils.h"
#include <sstream>
#include <vector>


std::vector<std::string> tokenize(std::string str, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);
	return result;
}
