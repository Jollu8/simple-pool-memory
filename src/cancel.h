#pragma once


#include "status.h"
#include "visibility.h"

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace arrow {
    class StopToken;

    struct StopSourceImpl;

    ///Experimental
    class ARROW_EXPORT StopSource {
    public:
        StopSource();

        ~StopSource();

        // Consumer API (the side that stops)
        void RequestStop();

        void RequestStop(Status error);

        void RequestStopFromSignal(int signum);

        StopToken Token();

        void Reset();

    protected:
        std::shared_ptr<StopSourceImpl> impl_;
    };

    class ARROW_EXPORT StopToken {
    public:
        StopToken() = default;

        explicit StopToken(std::shared_ptr<StopSourceImpl> impl) :
                impl_(std::move(impl)) {}

        static StopToken Unstoppable() { return {}; }

        Status Poll() const;

        bool IsStopRequested() const;

    protected:
        std::shared_ptr<StopSourceImpl> impl_;

    };
} // namespace arrow