#include "tests.h"
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

void test_Service_ValidEntity_ReturnsTrue()
{
	FakeRepository fakeRepository = FakeRepository();
	fakeRepository.returnsBooleanValue = true;

	Service service(fakeRepository, nullptr, {});
	assert(service.addService("title", "genre", 2000, 100, "www.yt.com") == true);
}
