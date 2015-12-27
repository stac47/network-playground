#include <memory>
#include <utility>

namespace np {
namespace tools {

template<typename T, typename... Args>
std::shared_ptr<T> make_shared_from_protected_ctor(Args && ... args)
{
    struct make_shared_enabler : public T
    {
        explicit make_shared_enabler(Args && ... args)
          : T(std::forward<Args>(args)...) {}
    };
    return std::make_shared<make_shared_enabler>(std::forward<Args>(args)...);
}

} // namespace tools
} // namespace np
