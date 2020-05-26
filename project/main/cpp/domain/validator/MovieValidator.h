//
// Created by sechelea on 4/25/20.
//

#ifndef MOVIEDB_MOVIEVALIDATOR_H
#define MOVIEDB_MOVIEVALIDATOR_H


#include "../entity/Movie.h"
#include "Validator.h"
#include "ValidatorException.h"

class MovieValidator:
        public Validator<Movie>{
    void validate(Movie entity) override {
        if (entity.getNoLikes() < 0) {
            throw ValidatorException("Number of likes for Movie cannot be negative");
        } if (entity.getLinkToTrailer().rfind("https://", 0) != 0) {
            throw ValidatorException("Link to Trailer of Movie doesn't start with \"https://\"");
        } if (entity.getLinkToMovie().rfind("https://", 0) != 0) {
            throw ValidatorException("Link to Movie of Movie doesn't start with \"https://\"");
        }
    };
};


#endif //MOVIEDB_MOVIEVALIDATOR_H
