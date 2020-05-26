//
// Created by sechelea on 3/28/20.
//

#include "TestRepository.h"

//
// Created by sechelea on 3/28/20.
//

#include <cassert>
#include "TestDynamicVector.h"


TestRepository::~TestRepository() {
    delete this->repository;
}

void TestRepository::testAll() {
    TestRepository* tests = new TestRepository();

    tests->testDefaultConstructor();
    tests->testParametrizedConstructor();

    tests->testDestructor();

    tests->testAdd();
    tests->testRemove();

    tests->testHas();
    tests->testSize();
    tests->testGet();

    tests->testToString();
}

void TestRepository::testDefaultConstructor() {
    delete this->repository;
    this->repository = new DynamicVector<Integer>();
    assert(this->repository->size() == 0);
}

void TestRepository::testParametrizedConstructor() {
    this->repository = new DynamicVector<Integer>(1);
    assert(this->repository->size() == 0);

    this->repository = new DynamicVector<Integer>(100);
    assert(this->repository->size() == 0);

    delete this->repository;
}

void TestRepository::testDestructor() {
    DynamicVector<Integer>* temp = new DynamicVector<Integer>();
    temp->add(* new Integer(1));

    this->repository = new DynamicVector<Integer>();
    this->repository->add(temp->get(0));

    delete this->repository;
    assert(temp->get(0).get() == 1);
}

void TestRepository::testAdd() {
    this->repository = new DynamicVector<Integer>();

    try { this->repository->add(* new Integer(0));
        this->repository->add(* new Integer(1));
        this->repository->add(* new Integer(2));
        this->repository->add(* new Integer(3));
        this->repository->add(* new Integer(4));
    } catch (RepositoryException& e){ assert(false); }

    assert(this->repository->get(0).get() == 0);
    assert(this->repository->get(1).get() == 1);
    assert(this->repository->get(2).get() == 2);
    assert(this->repository->get(3).get() == 3);
    assert(this->repository->get(4).get() == 4);

    assert(this->repository->size() == 5);

    delete this->repository;
}

void TestRepository::testRemove() {
    this->repository = new DynamicVector<Integer>();
    this->repository->add(* new Integer(0));
    this->repository->add(* new Integer(1));
    this->repository->add(* new Integer(2));
    this->repository->add(* new Integer(3));
    this->repository->add(* new Integer(4));

    assert(this->repository->size() == 5);

    try { this->repository->remove(*new Integer(5));
        assert(false);
    } catch (RepositoryException& e) {}
    try { this->repository->remove(*new Integer(3));
        this->repository->remove(*new Integer(0));
        this->repository->remove(*new Integer(2));
        this->repository->remove(*new Integer(4));
        this->repository->remove(*new Integer(1));
    } catch (RepositoryException& e) { assert(false); }

    assert(this->repository->size() == 0);
}

void TestRepository::testHas() {
    this->repository = new DynamicVector<Integer>();
    this->repository->add(* new Integer(0));
    this->repository->add(* new Integer(1));

    assert(this->repository->has(* new Integer(1)));
    assert(this->repository->has(* new Integer(0)));

    assert(not this->repository->has(* new Integer(2)));
    assert(not this->repository->has(* new Integer(3)));

    delete this->repository;
}

void TestRepository::testSize() {
    this->repository = new DynamicVector<Integer>();

    assert(this->repository->size() == 0);
    this->repository->add(* new Integer(0));
    assert(this->repository->size() == 1);
    this->repository->add(* new Integer(1));
    assert(this->repository->size() == 2);
    this->repository->add(* new Integer(2));
    assert(this->repository->size() == 3);
    this->repository->remove(* new Integer(0));
    assert(this->repository->size() == 2);
    this->repository->remove(* new Integer(2));
    assert(this->repository->size() == 1);
    this->repository->remove(* new Integer(1));
    assert(this->repository->size() == 0);

    delete this->repository;
}

void TestRepository::testGet() {
    this->repository = new DynamicVector<Integer>();

    for(int index = 0; index < 5; index += 1) {
        this->repository->add(* new Integer(index));
    }

    for(int index = 0; index < 5; index += 1) {
        assert(this->repository->get(index).get() == index);
    }

    delete this->repository;
}

void TestRepository::testToString() {
    this->repository = new DynamicVector<Integer>();

    for(int index = 0; index < 10; index += 1) {
        this->repository->add(* new Integer(index));
    }
    assert(this->repository->toString() == "0 1 2 3 4 5 6 7 8 9 ");
    assert(this->repository->toString(", ") == "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ");
    for(int index = 0; index < 10; index += 1) {
        this->repository->remove(* new Integer(index));
    }

    delete this->repository;
}
