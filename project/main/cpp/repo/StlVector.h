//
// Created by sechelea on 4/25/20.
//

#pragma once

#include "Repository.h"
#include "RepositoryException.h"

template <typename Type>
class StlVector : public Repository<Type> {
private:
    std::vector<Type>* elements;

public:
    StlVector<Type>() {
        this->elements = new std::vector<Type>();
    }

    /**
     * For backwards compatibility
     */
    explicit StlVector<Type>(int initialCapacity) {
        this->elements = new std::vector<Type>();
    }

    virtual ~StlVector<Type>() {
        delete this->elements;
    }

    void loadCSV(std::ifstream& input) override {
        std::string line;
        while(std::getline(input, line)) {
            Type* element = new Type(line);
            this->add(*element);
        }
    }

    void saveCSV(std::ofstream& output) override {
        for(auto current = this->elements->begin();
                current != this->elements->end(); ++ current) {
            output << (*current).toString(",") << "\n";
        }
    }

    void saveHTML(std::ofstream &output) override {
        output << "<!doctype html>\n"
                  "<html>\n"
                  "<head>\n"
                  "\t<title>StlVector</title>\n"
                  "</head>\n"
                  "<body>\n"
                  "\t<table border=\"1\">\n";
        output << (*this->elements->begin()).toHtmlTableHead(1);
        for(auto current = this->elements->begin();
                current != this->elements->end(); ++ current) {
            output << (*current).toHtmlTableRow(1);
        }
        output << "\t</table>\n"
                  "</body>\n"
                  "</html>";
    }

    void add(Type element) override {
        if(this->has(element)) throw RepositoryException("Element already exists.");
        this->elements->push_back(element);
    }

    void remove(Type element) override {
        if(not this->has(element)) throw RepositoryException("Element does not exist.");
        int index = 0;
        for(auto current = this->elements->begin();
                current != this->elements->end(); ++current) {
            if(*current == element) break;
            index += 1;
        }
        this->elements->erase(this->elements->begin() + index);
    }

    bool has(Type element) override {
        for(auto current = this->elements->begin();
                current != this->elements->end(); ++ current) {
            if (*current == element) {
                return true;
            }
        }
        return false;
    }

    int size() override {
        return this->elements->size();
    }

    Type get(int index) override {
        return this->elements->at(index);
    }

    std::string toString(std::string separator = " ") override {
        std::string string = "";
        for(auto current = this->elements->begin();
                current != this->elements->end(); ++ current) {
            string += (*current).toString() + separator;
        }
        return string;
    }
};