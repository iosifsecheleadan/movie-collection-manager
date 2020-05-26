//
// Created by sechelea on 3/27/20.
//

#include "Movie.h"
#include "../validator/ValidatorException.h"

#include <utility>

Movie::~Movie() = default;

Movie::Movie(std::string title, std::string genre, int yearOfRelease, int noLikes,
             std::string linkToTrailer, std::string linkToMovie) {
    this->title = std::move(title);
    this->genre = std::move(genre);
    this->yearOfRelease = yearOfRelease;
    this->noLikes = noLikes;
    this->linkToTrailer = std::move(linkToTrailer);
    this->linkToMovie = std::move(linkToMovie);
}

Movie::Movie(const std::string& csvFormat) {
    std::stringstream split(csvFormat);
    std::vector<std::string> values;
    std::string value;
    while (std::getline(split, value, ',')) {
        values.push_back(value);
    }
    if(values.size() != 6) throw ValidatorException("String not formatted correctly");

    try {
        this->title = values[0];
        this->genre = values[1];
        this->yearOfRelease = std::stoi(values[2]);
        this->noLikes = std::stoi(values[3]);
        this->linkToTrailer = values[4];
        this->linkToMovie = values[5];
    } catch (...) { throw ValidatorException("String not formatted correctly"); }
}

Movie::Movie(const Movie& that) {
    this->title = that.title;
    this->genre = that.genre;
    this->yearOfRelease = that.yearOfRelease;
    this->noLikes = that.noLikes;
    this->linkToTrailer = that.linkToTrailer;
    this->linkToMovie = that.linkToMovie;
}

std::string Movie::toString() {
    return "\nTitle : " + this->title +
        "\nGenre : " + this->genre +
        "\nYear of Release : " + std::to_string(this->yearOfRelease) +
        "\nLikes : " + std::to_string(this->noLikes) +
        "\nTrailer : " + this->linkToTrailer +
        "\nMovie : " + this->linkToMovie;
}

std::string Movie::toString(const std::string&  separator) {
    return this->title + separator + this->genre + separator + std::to_string(this->yearOfRelease) + separator +
           std::to_string(this->noLikes) + separator + this->linkToTrailer + separator + this->linkToMovie;
}



std::string Movie::toHtmlTableHead(int depth) {
    std::string tabs;
    for(int index = 0; index < depth; index += 1) {
        tabs += "\t";
    }
    return tabs + "<tr>\n"
    "\t" + tabs + "<td>Title</td>\n"
    "\t" + tabs + "<td>Genre</td>\n"
    "\t" + tabs + "<td>Year of Release</td>\n"
    "\t" + tabs + "<td>Likes</td>\n"
    "\t" + tabs + "<td>Trailer</td>\n"
    "\t" + tabs + "<td>Movie</td>\n"
         + tabs + "</tr>\n";
}


std::string Movie::toHtmlTableRow(int depth) {
    std::string tabs;
    for(int index = 0; index < depth; index += 1) {
        tabs += "\t";
    }
    return tabs + "<tr>\n"
    "\t" + tabs + "<td>" + this->title + "</td>\n"
    "\t" + tabs + "<td>" + this->genre + "</td>\n"
    "\t" + tabs + "<td>" + std::to_string(this->yearOfRelease) + "</td>\n"
    "\t" + tabs + "<td>" + std::to_string(this->noLikes) + "</td>\n"
    "\t" + tabs + "<td> <a href=\"" + this->linkToTrailer + "\">Watch</a> </td>\n"
    "\t" + tabs + "<td> <a href=\"" + this->linkToMovie + "\">Stream</a> </td>\n"
         + tabs + "</tr>\n";
}

std::string Movie::getGenre() {
    return this->genre;
}

std::string Movie::getLinkToTrailer() {
    return this->linkToTrailer;
}

std::string Movie::getLinkToMovie() {
    return this->linkToMovie;
}

bool Movie::operator==(const Movie& that) {
    return this->yearOfRelease == that.yearOfRelease &&
            this->title == that.title &&
            this->genre == that.genre;
}

bool Movie::operator!=(const Movie& that) {
    return this->yearOfRelease != that.yearOfRelease || this->title != that.title ||
        this->genre != that.genre;
}

int Movie::getNoLikes() {
    return this->noLikes;
}

void Movie::setNoLikes(int newNoLikes) {
    this->noLikes = newNoLikes;
}





