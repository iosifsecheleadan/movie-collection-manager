//
// Created by sechelea on 3/28/20.
//

#pragma once

#include "../../../main/cpp/ctrl/Administrator.h"
#include "../domain/integer/Integer.h"
#include "../domain/integer/IntegerValidator.h"
#include "../../../main/cpp/domain/validator/MovieValidator.h"

class TestAdministrator {
private:
    Administrator* administrator;

public:
    ~TestAdministrator();

    static void testAll();

    void testGetByGenre();
};
