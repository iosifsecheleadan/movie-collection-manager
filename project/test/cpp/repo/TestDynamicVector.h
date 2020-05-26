//
// Created by sechelea on 3/28/20.
//

#pragma once

#include "../../../main/cpp/repo/DynamicVector.h"
#include "../domain/integer/Integer.h"

class TestDynamicVector {
private:
    DynamicVector<Integer>* vector;

public:
    ~TestDynamicVector();

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
