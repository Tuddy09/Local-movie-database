#pragma once
#include "service.h"
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <qwidget.h>

class GUI :
    public QWidget
{
    Q_OBJECT
private:
    Service service;
    void chooseBetweenCSVOrHTMLForSavingWatchlist();
public:
    GUI(const Service& service, QWidget* parent = 0) : service(service)
    {
        this->chooseBetweenCSVOrHTMLForSavingWatchlist();
        this->initGUI();
        this->populateList();
        this->connectSignalsAndSlots();
    }
    void initGUI();
private:
    void populateList();
    void connectSignalsAndSlots();
    void addMovie();
    void deleteMovie();
    void updateMovie();
    int getSelectedIndex() const;
    void listItemChanged();
    void populateAfterDelete(std::string title);
    QListWidget* movieList;
    QLineEdit* titleEdit;
    QLineEdit* genreEdit;
    QLineEdit* yearEdit;
    QLineEdit* likesEdit;
    QLineEdit* trailerEdit;
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    QListWidget* watchList;
    void populateWatchList();
    QPushButton* addToWatchListButton;
    QPushButton* playButton;
    void addToWatchList();
    void playMovie();
    QPushButton* filterButton;
    QLineEdit* filterEdit;
    void filterMoviesByGivenGender();
    QPushButton* removeFromWatchList;
    void removeMovieFromWatchList();
    QPushButton* openWatchList;
    void openWatchListFile();
    QPushButton* saveWatchList;
    void saveWatchListFile();
};