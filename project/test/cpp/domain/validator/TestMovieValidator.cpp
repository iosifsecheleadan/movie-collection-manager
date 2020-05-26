//
// Created by sechelea on 4/27/20.
//

#include <cassert>
#include "TestMovieValidator.h"
#include "../../../../main/cpp/domain/validator/MovieValidator.h"


void TestMovieValidator::testAll() {
    TestMovieValidator* tests = new TestMovieValidator();

    tests->testValidate();
}

void TestMovieValidator::testValidate() {
    this->validator = new MovieValidator();
    Movie* movie = new Movie("title", "genre", -34, -1, "trailer", "movie");
    try { this->validator->validate(*movie); assert(false);
    } catch (ValidatorException& e) {
        std::string errorMessage = "Number of likes for Movie cannot be negative";
        assert(e.what() == errorMessage);
    }
    movie = new Movie("title", "genre", -77, 0, "trailer", "movie");
    try { this->validator->validate(*movie); assert(false);
    } catch (ValidatorException& e) {
        std::string errorMessage = "Link to Trailer of Movie doesn't start with \"https://\"";
        assert(e.what() == errorMessage);
    }
    movie = new Movie("title", "genre", -77, 0, "https://trailer", "movie");
    try { this->validator->validate(*movie); assert(false);
    } catch (ValidatorException& e) {
        std::string errorMessage = "Link to Movie of Movie doesn't start with \"https://\"";
        assert(e.what() == errorMessage);
    }
    movie = new Movie("title", "genre", -77, 0, "https://trailer", "https://movie");
    this->validator->validate(*movie);
}
