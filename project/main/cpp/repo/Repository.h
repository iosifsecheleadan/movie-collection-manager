//
// Created by sechelea on 3/27/20.
//

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

template <typename Type>
class Repository {
public:
    Repository<Type>() = default;


    /**
     * Delete Collection and all other attributes of Repository.
     */
    virtual ~Repository<Type>() = default;

    /**
     * Load all elements in CVS format from input file stream
     * @param input file stream
     * @throws RepositoryException for duplicate elements
     * <br> ValidatorException for invalid line formatting
     */
    virtual void loadCSV(std::ifstream& input) = 0;

    /**
     * Write all elements in CVS format into output file stream
     * @param output file stream
     */
    virtual void saveCSV(std::ofstream& output) = 0;

    /**
     * Write all elements in HTML Table format into output file stream
     * @param output file stream
     */
    virtual void saveHTML(std::ofstream& output) = 0;

    /**
     * Add given element to Collection.
     * @param element - Type
     * @throws RepositoryException if element already exists
     */
    virtual void add(Type element) = 0;

    /**
     * Remove given element from Collection.
     * @param element - Type
     * @throws RepositoryException if element doesn't exist
     */
    virtual void remove(Type element) = 0;

    /**
     * Search for given element in Collection.
     * @param element - Type
     * @return bool
     *      true if found
     *      false otherwise
     */
    virtual bool has(Type element) = 0;

    /**
     * Return number of elements in Collection.
     * @return int
     */
    virtual int size() = 0;

    /**
     * Return element at given index in Collection
     * @param index - int
     * @return Type
     */
    virtual Type get(int index) = 0;

    /**
     * Return Collection as std::string.
     * @param separator - std::string
     * @return std::string
     *      separated by given string
     */
    virtual std::string toString(std::string separator = " ") = 0;
};
