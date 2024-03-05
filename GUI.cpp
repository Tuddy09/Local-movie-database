#include "GUI.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <qlabel.h>
#include <qmessagebox.h>
#include <vector>
#include <string>
#include "RepositoryExceptions.h"
#include "CSVWatchList.h"
#include "HTMLWatchList.h"

using std::string;
using std::vector;
void GUI::chooseBetweenCSVOrHTMLForSavingWatchlist()
{
	QMessageBox::StandardButtons reply = QMessageBox::Yes | QMessageBox::No;
	QMessageBox msgClose(QMessageBox::Question, "Save watchlist", "Do you want to save the watchlist in CSV or HTML format?", reply);
	msgClose.setButtonText(QMessageBox::Yes, "CSV");
	msgClose.setButtonText(QMessageBox::No, "HTML");
	if (msgClose.exec() == QMessageBox::Yes)
	{
		this->service.watchList = new CSVWatchList{ "watchlist.csv" };
	}
	else
	{
		this->service.watchList = new HTMLWatchList{ "watchlist.html" };
	}
}
void GUI::initGUI()
{
	QHBoxLayout* mainLayout = new QHBoxLayout{ this };
	QWidget* leftWidget = new QWidget{};
	QVBoxLayout* leftSide = new QVBoxLayout{ leftWidget };
	this->movieList = new QListWidget{};
	leftSide->addWidget(this->movieList);
	QWidget* middleWidget = new QWidget{};
	QFormLayout* middleSide = new QFormLayout{ middleWidget };
	this->titleEdit = new QLineEdit{};
	this->genreEdit = new QLineEdit{};
	this->yearEdit = new QLineEdit{};
	this->likesEdit = new QLineEdit{};
	this->trailerEdit = new QLineEdit{};
	middleSide->addRow("Title", this->titleEdit);
	middleSide->addRow("Genre", this->genreEdit);
	middleSide->addRow("Year", this->yearEdit);
	middleSide->addRow("Likes", this->likesEdit);
	middleSide->addRow("Trailer", this->trailerEdit);
	QWidget* buttonsWidget = new QWidget{};
	QHBoxLayout* buttonsLayout = new QHBoxLayout{ buttonsWidget };
	this->addButton = new QPushButton{ "Add" };
	this->deleteButton = new QPushButton{ "Delete" };
	this->updateButton = new QPushButton{ "Update" };
	buttonsLayout->addWidget(this->addButton);
	buttonsLayout->addWidget(this->deleteButton);
	buttonsLayout->addWidget(this->updateButton);
	leftSide->addWidget(buttonsWidget);
	mainLayout->addWidget(leftWidget);
	mainLayout->addWidget(middleWidget);
	QWidget* rightWidget = new QWidget{};
	QVBoxLayout* rightSide = new QVBoxLayout{ rightWidget };
	this->watchList = new QListWidget{};
	rightSide->addWidget(this->watchList);
	QWidget* watchListButtonsWidget = new QWidget{};
	QHBoxLayout* watchListButtonsLayout = new QHBoxLayout{ watchListButtonsWidget };
	this->addToWatchListButton = new QPushButton{ "Add" };
	this->playButton = new QPushButton{ "Play" };
	watchListButtonsLayout->addWidget(this->addToWatchListButton);
	watchListButtonsLayout->addWidget(this->playButton);
	rightSide->addWidget(watchListButtonsWidget);
	QWidget* filterWidget = new QWidget{};
	QVBoxLayout* filterLayout = new QVBoxLayout{ filterWidget };
	this->filterEdit = new QLineEdit{};
	this->filterButton = new QPushButton{ "Filter" };
	filterLayout->addWidget(this->filterEdit);
	filterLayout->addWidget(this->filterButton);
	rightSide->addWidget(filterWidget);
	mainLayout->addWidget(rightWidget);
	QWidget* removeWidget = new QWidget{};
	QVBoxLayout* removeLayout = new QVBoxLayout{ removeWidget };
	this->removeFromWatchList = new QPushButton{ "Remove" };
	removeLayout->addWidget(this->removeFromWatchList);
	rightSide->addWidget(removeWidget);
	QWidget* openWidget = new QWidget{};
	QVBoxLayout* openLayout = new QVBoxLayout{ openWidget };
	this->openWatchList = new QPushButton{ "Open" };
	openLayout->addWidget(this->openWatchList);
	rightSide->addWidget(openWidget);
	QWidget* saveWidget = new QWidget{};
	QVBoxLayout* saveLayout = new QVBoxLayout{ saveWidget };
	this->saveWatchList = new QPushButton{ "Save" };
	saveLayout->addWidget(this->saveWatchList);
	rightSide->addWidget(saveWidget);
}


void GUI::populateList()
{
	movieList->clear();
	vector<Movie> movies = this->service.getAllService();
	for (auto movie : movies)
		movieList->addItem(QString::fromStdString(movie.toString()));
	movieList->setCurrentRow(0);
}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(this->movieList, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->getSelectedIndex();
		if (selectedIndex < 0)
			return;
		Movie movie = this->service.getAllService()[selectedIndex];
		this->titleEdit->setText(QString::fromStdString(movie.getTitle()));
		this->genreEdit->setText(QString::fromStdString(movie.getGenre()));
		this->yearEdit->setText(QString::fromStdString(std::to_string(movie.getYearOfRelease())));
		this->likesEdit->setText(QString::fromStdString(std::to_string(movie.getNumberOfLikes())));
		this->trailerEdit->setText(QString::fromStdString(movie.getTrailer()));
		});
	QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addMovie);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deleteMovie);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateMovie);
	QObject::connect(this->addToWatchListButton, &QPushButton::clicked, this, &GUI::addToWatchList);
	QObject::connect(this->playButton, &QPushButton::clicked, this, &GUI::playMovie);
	QObject::connect(this->filterButton, &QPushButton::clicked, this, &GUI::filterMoviesByGivenGender);
	QObject::connect(this->removeFromWatchList, &QPushButton::clicked, this, &GUI::removeMovieFromWatchList);
	QObject::connect(this->openWatchList, &QPushButton::clicked, this, &GUI::openWatchListFile);
	QObject::connect(this->saveWatchList, &QPushButton::clicked, this, &GUI::saveWatchListFile);
}

void GUI::addMovie()
{
	string title = this->titleEdit->text().toStdString();
	string genre = this->genreEdit->text().toStdString();
	int year = this->yearEdit->text().toInt();
	int likes = this->likesEdit->text().toInt();
	string trailer = this->trailerEdit->text().toStdString();
	try {
		this->service.addService(title, genre, year, likes, trailer);
		this->populateList();
	}
	catch (RepositoryException& exception) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
	catch (FileException& exception) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
	catch (MovieException& exception) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.getErrors()[0]));
	}
	
}

void GUI::deleteMovie()
{
	string title = this->titleEdit->text().toStdString();
	try {
		this->populateAfterDelete(title);
	}
	catch (RepositoryException& exception) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
	catch (FileException& exception) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
	catch (MovieException& exception) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.getErrors()[0]));
	}
}

void GUI::updateMovie()
{
	string title = this->titleEdit->text().toStdString();
	string genre = this->genreEdit->text().toStdString();
	int year = this->yearEdit->text().toInt();
	int likes = this->likesEdit->text().toInt();
	string trailer = this->trailerEdit->text().toStdString();
	try {
		this->service.updateService(title, genre, year, likes, trailer);
		this->populateList();
	}
	catch (RepositoryException& exception) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
	catch (FileException& exception) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.what()));
	}
	catch (MovieException& exception) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exception.getErrors()[0]));
	}
}

int GUI::getSelectedIndex() const
{
	int currentRow = movieList->currentRow();
	return currentRow;
}

void GUI::listItemChanged()
{
	int index = this->getSelectedIndex();
	if(index <0)
		return;
	Movie movie = this->service.getAllService()[index];
	this->titleEdit->setText(QString::fromStdString(movie.getTitle()));
	this->genreEdit->setText(QString::fromStdString(movie.getGenre()));
	this->yearEdit->setText(QString::fromStdString(std::to_string(movie.getYearOfRelease())));
	this->likesEdit->setText(QString::fromStdString(std::to_string(movie.getNumberOfLikes())));
	this->trailerEdit->setText(QString::fromStdString(movie.getTrailer()));

}

void GUI::populateAfterDelete(std::string title)
{
	movieList->clear();
	this->service.removeService(title);
	vector<Movie> movies = this->service.getAllService();
	for (auto movie : movies)
		movieList->addItem(QString::fromStdString(movie.toString()));
	movieList->setCurrentRow(0);
}

void GUI::populateWatchList()
{
	watchList->clear();
	auto watchlist = this->service.getWatchList();
	auto movies = watchlist->getAllWatchList();
	for (auto movie : movies)
		watchList->addItem(QString::fromStdString(movie.toString()));
	watchList->setCurrentRow(0);
}

void GUI::addToWatchList()
{
	int index = this->getSelectedIndex();
	if (index < 0)
		return;
	std::string title = this->titleEdit->text().toStdString();
	int indexOfMovie = this->service.GetIndexByTitle(title);
	Movie movie = this->service.getAllService()[indexOfMovie];
	this->service.addMovieToWatchList(movie);
	this->populateWatchList();
}

void GUI::playMovie()
{
	int index = this->getSelectedIndex();
	if (index < 0)
		return;
	std::string title = this->titleEdit->text().toStdString();
	int indexOfMovie = this->service.GetIndexByTitle(title);
	Movie movie = this->service.getAllService()[indexOfMovie];
	movie.play();
}

void GUI::filterMoviesByGivenGender()
{
	string genre = this->filterEdit->text().toStdString();
	if (genre == "")
	{
		this->populateList();
		return;
	}
	movieList->clear();
	vector<Movie> movies(this->service.getAllService().size());
	movies = this->service.listMoviesByGenre(movies, genre, this->service.getAllService());
	for (auto movie : movies)
		movieList->addItem(QString::fromStdString(movie.toString()));
	movieList->setCurrentRow(0);
}

void GUI::removeMovieFromWatchList()
{
	int index = this->getSelectedIndex();
	if (index < 0)
		return;
	Movie movie = this->service.getAllService()[index];
	//pop up window to ask if the user liked the movie
	QWidget* window = new QWidget;
	QMessageBox::StandardButton reply = QMessageBox::question(window, "Question", "Did you like the movie?", QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes)
		this->service.updateLikesService(movie.getTitle());
	this->service.deleteMovieFromWatchList(movie.getTitle());
	this->populateList();
	this->populateWatchList();
}

void GUI::openWatchListFile()
{
	this->service.openWatchList();
}

void GUI::saveWatchListFile()
{
	QMessageBox::StandardButton reply = QMessageBox::question(this, "Question", "Do you want to save the watchlist?", QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes)
		this->service.saveWatchList();
}
