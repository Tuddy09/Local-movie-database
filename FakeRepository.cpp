#include "FakeRepository.h"

int FakeRepository::findByTitle(std::string title)
{
	if(this->returnsBooleanValue)
			return 0;
	return -1;
}
