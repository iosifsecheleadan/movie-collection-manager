//
// Created by sechelea on 3/28/20.
//

#pragma once

#include "Integer.h"

class TestInteger {
private:
    Integer one;
    Integer two;

public:
    ~TestInteger();

    static void testAll();

    void testDefaultConstructor();

    void testParametrizedConstructor();

    void testGet();

    void testSet();

    void testToString();

    void testToHtmlTableHead();

    void testToHtmlTableRow();

    void testAssignment();

    void testEquality();

    void testInequality();
};
