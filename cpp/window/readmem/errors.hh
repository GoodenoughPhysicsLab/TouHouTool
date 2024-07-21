#include <exception>
#include "../../fast_io/fast_io_dsal/string_view.h"

namespace thtool::readmem {

class GameNotStartError : public ::std::exception {
    fast_io::string_view err_msg;
public:
    GameNotStartError(fast_io::string_view msg) {
        this->err_msg = msg;
    }

    ~GameNotStartError() = default;

    const char* what() const noexcept override {
        return err_msg.data();
    }
};

}
