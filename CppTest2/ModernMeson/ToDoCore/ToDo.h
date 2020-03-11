//#pragma once
#ifndef TODO_H
#define TODO_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class ToDo {
    public:
        ToDo();
        ~ToDo();

    public:
        size_t size() const;
    
    public:
        void addTask(const string& task);
        string getTask(size_t idx) const;

    private:
        vector< string > this_tasks;
};

#endif