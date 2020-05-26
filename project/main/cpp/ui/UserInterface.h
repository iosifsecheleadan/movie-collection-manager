//
// Created by sechelea on 3/27/20.
//

#pragma once

class UserInterface {
public:
    UserInterface() = default;

    virtual ~UserInterface() = default;

    /**
     * Run the program.
     */
    virtual void run() = 0;
};