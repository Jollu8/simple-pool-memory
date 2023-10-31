#pragma once

#include <cstring>
#include <iostream>

enum class StatusCode {
    INVALID = -1,
    OK = 0,
    CANCELLED = 1,
    KEY_ERROR = 2
};

class Status {
public: // Constructors
    Status() : code_(StatusCode::OK) {}

    explicit Status(StatusCode code) : code_(code) {}

    Status(StatusCode code, const std::string &msg) :
            code_(code),
            msg_(msg) {}

public: // Methods
    StatusCode Code() const { return code_; }

    bool Ok() const { return code_ == StatusCode::OK; }

    static Status OK() { return Status(); }

    static Status Invalid(const std::string &msg) {
        return Status(StatusCode::INVALID, msg);
    }

    static Status Cancelled(const std::string &msg) {
        return Status(StatusCode::CANCELLED, msg);
    }

    static Status KeyError(const std::string &msg) {
        return Status(StatusCode::KEY_ERROR, msg);
    }


    std::string ToString() const {
        using namespace std::string_literals;
        std::string statusString;
        switch (code_) {
            case StatusCode::OK:
                statusString = "OK"s;
                break;
            case StatusCode::CANCELLED:
                statusString = "CANCELLED";
                break;
            default:
                statusString = "UNKNOWN";
                break;
        }
        if (!msg_.empty())statusString += ": "s + msg_;
        return statusString;
    }

    void Abort(const std::string &message) const {
        std::cerr << "-- Arrow Fatal Error --\n";
        if (!message.empty()) std::cerr << message << '\n';

        std::cerr << ToString() << std::endl;
        std::abort();
    }

private: // Fields
    StatusCode code_;
    std::string msg_;

};