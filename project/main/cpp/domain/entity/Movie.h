//
// Created by sechelea on 3/27/20.
//
#pragma once

#include <string>
#include <sstream>
#include <vector>

class Movie {
private:
    std::string title;
    std::string genre;
    int yearOfRelease;
    int noLikes;
    std::string linkToTrailer;
    std::string linkToMovie;

public :
    Movie() = default;

    explicit Movie(std::string title, std::string genre, int yearOfRelease, int noLikes,
          std::string linkToTrailer, std::string linkToMovie);

    /**
     * Construct movie from Comma Separated Values Line
     * @param csvFormat String
     * @throws ValidatorException if string is not formatted correctly
     */
    explicit Movie(const std::string& csvFormat);

    Movie(const Movie& that);

    ~Movie();

    /**
     * Return Movie data formatted for print.
     * @return string
     */
    std::string toString();

    /**
     * Return Movie data separated by given string.
     * @param separator - string
     * @return string
     */
    std::string toString(const std::string& separator);

    /**
     * Return an HTML Table Head corresponding to Movie type
     * @param depth depth of table row (i.e. number of tabs)
     */
    std::string toHtmlTableHead(int depth);

    /**
     * Return an HTML Table Row containing Movie data
     * @param depth depth of table row (i.e. number of tabs)
     */
    std::string toHtmlTableRow(int depth);

    /**
     * Return Movie Genre.
     * @return string
     */
    std::string getGenre();

    /**
     * Return Movie Link to Trailer.
     * @return string
     */
    std::string getLinkToTrailer();

    /**
     * Return Movie Link to Movie.
     * @return string
     */
    std::string getLinkToMovie();

    /**
     * Return Movie number of Likes
     * @return int
     */
    int getNoLikes();

    /**
     * Set Movie number of Likes
     * @param newNoLikes - int
     */
    void setNoLikes(int newNoLikes);

    /**
     * Compare two Movies by
     *      Year of Release, Title and Genre
     * @param that - Movie
     * @return bool
     *      true if Year of Release, Title and Genre are the same
     *      false otherwise
     */
    bool operator==(const Movie& that);

    /**
     * Compare two Movies by
     *      Year of Release, Title and Genre
     * @param that - Movie
     * @return bool
     *      true if Year of Release, Title or Genre are the different
     *      false otherwise
     */
    bool operator!=(const Movie& that);
};

