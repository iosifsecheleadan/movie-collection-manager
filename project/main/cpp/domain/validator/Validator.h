//
// Created by sechelea on 4/25/20.
//

#pragma once

template <typename Type>
class Validator {
public:
    /**
     * Validates an element of generic type
     * @param entity given element
     * @throws ValidatorException if invalid
     */
    virtual void validate(Type entity) = 0;
};