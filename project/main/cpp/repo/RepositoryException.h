//
// Created by sechelea on 4/25/20.
//

#pragma once

#include <string>
#include <stdexcept>
#include "../main/MainException.h"

class RepositoryException : public MainException {
public:
    explicit RepositoryException(std::string message) {
        this->message = std::move(message);
    }

    virtual const char* what() const throw () {
        return this->message.c_str();
    }
};