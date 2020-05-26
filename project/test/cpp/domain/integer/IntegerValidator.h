//
// Created by sechelea on 4/25/20.
//

#pragma once

#include "Integer.h"
#include "../../../../main/cpp/domain/validator/Validator.h"

class IntegerValidator : public Validator<Integer> {
    void validate(Integer) override {}
};