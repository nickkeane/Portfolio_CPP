#include "sodiumpp.h"

#include <exception>
#include <memory>
#include <sodium.h>

namespace sodiumpp {
    static std::unique_ptr<SodiumContext> gSC = nullptr;

    SodiumContext* SodiumContext::instance() {
        if (gSC == nullptr) {
            if (sodium_init() < 0)
                throw std::runtime_error("Sodium library not properly initialized");
            gSC.reset(new SodiumContext());
        }
        return gSC.get();
    }

    int SodiumContext::SetMisuseHandler(OnMisuse fnMisuseHandler) {
        return sodium_set_misuse_handler(fnMisuseHandler);
    }

    void SodiumContext::Misuse() {
        sodium_misuse();
    }

    SodiumContext::SodiumContext() {

    }

    SodiumContext::SodiumContext(SodiumContext const& /*rhs*/) {

    }

    SodiumContext::~SodiumContext() {

    }

    SodiumContext& SodiumContext::operator=(SodiumContext const& /*rhs*/) {
        return *this;
    }    
}