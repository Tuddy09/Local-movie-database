#pragma once
#include "repository.h"

class FakeRepository : public Repository
{
public:
	bool returnsBooleanValue;
	FakeRepository() : Repository{ "data.txt" } {}
	~FakeRepository() {}
	int findByTitle(std::string title) override;
};