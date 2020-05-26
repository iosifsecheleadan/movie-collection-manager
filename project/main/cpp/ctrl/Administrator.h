//
// Created by sechelea on 3/27/20.
//

#pragma once

#include  "../domain/entity/Movie.h"
#include "../repo/Repository.h"
#include "Controller.h"

class Administrator : public Controller<Movie>{
public:
    Administrator();

    Administrator(Validator<Movie>* validator) : Controller(validator) {}

    explicit Administrator(Validator<Movie>* validator, Repository<Movie>* repo) :
                Controller(validator, repo) {}

    /**
     * Return all movies with given genre in a new vector.
     * If string is empty return all movies
     * @param genre - string
     * @return vector
     */
    std::vector<Movie> getByGenre(const std::string& genre) {
        std::vector<Movie>* movies = new std::vector<Movie>();
        for(int index = 0; index < this->repository->size(); index +=1) {
            Movie current = this->repository->get(index);
            if (genre.empty() || current.getGenre() == genre) {
                movies->push_back(this->repository->get(index));
            }
        }
        return *movies;
    }
};
