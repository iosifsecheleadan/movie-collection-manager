//
// Created by sechelea on 3/27/20.
//

#pragma once

#include <string>
#include <stdexcept>
#include "../main/MainException.h"

class ControllerException : public MainException {
public:
    explicit ControllerException(std::string message) {
        this->message = std::move(message);
    }

    virtual const char* what() const throw () {
        return this->message.c_str();
    }
};