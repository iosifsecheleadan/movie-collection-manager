//
// Created by sechelea on 4/25/20.
//

#include <cassert>
#include "TestStlVector.h"
#include "../../../main/cpp/repo/RepositoryException.h"

TestStlVector::~TestStlVector() {
    delete this->vector;
}

void TestStlVector::testAll() {
    TestStlVector* tests = new TestStlVector();

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

void TestStlVector::testDefaultConstructor() {
    this->vector = new StlVector<Integer>();
    assert(this->vector->size() == 0);
}

void TestStlVector::testParametrizedConstructor() {
    this->vector = new StlVector<Integer>(1);
    assert(this->vector->size() == 0);

    this->vector = new StlVector<Integer>(100);
    assert(this->vector->size() == 0);

    delete this->vector;
}

void TestStlVector::testDestructor() {
    StlVector<Integer>* temp = new StlVector<Integer>();
    temp->add(* new Integer(1));

    this->vector = new StlVector<Integer>();
    this->vector->add(temp->get(0));

    delete this->vector;
    assert(temp->get(0).get() == 1);
}

void TestStlVector::testAdd() {
    this->vector = new StlVector<Integer>();

    try { this->vector->add(* new Integer(0));
        this->vector->add(* new Integer(1));
        this->vector->add(* new Integer(2));
        this->vector->add(* new Integer(3));
        this->vector->add(* new Integer(4));
    } catch (RepositoryException& e){ assert(false); }

    assert(this->vector->get(0).get() == 0);
    assert(this->vector->get(1).get() == 1);
    assert(this->vector->get(2).get() == 2);
    assert(this->vector->get(3).get() == 3);
    assert(this->vector->get(4).get() == 4);

    assert(this->vector->size() == 5);

    delete this->vector;
}

void TestStlVector::testRemove() {
    this->vector = new StlVector<Integer>();
    this->vector->add(* new Integer(0));
    this->vector->add(* new Integer(1));
    this->vector->add(* new Integer(2));
    this->vector->add(* new Integer(3));
    this->vector->add(* new Integer(4));

    assert(this->vector->size() == 5);


    try { this->vector->remove(*new Integer(5));
        assert(false);
    } catch (RepositoryException& e) {}
    try { this->vector->remove(*new Integer(3));
        this->vector->remove(*new Integer(0));
        this->vector->remove(*new Integer(2));
        this->vector->remove(*new Integer(4));
        this->vector->remove(*new Integer(1));
    } catch (RepositoryException& e) { assert(false); }

    assert(this->vector->size() == 0);
}

void TestStlVector::testHas() {
    this->vector = new StlVector<Integer>();
    this->vector->add(* new Integer(0));
    this->vector->add(* new Integer(1));

    assert(this->vector->has(* new Integer(1)));
    assert(this->vector->has(* new Integer(0)));

    assert(not this->vector->has(* new Integer(2)));
    assert(not this->vector->has(* new Integer(3)));

    delete this->vector;
}

void TestStlVector::testSize() {
    this->vector = new StlVector<Integer>();

    assert(this->vector->size() == 0);
    this->vector->add(* new Integer(0));
    assert(this->vector->size() == 1);
    this->vector->add(* new Integer(1));
    assert(this->vector->size() == 2);
    this->vector->add(* new Integer(2));
    assert(this->vector->size() == 3);
    this->vector->remove(* new Integer(0));
    assert(this->vector->size() == 2);
    this->vector->remove(* new Integer(2));
    assert(this->vector->size() == 1);
    this->vector->remove(* new Integer(1));
    assert(this->vector->size() == 0);

    delete this->vector;
}

void TestStlVector::testGet() {
    this->vector = new StlVector<Integer>();

    for(int index = 0; index < 5; index += 1) {
        this->vector->add(* new Integer(index));
    }

    for(int index = 0; index < 5; index += 1) {
        assert(this->vector->get(index).get() == index);
    }

    delete this->vector;
}

void TestStlVector::testToString() {
    this->vector = new StlVector<Integer>();

    for(int index = 0; index < 10; index += 1) {
        this->vector->add(* new Integer(index));
    }
    assert(this->vector->toString() == "0 1 2 3 4 5 6 7 8 9 ");
    assert(this->vector->toString(", ") == "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ");
    for(int index = 0; index < 10; index += 1) {
        this->vector->remove(* new Integer(index));
    }

    delete this->vector;
}
