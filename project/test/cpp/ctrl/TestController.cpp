//
// Created by sechelea on 3/28/20.
//

#include <cassert>
#include "TestController.h"
#include "../domain/integer/Integer.h"

TestController::~TestController() {
    delete this->controller;
}

void TestController::testAll() {
    TestController* tests = new TestController();

    tests->testDefaultConstructor();
    tests->testParametrizedConstructor();

    tests->testDestructor();

    tests->testAdd();
    tests->testRemove();
    tests->testUpdate();

    tests->testToString();
}

void TestController::testDefaultConstructor() {
    this->controller = new Controller<Integer>(new IntegerValidator());

    assert(this->controller->toString() == "\n");

    delete this->controller;
}

void TestController::testParametrizedConstructor() {
    Repository<Integer>* repo = new DynamicVector<Integer>();
    repo->add(* new Integer());
    this->controller = new Controller<Integer>(new IntegerValidator(), repo);

    assert(this->controller->toString() == "0\n\n");
    assert(this->controller->toString() == repo->toString("\n") + "\n");

    delete this->controller;
}

void TestController::testDestructor() {
    this->controller = new Controller<Integer>(new IntegerValidator());
    delete this->controller;

    Repository<Integer>* repo = new DynamicVector<Integer>(100);
    this->controller = new Controller<Integer>(new IntegerValidator(), repo);
    delete this->controller;
    // the deletion of repo is checked in TestRepository and TestDynamicVector
    // nothing much to test here
}

void TestController::testAdd() {
    this->controller = new Controller<Integer>(new IntegerValidator());
    this->controller->add(* new Integer());

    try {
        this->controller->add(* new Integer());
    } catch (RepositoryException& exception) {
        //std::cout << exception.what();
        std::string errorMessage = "Element already exists.";
        assert(exception.what() == errorMessage);
    }
    assert(this->controller->toString() == "0\n\n");

    delete this->controller;
}

void TestController::testRemove() {
    this->controller = new Controller<Integer>(new IntegerValidator());

    try {
        this->controller->remove(* new Integer());
    } catch (RepositoryException& exception)  {
        std::string errorMessage = "Element does not exist.";
        assert(exception.what() == errorMessage);
    }
    this->controller->add(* new Integer());
    this->controller->remove(* new Integer());
    assert(this->controller->toString() == "\n");

    delete this->controller;
}

void TestController::testUpdate() {
    Repository<Integer>* repo = new DynamicVector<Integer>();
    this->controller = new Controller<Integer>(new IntegerValidator(), repo);
    this->controller->add(* new Integer());
    this->controller->add(* new Integer(1));
    this->controller->add(* new Integer(2));

    try {
        this->controller->update(* new Integer(), * new Integer(1));
    } catch (ControllerException& exception) {
        std::string errorMessage = "Entity 1 already exists in the Repository.";
        assert(exception.what() == errorMessage);
        assert(repo->has(* new Integer()));
    }
    try {
        this->controller->update(* new Integer(5), * new Integer());
    } catch (ControllerException& exception) {
        std::string errorMessage = "Entity 5 does not exist in the Repository.";
        assert(exception.what() == errorMessage);
    }

    this->controller->update(* new Integer(), * new Integer());
    assert(repo->has(* new Integer()));
    this->controller->update(* new Integer(1), * new Integer(5));
    assert(repo->has(* new Integer(5)));
    assert(not repo->has(* new Integer(1)));

    delete this->controller;
}

void TestController::testToString() {
    this->controller = new Controller<Integer>(new IntegerValidator());

    this->controller->add(* new Integer());
    this->controller->add(* new Integer(1));
    this->controller->add(* new Integer(2));
    assert(this->controller->toString() == "0\n1\n2\n\n");

    delete this->controller;
}
