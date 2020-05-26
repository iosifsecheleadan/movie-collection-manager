//
// Created by sechelea on 3/28/20.
//

#pragma once

#include <string>

/**
 * For testing purposes : DynamicVector needs a type that has
 *      a toString function.
 *      assignment operator.
 *      equality and inequality operator.
 */

class Integer {
private:
    int integer;

public:
    Integer() = default;

    explicit Integer(const std::string& string);

    explicit Integer(int integer);

    ~Integer() = default;

    int get();

    void set(int newInteger);

    std::string toHtmlTableHead(int depth);

    std::string toHtmlTableRow(int depth);

    std::string toString(std::string separator = " ");

    Integer& operator=(const Integer& that);

    bool operator==(const Integer& that);

    bool operator!=(const Integer& that);
};