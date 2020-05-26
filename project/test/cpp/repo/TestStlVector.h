//
// Created by sechelea on 4/25/20.
//


#pragma once

#include "../../../main/cpp/repo/StlVector.h"
#include "../domain/integer/Integer.h"

class TestStlVector {
private:
    StlVector<Integer>* vector;

public:
    ~TestStlVector();

    static void testAll();

    void testDefaultConstructor();

    void testParametrizedConstructor();

    void testDestructor();

    void testAdd();

    void testRemove();

    void testHas();

    void testSize();

    void testGet();

    void testToString();
};
