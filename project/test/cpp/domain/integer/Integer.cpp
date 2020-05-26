//
// Created by sechelea on 3/28/20.
//

#include "Integer.h"

Integer::Integer(int integer) {
    this->integer = integer;
}

Integer::Integer(const std::string& string) {
    this->integer = std::stoi(string);
}

int Integer::get() {
    return this->integer;
}

void Integer::set(int newInteger) {
    this->integer = newInteger;
}


std::string Integer::toHtmlTableHead(int depth) {
    std::string tabs;
    for(int index = 0; index < depth; index += 1) {
        tabs += "\t";
    }
    return tabs + "<tr>\n"
    "\t" + tabs + "<td>Integer</td>\n"
         + tabs + "</tr>\n";
}

std::string Integer::toHtmlTableRow(int depth) {
    std::string tabs;
    for(int index = 0; index < depth; index += 1) {
        tabs += "\t";
    }
    return tabs + "<tr>\n"
    "\t" + tabs + "<td>" + std::to_string(this->integer) + "</td>\n"
         + tabs + "</tr>\n";
}

std::string Integer::toString(std::string separator) {
    return std::to_string(this->integer);
}

Integer &Integer::operator=(const Integer &that) {
    if (this != &that) {
        this->integer = that.integer;
    }
    return *this;
}

bool Integer::operator==(const Integer &that) {
    return this->integer == that.integer;
}

bool Integer::operator!=(const Integer& that) {
    return this->integer != that.integer;
}

