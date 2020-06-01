//
// Created by sechelea on 5/29/20.
//

#pragma once

#include <map>
#include "project/main/cpp/repo/Repository.h"

template<typename Type>
class UndoRedoController {
private:
    std::vector<std::pair<std::string, Type>>* operations;
    // INDEX is always set to Next Operation (i.e. Next Operation to Add or Redo)
    int index;

public:
    UndoRedoController() {
        this->index = 0;
        this->operations = new std::vector<std::pair<std::string, Type>>();
    }

    void addOperation(const std::string& name, Type element) {
        // Delete all redo operations
        auto first = this->operations->begin();
        auto last = this->operations->begin() + this->index;
        this->operations = new std::vector<std::pair<std::string, Type>>(first, last);
        // Add new Operation
        auto newPair = new std::pair<std::string, Type>(name, element);
        this->operations->push_back(*newPair);
        this->index += 1;
    }

    std::pair<std::string, Type> undo() {
        if(this->index < 1) throw ControllerException("No more Undo Operations");
        this->index -= 1;
        return this->operations->at(this->index);
    }

    std::pair<std::string, Type> redo() {
        if(this->index >= this->operations->size()) throw ControllerException("No more Redo Operations");
        auto operation = this->operations->at(this->index);
        this->index += 1;
        return operation;
    }
};