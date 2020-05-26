//
// Created by sechelea on 3/27/20.
//

#pragma once

#include <string>
#include <stdexcept>

class UserInterfaceException : public MainException {
public:
    explicit UserInterfaceException(std::string message) {
        this->message = std::move(message);
    }

    virtual const char* what() const throw () {
        return this->message.c_str();
    }

    UserInterfaceException() {
        this->message = "Wrong Input. Please try again.";
    }
};

