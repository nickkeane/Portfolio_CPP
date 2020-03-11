#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace listlib {
    class ListLib {
        public:
            ListLib();
            ~ListLib();

        public:
            size_t size() const;
        
        public:
            void addTask(const string& task);
            string getTask(size_t idx) const;

        private:
            vector< string > this_tasks;
    };
}