#include "ListLib.h"

namespace listlib {
    ListLib::ListLib() {

    }

    ListLib::~ListLib() {
        
    }

    size_t ListLib::size() const {
        return this_tasks.size();
    }

    void ListLib::addTask(const string& task) {
        this_tasks.push_back(task);
    }

    string ListLib::getTask(size_t idx) const {
        if (idx < this_tasks.size())
            return this_tasks[idx];
        else
            return "";    
    }
}