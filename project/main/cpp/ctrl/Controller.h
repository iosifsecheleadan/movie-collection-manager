//
// Created by sechelea on 3/27/20.
//

#pragma once

#include "../repo/Repository.h"
#include "ControllerException.h"
#include "../repo/DynamicVector.h"
#include "../domain/validator/Validator.h"

template <typename Type>
class Controller{
protected:
    Repository<Type>* repository;
    Validator<Type>* validator;

public:
    Controller<Type>(Validator<Type>* validator) {
        this->repository = new DynamicVector<Type>();
        this->validator = validator;
    }

    explicit Controller(Validator<Type>* validator, Repository<Type>* repo){
        this->repository = repo;
        this->validator = validator;
    };

    ~Controller() {
        delete this->repository;
    };

    /**
     * Load all data from CSV formatted file at given location
     * @param location string
     * @throws RepositoryException for duplicate elements
     * <br> ValidatorException for invalid line formatting
     */
    void loadCSV(std::string location) {
        std::ifstream in(location);
        this->repository->loadCSV(in);
        in.close();
    }

    /**
     * Save all data in CSV format in file at given location
     * @param location string
     */
    void saveCSV(std::string location) {
        std::ofstream out(location);
        this->repository->saveCSV(out);
        out.close();
    }

    /**
     * Save all data in HTML Table format in file at given location
     * @param location string
     */
    void saveHTML(std::string location) {
        std::ofstream out(location);
        this->repository->saveHTML(out);
        out.close();
    }

    /**
     * Add given element to repository
     * @param element
     * @throws RepositoryException if element is a duplicate
     * <br> ValidatorException if element is invalid
     */
    void add(Type element) {
        this->validator->validate(element);
        this->repository->add(element);
    }

    /**
     * Remove given element from repository
     * @param element
     * @throws RepositoryException if element is not present
     */
    void remove(Type element) {
        this->repository->remove(element);
    }

    /**
     * Remove oldElement and add newElement
     * @param oldElement
     * @param newElement
     * @throws ControllerException if oldElement is not present
     * or if newElement is a duplicate
     */
    void update(Type oldElement, Type newElement) {
        this->validator->validate(newElement);

        if (this->repository->has(oldElement)) {
            this->repository->remove(oldElement);

            if (this->repository->has(newElement)) {
                this->repository->add(oldElement);
                throw ControllerException("Entity " + newElement.toString(", ") + " already exists in the Repository.");
            } else {
                this->repository->add(newElement);
            }
        } else {
            throw ControllerException("Entity " + oldElement.toString(", ") + " does not exist in the Repository.");
        }
    }

    int size() {
        return this->repository->size();
    }


    std::string getToString(int index) {
        return this->repository->get(index).toString(",");
    }

    /**
     * Return string containing all repository elements on new lines
     */
    std::string toString() {
        return this->repository->toString("\n") + "\n";
    }

    Type get(int index) {
        return this->repository->get(index);
    }
};
