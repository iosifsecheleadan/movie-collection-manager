//
// Created by sechelea on 4/25/20.
//

#pragma once

#include <string>
#include <stdexcept>

/**
 * Base exception class for whole project
 */
class MainException : public std::exception {
protected:
    std::string message;

public:
    MainException() = default;

    explicit MainException(std::string message) {
        this->message = std::move(message);
    }

    virtual const char* what() const throw () {
        return this->message.c_str();
    }
};