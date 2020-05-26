//
// Created by sechelea on 3/28/20.
//

#include <cassert>
#include "TestAdministrator.h"

TestAdministrator::~TestAdministrator() {
    delete this->administrator;
}

void TestAdministrator::testAll() {
    TestAdministrator* tests = new TestAdministrator();

    tests->testGetByGenre();
}

void TestAdministrator::testGetByGenre() {
    Repository<Movie>* repo = new DynamicVector<Movie>();
    Administrator* admin = new Administrator(new MovieValidator(), repo);
    this->administrator = (Administrator*) new Controller<Movie>(new MovieValidator(), repo);

    this->administrator->add(* new Movie("title", "genre", 0, 1, "https://trailer", "https://movie"));
    this->administrator->add(* new Movie("title2", "genre", 0, 1, "https://trailer", "https://movie"));
    this->administrator->add(* new Movie("title", "genre2", 0, 1, "https://trailer", "https://movie"));

    assert(this->administrator->getByGenre("").size() == 3);
    assert(this->administrator->getByGenre("empty").size() == 0);
    assert(this->administrator->getByGenre("genre").size() == 2);
    assert(this->administrator->getByGenre("genre2").size() == 1);

    delete this->administrator;
}
