//
// Created by sechelea on 3/27/20.
//
#pragma once

#include "Repository.h"
#include "RepositoryException.h"

/**
 * For function specifications see Repository
 * @see Repository
 */
template <typename Type>
class DynamicVector : public Repository<Type>{
private:
    static const int minimalCapacity = 4;
    // golden ratio
    const double resizeFactor = 1.6180339;
    int capacity, length;
    Type* elements;

public:
    DynamicVector<Type>() {
       this->capacity = minimalCapacity;
       this->length = 0;
       this->elements = new Type[this->capacity];
    }

    explicit DynamicVector<Type>(int initialCapacity) {
        this->capacity = initialCapacity;
        this->length = 0;
        this->elements = new Type[this->capacity];
    }

    virtual ~DynamicVector<Type>() {
        delete[] this->elements;
    }

    void loadCSV(std::ifstream& input) override {
        std::string line;
        while(std::getline(input, line)) {
            Type* element = new Type(line);
            this->add(*element);
        }
    }

    void saveCSV(std::ofstream& output) override {
        for(int index = 0; index < this->length; index += 1) {
            output << this->elements[index].toString(",") << "\n";
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
        output << this->elements[0].toHtmlTableHead(1);
        for(int index = 0; index < this->length; index += 1) {
            output << this->elements[index].toHtmlTableRow(1);
        }
        output << "\t</table>\n"
                  "</body>\n"
                  "</html>";
    }

    void add(Type element) override {
        if(this->has(element)) throw RepositoryException("Element already exists.");
        this->elements[this->length] = element;
        this->length += 1;

        this->enlarge();
    }

    void remove(Type element) override {
        if(not this->has(element)) throw RepositoryException("Element does not exist.");
        bool found = false;
        for (int index = 0; index < this->length; index += 1) {
            if (!found && this->elements[index] == element) {
                found = true;
                this->length -= 1;
            }
            if (found) {
                this->elements[index] = this->elements[index + 1];
            }
        }
        this->shrink();
    }

    bool has(Type element) override {
        for(int index = 0; index < this->length; index += 1) {
            if (this->elements[index] == element) {
                return true;
            }
        }
        return false;
    }

    int size() override {
        return this->length;
    }

    Type get(int index) override {
        return this->elements[index];
    }

    std::string toString(std::string separator = " ") override {
        std::string string = "";
        for(int index = 0; index < this->length; index += 1) {
            string += this->elements[index].toString() + separator;
        }
        return string;
    }

private:
    /**
     * Allocate more space for the collection
     */
    void enlarge() {
        if(this->length >= this->capacity) {
            this->capacity = (int) (this->capacity * resizeFactor);

            Type *temp = new Type[this->capacity];
            for (int index = 0; index < this->length; index += 1) {
                temp[index] = this->elements[index];
            }
            delete[] this->elements;

            this->elements = temp;
        }
    }

    /**
     * Deallocate unused space in the collection
     */
    void shrink() {
        if(this->length * 4 < this->capacity &&
                this->capacity > 4 && this->length > 0) {
            this->capacity = (int) (this->capacity / resizeFactor);

            Type *temp = new Type[this->capacity];
            for (int index = 0; index < this->length; index += 1) {
                temp[index] = this->elements[index];
            }
            delete[] this->elements;

            this->elements = temp;
        }
    }
};
