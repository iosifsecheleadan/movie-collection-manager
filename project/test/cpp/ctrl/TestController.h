//
// Created by sechelea on 3/28/20.
//

#pragma once

#include "../../../main/cpp/ctrl/Controller.h"
#include "../domain/integer/Integer.h"
#include "../domain/integer/IntegerValidator.h"

class TestController {
private:
    Controller<Integer>* controller;

public:

    ~TestController();

    static void testAll();

    void testDefaultConstructor();

    void testParametrizedConstructor();

    void testDestructor();

    void testAdd();

    void testRemove();

    void testUpdate();

    void testToString();

};


