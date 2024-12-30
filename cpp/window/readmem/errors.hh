#pragma once

#include <exception>
#include <string_view>

namespace thtool::readmem {

class GameNotStartError : public ::std::exception {
    ::std::string_view err_msg{"game not start(don't means touhou window not open)"};
public:
    GameNotStartError() = default;
    ~GameNotStartError() = default;

    const char* what() const noexcept override {
        return err_msg.data();
    }
};

}
