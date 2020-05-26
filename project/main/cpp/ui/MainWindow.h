//
// Created by sechelea on 5/25/20.
//

#pragma once

#include <utility>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtCore/QStringListModel>
#include <QtWidgets/QMessageBox>
#include <project/main/cpp/domain/validator/ValidatorException.h>

#include "project/main/cpp/domain/entity/Movie.h"
#include "../ctrl/Administrator.h"
#include "UserInterfaceException.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
private:
    //                              OBJECTS

    Controller<Movie>* user;
    Administrator* admin;
    std::string fileLocation;

    QWidget* main;

    QGridLayout* gridLayout;

    QLabel* dataBaseLabel;
    QListView* dataBaseList;

    QLineEdit* addMovieEdit;
    QPushButton* addNewButton;
    QPushButton* removeButton;
    QPushButton* updateButton;
    QPushButton* adminOpenHTML;
    QPushButton* adminOpenCSV;
    QPushButton* watchTrailer;

    QLabel* watchListLabel;
    QListView* watchList;


    QLabel* searchMovieLabel;
    QLineEdit* searchMovieEdit;
    QPushButton* watchMovie;
    QPushButton* userOpenHTML;
    QPushButton* userOpenCSV;

    //                              UI SET UP

    void setUp() {
        this->main = new QWidget();
        this->gridLayout = new QGridLayout();

        this->setUpAdmin();
        this->setUpUser();

        this->main->setLayout(this->gridLayout);
        this->setCentralWidget(this->main);
    }

    void setUpUser() {
        this->watchListLabel = new QLabel("Move Watch List");
        this->watchList = new QListView();
        this->watchList->setEditTriggers(QAbstractItemView::NoEditTriggers);

        this->searchMovieLabel = new QLabel("Search Movies by Genre:");

        this->searchMovieEdit = new QLineEdit("Search");
        this->searchMovieEdit->setToolTip("Search Movies in Watch List and in Data Base By Genre");
        connect(searchMovieEdit, SIGNAL(textChanged(const QString&)), this, SLOT(searchByGenre(const QString&)));

        this->watchMovie = new QPushButton("Watch Movie");
        this->watchMovie->setToolTip("Open Selected Movie in new Tab\nDelete and Rate Selected Movie");
        connect(watchMovie, SIGNAL(released()), this, SLOT(watchSelectedMovie()));

        this->userOpenCSV = new QPushButton("Open CSV");
        this->userOpenCSV->setToolTip("Open Saved CSV File");
        connect(userOpenCSV, SIGNAL(released()), this, SLOT(openUserCSV()));

        this->userOpenHTML = new QPushButton("Open HTML");
        this->userOpenHTML->setToolTip("Open Saved HTML File");
        connect(userOpenHTML, SIGNAL(released()), this, SLOT(openUserHTML()));


        this->gridLayout->addWidget(this->watchListLabel, 0, 3, 1, 3);
        this->gridLayout->addWidget(this->watchList, 1, 3, 1, 3);

        this->gridLayout->addWidget(this->userOpenCSV, 2, 3);
        this->gridLayout->addWidget(this->userOpenHTML, 2, 4);
        this->gridLayout->addWidget(this->watchMovie, 2, 5);

        this->gridLayout->addWidget(this->searchMovieLabel, 3, 3, 1, 3);

        this->gridLayout->addWidget(this->searchMovieEdit, 4, 3, 1, 3);
    }

    void setUpAdmin() {
        this->dataBaseLabel = new QLabel("Movie Data Base");
        this->dataBaseList = new QListView();
        this->dataBaseList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->addMovieEdit = new QLineEdit("Input New Movie data");

        this->addNewButton = new QPushButton("Add");
        this->addNewButton->setToolTip("Add New Movie");
        connect(addNewButton, SIGNAL(released()), this, SLOT(addNewMovie()));

        this->removeButton = new QPushButton("Remove");
        this->removeButton->setToolTip("Remove Selected Movie");
        connect(removeButton, SIGNAL(released()), this, SLOT(removeSelectedMovie()));

        this->updateButton = new QPushButton("Update");
        this->updateButton->setToolTip("Update Selected Movie with New Movie");
        connect(updateButton, SIGNAL(released()), this, SLOT(updateSelectedMovie()));

        this->adminOpenCSV = new QPushButton("Open CSV");
        this->adminOpenCSV->setToolTip("Open Saved CSV File");
        connect(adminOpenCSV, SIGNAL(released()), this, SLOT(openAdminCSV()));

        this->adminOpenHTML = new QPushButton("Open HTML");
        this->adminOpenHTML->setToolTip("Open Saved HTML File");
        connect(adminOpenHTML, SIGNAL(released()), this, SLOT(openAdminHTML()));

        this->watchTrailer = new QPushButton("Watch Trailer");
        this->watchTrailer->setToolTip("Open Trailer of Selected Movie in new Tab");
        connect(watchTrailer, SIGNAL(released()), this, SLOT(watchSelectedTrailer()));

        this->gridLayout->addWidget(this->dataBaseLabel, 0, 0, 1, 3);
        this->gridLayout->addWidget(this->dataBaseList, 1, 0, 1, 3);

        this->gridLayout->addWidget(this->adminOpenCSV, 2, 0);
        this->gridLayout->addWidget(this->adminOpenHTML, 2, 1);
        this->gridLayout->addWidget(this->watchTrailer, 2, 2);

        this->gridLayout->addWidget(this->addNewButton, 3, 0);
        this->gridLayout->addWidget(this->removeButton, 3, 1);
        this->gridLayout->addWidget(this->updateButton, 3, 2);

        this->gridLayout->addWidget(this->addMovieEdit, 4, 0, 1, 3);
    }

    //                              LOAD AND SAVE FILES

    void loadFiles() {
        this->admin->loadCSV(this->fileLocation + "/admin.csv");
        this->user->loadCSV(this->fileLocation + "/user.csv");
    }

    void saveFiles() {
        this->admin->saveCSV(this->fileLocation + "/admin.csv");
        this->user->saveCSV(this->fileLocation + "/user.csv");

        this->admin->saveHTML(this->fileLocation + "/admin.html");
        this->user->saveHTML(this->fileLocation + "/user.html");
    }

    //                              REFRESH - load tables after add / remove / update

    void refreshTables() {
        this->refreshDataBase();
        this->refreshWatchList();
    }

    void refreshWatchList() {
        QStringListModel* model = new QStringListModel(this);
        QStringList stringList;
        for(int index = 0; index < this->user->size(); index += 1) {
            stringList.append(QString(
                    this->user->getToString(index)
                    .c_str()));
        }
        model->setStringList(stringList);
        this->watchList->setModel(model);
        this->watchList->update();
    }

    void refreshDataBase() {
        QStringListModel* model = new QStringListModel(this);
        QStringList stringList;
        for(int index = 0; index < this->admin->size(); index += 1) {
            stringList.append(QString(
                    this->admin->getToString(index)
                    .c_str()));
        }
        model->setStringList(stringList);
        this->dataBaseList->setModel(model);
        this->dataBaseList->update();
    }

    //                              MESSAGE BOXES

    void errorMessage(QString message) {
        QMessageBox box;
        message = "There has been an ERROR:\n\t" + message;
        box.critical(this, "Error", message);
        box.show();
    }

    void simpleMessage(const QString& message) {
        QMessageBox box;
        box.setWindowTitle("Message");
        box.setText(message);
        box.exec();
    }

    //                              FILTER

    void filterUser(const std::string& string) {
        QStringListModel* model = new QStringListModel(this);
        QStringList stringList;
        for(int index = 0; index < this->user->size(); index += 1) {
            Movie movie = this->user->get(index);
            if(movie.getGenre().find(string) != std::string::npos) {
                stringList.append(QString(
                        movie.toString(",")
                                .c_str()));
            }
        }
        model->setStringList(stringList);
        this->watchList->setModel(model);
        this->watchList->update();
    }

    void filterAdmin(const std::string& string) {
        QStringListModel* model = new QStringListModel(this);
        QStringList stringList;
        for(int index = 0; index < this->admin->size(); index += 1) {
            Movie movie = this->admin->get(index);
            if(movie.getGenre().find(string) != std::string::npos) {
                stringList.append(QString(
                        movie.toString(",")
                                .c_str()));
            }
        }
        model->setStringList(stringList);
        this->dataBaseList->setModel(model);
        this->dataBaseList->update();
    }

    //                              OTHER

    void closeEvent(QCloseEvent* event) override {
        this->saveFiles();
        QMainWindow::closeEvent(event);
    }

    static void openWithDefault(const std::string& thing) {
        system(("xdg-open " + thing).c_str());
    }

private slots:
    void addNewMovie() {
        std::string string = this->addMovieEdit->text().toStdString();
        try { Movie* movie = new Movie(string);
            this->admin->add(*movie);
            this->refreshDataBase();
        } catch (MainException& exception) { this->errorMessage(exception.what()); return;}
    }

    void removeSelectedMovie() {
        if(this->dataBaseList->selectionModel()->selectedIndexes().empty()) {
            this->errorMessage("Please Select a Movie from the Movie Data Base"); return;
        }
        QModelIndex index = this->dataBaseList->selectionModel()->selectedIndexes().first();
        std::string data = index.data().toString().toStdString();
        try { Movie *movie = new Movie(data);
            this->admin->remove(*movie);
            this->refreshDataBase();
        } catch (MainException& exception) { this->errorMessage(exception.what()); return; }
    }

    void updateSelectedMovie() {
        std::string string = this->addMovieEdit->text().toStdString();

        if(this->dataBaseList->selectionModel()->selectedIndexes().empty()) {
            this->errorMessage("Please Select a Movie from the Movie Data Base"); return;
        }
        QModelIndex index = this->dataBaseList->selectionModel()->selectedIndexes().first();
        std::string data = index.data().toString().toStdString();

        try { Movie* newMovie = new Movie(string);
            Movie* selected = new Movie(data);
            this->admin->update(*selected, *newMovie);
            this->refreshDataBase();
        } catch (MainException& exception) { this->errorMessage(exception.what());
        }
    }


    void openUserCSV() {
        this->saveFiles();
        openWithDefault(this->fileLocation + "/user.csv");
    }

    void openUserHTML() {
        this->saveFiles();
        openWithDefault(this->fileLocation + "/user.html");
    }

    void openAdminCSV() {
        openWithDefault(this->fileLocation + "/admin.csv");
        this->saveFiles();
    }

    void openAdminHTML() {
        this->saveFiles();
        openWithDefault(this->fileLocation + "/admin.html");
    }

    void searchByGenre(const QString& string) {
        this->filterUser(string.toStdString());
        this->filterAdmin(string.toStdString());
    }

    void watchSelectedTrailer() {
        if(this->dataBaseList->selectionModel()->selectedIndexes().empty()) {
            this->errorMessage("Please Select a Movie from the Movie Data Base"); return;
        }
        QModelIndex index = this->dataBaseList->selectionModel()->selectedIndexes().first();
        std::string data = index.data().toString().toStdString();

        try {
            Movie* movie = new Movie(data);
            this->openWithDefault(movie->getLinkToTrailer());

            if(askUserYesNo("Did you like the Trailer?",
                            "Would you like to save the Movie to your Watch List?")
                            == QMessageBox::Yes) {
                this->user->add(*movie);
                this->refreshWatchList();
            }
        } catch (MainException& exception) { this->errorMessage(exception.what()); return; }
    }

    void watchSelectedMovie() {
        if(this->watchList->selectionModel()->selectedIndexes().empty()) {
            this->errorMessage("Please Select a Movie from the Watch List");
        }
        QModelIndex index = this->watchList->selectionModel()->selectedIndexes().first();
        std::string data = index.data().toString().toStdString();
        try { Movie *movie = new Movie(data);
            this->openWithDefault(movie->getLinkToMovie());

            if (askUserYesNo("Did you like the Movie?",
                             "Would you like to give it a Like")
                == QMessageBox::Yes) {
                Movie *newMovie = new Movie(*movie);
                newMovie->setNoLikes(newMovie->getNoLikes() + 1);
                this->admin->update(*movie, *newMovie);
            }
            this->user->remove(*movie);
            this->refreshTables();
        } catch (MainException& exception) { this->errorMessage(exception.what()); return; }
    }

    static int askUserYesNo(const QString& question, const QString& details) {
        QMessageBox messageBox;
        messageBox.setText(question);
        messageBox.setInformativeText(details);
        messageBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        messageBox.setDefaultButton(QMessageBox::Yes);
        return messageBox.exec();
    }


public:
    MainWindow(Controller<Movie>* administrator, Controller<Movie>* user, std::string fileLocation) {
        this->admin = (Administrator *) administrator;
        this->user = user;
        this->fileLocation = std::move(fileLocation);

        this->setUp();
        this->loadFiles();
        this->refreshTables();
    }

    void run() {
        this->show();
    }
};
