//
// Created by sechelea on 3/28/20.
//

#include <cassert>
#include "TestInteger.h"

TestInteger::~TestInteger() {
    //delete &this->one;
    //delete &this->two;
}

void TestInteger::testAll() {
    TestInteger* tests = new TestInteger();

    tests->testDefaultConstructor();
    tests->testParametrizedConstructor();

    tests->testToString();
    tests->testToHtmlTableHead();
    tests->testToHtmlTableRow();

    tests->testAssignment();

    tests->testEquality();
    tests->testInequality();
}

void TestInteger::testDefaultConstructor() {
    one = * new Integer();
    two = * new Integer();

    assert(one.get() == 0);
    assert(two.get() == 0);
    assert(one.get() == two.get());
}

void TestInteger::testParametrizedConstructor() {
    one = * new Integer(50);
    two = * new Integer('2');

    assert(one.get() == 50);
    assert(two.get() == 50);
    assert(one.get() == two.get());

    two = * new Integer(50);
    assert(one.get() == '2');
    assert(two.get() == '2');
    assert(one.get() == two.get());
}


void TestInteger::testGet() {
    one = * new Integer(23456);
    two = * new Integer(0);

    assert(one.get() == 23456);
    assert(two.get() == 0);
}

void TestInteger::testSet() {
    one = * new Integer(23456);
    two = * new Integer(0);

    assert(one.get() != two.get());
    two.set(23456);
    assert(one.get() == two.get());
}

void TestInteger::testToString() {
    one = * new Integer(23456);
    two = * new Integer(0);

    assert(one.toString() == "23456");
    assert(one.toString() == one.toString("Whatever comes here cause it's neve used."));
    assert(two.toString() == "0");
    assert(two.toString() == two.toString("NULL (just to add to the confusion)"));
}

void TestInteger::testToHtmlTableHead() {
    one = * new Integer(23456);
    two = * new Integer(0);
    assert(one.toHtmlTableHead(0) != two.toHtmlTableHead(1));
    assert(one.toHtmlTableHead(1) != one.toHtmlTableHead(2));
    assert(one.toHtmlTableHead(2) == two.toHtmlTableHead(2));
    assert(one.toHtmlTableHead(0) == "<tr>\n\t<td>Integer</td>\n</tr>\n");
    assert(two.toHtmlTableHead(2) == "\t\t<tr>\n\t\t\t<td>Integer</td>\n\t\t</tr>\n");
}

void TestInteger::testToHtmlTableRow() {
    one = * new Integer(23456);
    two = * new Integer(0);
    assert(one.toHtmlTableRow(0) != two.toHtmlTableRow(0));
    assert(one.toHtmlTableRow(2) == one.toHtmlTableRow(2));
    assert(one.toHtmlTableRow(0) == "<tr>\n\t<td>23456</td>\n</tr>\n");
    assert(two.toHtmlTableRow(2) == "\t\t<tr>\n\t\t\t<td>0</td>\n\t\t</tr>\n");
}

void TestInteger::testAssignment() {
    one = * new Integer(23456);
    two = one;

    assert(one.get() == two.get());
    two.set(65432);
    assert(one.get() != two.get());
}

void TestInteger::testEquality() {
    one = * new Integer(23456);
    two = * new Integer(23456);
    assert(one == two);

    two = one;
    assert(one == two);

    one.set(23456);
    assert(one == two);
}

void TestInteger::testInequality() {
    one = * new Integer(23456);
    two = * new Integer();
    assert(one != two);

    two.set(65432);
    assert(one != two);
}

