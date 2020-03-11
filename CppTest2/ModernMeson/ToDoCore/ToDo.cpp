#include "ToDo.h"

ToDo::ToDo() {

}

ToDo::~ToDo() {
    
}

size_t ToDo::size() const {
    return this_tasks.size();
}

void ToDo::addTask(const string& task) {
    this_tasks.push_back(task);
}

string ToDo::getTask(size_t idx) const {
    if (idx < this_tasks.size())
        return this_tasks[idx];
    else
        return "";    
}