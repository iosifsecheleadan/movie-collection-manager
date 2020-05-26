//
// Created by sechelea on 3/28/20.
//

#pragma once

#include "../../../../main/cpp/domain/entity/Movie.h"

class TestMovie {
private:
    Movie one;
    Movie two;
    Movie three;

public:
    ~TestMovie();

    static void testAll();

    void testDefaultConstructor();

    void testParametrizedConstructor();

    void testCsvFormatConstructor();

    void testCopyConstructor();

    void testDestructor();

    void testDefaultToString();

    void testSeparatorToString();

    void testToHtmlTableHead();

    void testToHtmlTableRow();

    void testGetGenre();

    void testGetLinkToTrailer();

    void testGetLinkToMovie();

    void testGetNoLikes();

    void testSetNoLikes();

    void testEquality();

    void testInequality();
};