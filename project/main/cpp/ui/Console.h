//
// Created by sechelea on 3/27/20.
//

#pragma once

#include "UserInterface.h"
#include "../domain/entity/Movie.h"
#include "../ctrl/Controller.h"
#include "../ctrl/Administrator.h"

class Console : public UserInterface{
private:
    Administrator* admin;
    Controller<Movie>* user;
    std::string fileLocation;

public:
    Console() = default;

    explicit Console(Controller<Movie>* administrator, Controller<Movie>* user, std::string fileLocation);

    virtual ~Console();

    /**
     * Run the program.
     * Allow user to choose user or admin mode
     */
    void run() override;

private:

    /**
     * Allow admin to
     *      - add Movie
     *      - remove Movie
     *      - update Movie
     *      - print all Movies to console
     *      - open CSV or HTML formatted file
     */
    void runAdminMode();

    /**
     * Allow user to
     *      - add Movie
     *      - remove Movie
     *      - print all saved Movies to console
     *      - open CSV or HTML formatted file
     */
    void runUserMode();

    /**
     * Print a given message
     * Read user input from console
     * Return a movie
     * @param message string
     * @throws UserInterfaceException if invalid input
     */
    Movie readMovie(std::string message);

    /**
     * Add 10 basic movies to the admin database
     */
    void addHardcoded();

    /**
     * Run the add functionality for the User:
     *      - view Movies in one Genre one by one
     *      - for each Movie, you can open the Trailer in your Browser
     *      - for each Movie, you can add it to your WatchList
     */
    void userAdd();

    /**
     * Run the remove functionality for the User:
     *      - read a Movie to Remove
     *      - if Movie was enjoyed, increase likes
     */
    void userRemove();

    /**
     * Read all entities from file at given location from constructor
     */
    void loadFiles();

    /**
     * Save all data in CSV and HTML formatted files
     */
    void saveFiles();

    /**
     * Open storage file with given name
     */
    void openStorageFile(const std::string& file);

    /**
     * Open file at given location with xdg-open system call
     */
    void openWithDefault(std::string thing);
};

