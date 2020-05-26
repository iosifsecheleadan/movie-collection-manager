//
// Created by sechelea on 4/27/20.
//

#pragma once

#include "../../../../main/cpp/domain/entity/Movie.h"
#include "../../../../main/cpp/domain/validator/Validator.h"

class TestMovieValidator {
private:
    Validator<Movie>* validator;

public:
    static void testAll();

    void testValidate();
};


