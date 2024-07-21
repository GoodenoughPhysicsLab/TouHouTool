#include <exception>
#include "../../fast_io/fast_io_dsal/string_view.h"

namespace thtool::readmem {

class GameNotStartError : public ::std::exception {
    fast_io::string_view err_msg{"checking game NOT start(don't means touhou window not open)"};
public:
    GameNotStartError() = default;
    ~GameNotStartError() = default;

    const char* what() const noexcept override {
        return err_msg.data();
    }
};

}
