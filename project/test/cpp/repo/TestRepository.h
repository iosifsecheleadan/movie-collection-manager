//
// Created by sechelea on 3/28/20.
//

#pragma once

#include "../../../main/cpp/repo/Repository.h"
#include "../domain/integer/Integer.h"

class TestRepository {
    Repository<Integer>* repository;

public:
    ~TestRepository();

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
