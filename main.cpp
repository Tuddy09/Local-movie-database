#include "main.h"

void testAll()
{
	test_Service_ValidEntity_ReturnsTrue();
}

int main(int argc, char *argv[])
{
	//testAll();
	QApplication application(argc, argv);
    QFont font{ "Verdana", 10 };
    application.setFont(font);

    Repository repo("data.txt");

	FileWatchList* watchList = nullptr;
	Service service(repo, watchList, MovieValidator{});

	GUI gui{ service };
	gui.show();
	return application.exec();
	
}

