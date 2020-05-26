//
// Created by sechelea on 4/25/20.
//


#pragma once

#include <string>
#include <stdexcept>
#include "../../main/MainException.h"

class ValidatorException : public MainException {
public:
    explicit ValidatorException(std::string message) {
        this->message = std::move(message);
    }

    virtual const char* what() const throw () {
        return this->message.c_str();
    }
};