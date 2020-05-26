//
// Created by sechelea on 3/28/20.
//

#include <cassert>
#include "TestDynamicVector.h"


TestDynamicVector::~TestDynamicVector() {
    delete this->vector;
}

void TestDynamicVector::testAll() {
    TestDynamicVector* tests = new TestDynamicVector();

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

void TestDynamicVector::testDefaultConstructor() {
    this->vector = new DynamicVector<Integer>();
    assert(this->vector->size() == 0);
}

void TestDynamicVector::testParametrizedConstructor() {
    this->vector = new DynamicVector<Integer>(1);
    assert(this->vector->size() == 0);

    this->vector = new DynamicVector<Integer>(100);
    assert(this->vector->size() == 0);

    delete this->vector;
}

void TestDynamicVector::testDestructor() {
    DynamicVector<Integer>* temp = new DynamicVector<Integer>();
    temp->add(* new Integer(1));

    this->vector = new DynamicVector<Integer>();
    this->vector->add(temp->get(0));

    delete this->vector;
    assert(temp->get(0).get() == 1);
}

void TestDynamicVector::testAdd() {
    this->vector = new DynamicVector<Integer>();

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

void TestDynamicVector::testRemove() {
    this->vector = new DynamicVector<Integer>();
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

void TestDynamicVector::testHas() {
    this->vector = new DynamicVector<Integer>();
    this->vector->add(* new Integer(0));
    this->vector->add(* new Integer(1));

    assert(this->vector->has(* new Integer(1)));
    assert(this->vector->has(* new Integer(0)));

    assert(not this->vector->has(* new Integer(2)));
    assert(not this->vector->has(* new Integer(3)));

    delete this->vector;
}

void TestDynamicVector::testSize() {
    this->vector = new DynamicVector<Integer>();

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

void TestDynamicVector::testGet() {
    this->vector = new DynamicVector<Integer>();

    for(int index = 0; index < 5; index += 1) {
        this->vector->add(* new Integer(index));
    }

    for(int index = 0; index < 5; index += 1) {
        assert(this->vector->get(index).get() == index);
    }

    delete this->vector;
}

void TestDynamicVector::testToString() {
    this->vector = new DynamicVector<Integer>();

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
