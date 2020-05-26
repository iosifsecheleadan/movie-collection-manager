//
// Created by sechelea on 3/27/20.
//

#include <iostream>

#include "Console.h"
#include "../ctrl/Administrator.h"
#include "UserInterfaceException.h"

Console::Console(Controller<Movie>* administrator, Controller<Movie>* user, std::string fileLocation) {
    this->admin = (Administrator *) administrator;
    this->user = user;
    this->fileLocation = fileLocation;
}

Console::~Console() {
    delete this->admin;
    delete this->user;
}

void Console::run() {
    try {
        this->loadFiles();
    } catch (MainException& e) { std::cout << e.what(); return; }
    std::string userInput;
    while (true) {
        std::cout << "[ root ] Please choose user mode [admin | user | exit] : \n";
        std::getline(std::cin, userInput);
        if (userInput == "admin") {
            this->runAdminMode();
        } else if (userInput == "user") {
            this->runUserMode();
        } else if (userInput == "exit") {
            this->saveFiles();
            break;
        } else {
            std::cout << "Wrong input. Please try again.\n";
        }
    }
}

void Console::runAdminMode() {
    std::string userInput;
    while (true) {
        try {
            std::cout << "[ admin ] Please give command [add | remove | update | print | open | exit]\n";
            std::getline(std::cin, userInput);
            if (userInput == "add") {
                this->admin->add(this->readMovie("add"));
            } else if (userInput == "remove") {
                this->admin->remove(this->readMovie("remove"));
            } else if (userInput == "update") {
                this->admin->update(this->readMovie("update"),
                                    this->readMovie("update with"));
            } else if (userInput == "print") {
                std::cout << this->admin->toString();
            } else if (userInput == "open") {
                this->openStorageFile("admin");
            }else if (userInput == "exit") {
                break;
            } else {
                std::cout << "Wrong input. Please try again.\n";
            }
        } catch (MainException& exception) {
            std::cout << exception.what() << "\n";
        }
    }
}

void Console::runUserMode() {
    std::string userInput;
    while (true) {
        try {
            std::cout << "[ user ] Please give command [add | remove | print | open | exit]\n";
            std::cin >> userInput;
            std::cin.clear(); std::cin.ignore();
            if (userInput == "add") {
                this->userAdd();
            } else if (userInput =="remove") {
                this->userRemove();
            } else if(userInput == "print") {
                std::cout << this->user->toString();
            } else if (userInput == "open") {
                this->openStorageFile("user");
            } else if (userInput == "exit") {
                break;
            } else {
                std::cout << "Wrong input. Please try again.\n";
            }
        } catch (MainException& exception) {
            std::cout << exception.what() << "\n";
        }
    }
}

void Console::userAdd() {
    std::string userInput;
    std::cout << "What genre are you interested in today?\n";
    std::getline(std::cin, userInput);
    for(Movie current : this->admin->getByGenre(userInput)) {
        std::cout << current.toString()
            << "\nOpen Trailer in browser? [y | n]";
        std::cin >> userInput;
        if (userInput == "y") {
            this->openWithDefault(current.getLinkToTrailer());
        }
        std::cout << "\nWould you like to add this movie to your watchlist? [y | n]";
        std::cin >> userInput;
        if (userInput == "y") {
            this->user->add(current);
        }
    }
    std::cin.clear(); std::cin.ignore();
}

void Console::userRemove() {
    Movie movie = this->readMovie("remove");
    this->user->remove(movie);
    std::string userInput;
    std::cout << "Did you enjoy this movie? [y | n ]\n";
    std::cin >> userInput;
    if (userInput == "y") {
        Movie* newMovie = new Movie(movie);
        newMovie->setNoLikes(newMovie->getNoLikes() + 1);
        this->admin->update(movie, *newMovie);
        std::cout << "Liked movie!\n";
    }
}

void Console::openStorageFile(const std::string& file) {
    std::string userInput;
    std::cout << "What file do you want to view ? [html | csv]\n";
    std::getline(std::cin, userInput);
    this->saveFiles();
    if(userInput == "html") {
        this->openWithDefault(this->fileLocation + "/" + file + ".html");
    } else if (userInput == "csv") {
        this->openWithDefault(this->fileLocation + "/" + file + ".txt");
    } else {
        std::cout << "Wrong input. Please try again.\n";
    }
}

Movie Console::readMovie(std::string message) {
    std::cout << "\tPlease give movie to " << message << ":\n[title | genre | year of release | number of likes | trailer link | movie link]\n";
    std::string title, genre, year, likes, linkToTrailer, linkToMovie;
    int yearOfRelease, noLikes;


    std::getline(std::cin, title);
    std::getline(std::cin, genre);
    std::getline(std::cin, year);
    std::getline(std::cin, likes);
    std::getline(std::cin, linkToTrailer);
    std::getline(std::cin, linkToMovie);
    try{
        yearOfRelease = std::stoi(year);
        noLikes = std::stoi(likes);
    } catch (std::invalid_argument exception) {
        throw UserInterfaceException();
    }

    return * new Movie(title, genre, yearOfRelease, noLikes, linkToTrailer, linkToMovie);
}

void Console::addHardcoded() {
    this->admin->add(* new Movie("Number 1", "1st", 2001, 2001, "https://link.com", "https://link.com"));
    this->admin->add(* new Movie("Number 2", "2nd", 2002, 2002, "https://link.com", "https://link.com"));
    this->admin->add(* new Movie("Number 3", "3rd", 2003, 2003, "https://link.com", "https://link.com"));
    this->admin->add(* new Movie("Number 4", "4th", 2004, 2004, "https://link.com", "https://link.com"));
    this->admin->add(* new Movie("Number 5", "1st", 2005, 2005, "https://link.com", "https://link.com"));
    this->admin->add(* new Movie("Number 6", "2nd", 2006, 2006, "https://link.com", "https://link.com"));
    this->admin->add(* new Movie("Number 7", "3rd", 2007, 2007, "https://link.com", "https://link.com"));
    this->admin->add(* new Movie("Number 8", "1st", 2008, 2008, "https://link.com", "https://link.com"));
    this->admin->add(* new Movie("Number 9", "2nd", 2009, 2009, "https://link.com", "https://link.com"));
    this->admin->add(* new Movie("Number 10", "1st", 2010, 2010, "https://link.com", "https://link.com"));
}

void Console::loadFiles() {
    this->user->loadCSV(this->fileLocation + "/user.csv");
    this->admin->loadCSV(this->fileLocation + "/admin.csv");
}

void Console::saveFiles() {
    this->user->saveCSV(this->fileLocation + "/user.csv");
    this->admin->saveCSV(this->fileLocation + "/admin.csv");
    this->user->saveHTML(this->fileLocation + "/user.html");
    this->admin->saveHTML(this->fileLocation + "/admin.html");
}

void Console::openWithDefault(std::string thing) {
    system(("xdg-open " + thing).c_str());
}
