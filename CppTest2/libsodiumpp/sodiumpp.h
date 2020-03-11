#pragma once

#include <string>

namespace sodiumpp {
    class SodiumContext {
        public:
            typedef void (OnMisuse)(void);

        public:
            static SodiumContext* instance();

        public:
            int SetMisuseHandler(OnMisuse fnMisuseHandler);
            void Misuse();

        private:
            SodiumContext();
            SodiumContext(SodiumContext const& rhs);
            SodiumContext& operator=(SodiumContext const& rhs);
        public:
            ~SodiumContext();
    };  
}