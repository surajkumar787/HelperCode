#include "betterevent.h"

namespace EPX
{
    BetterEvent::BetterEvent() = default;

    void BetterEvent::operator()() const
    {
        for (auto& callback : _callbacks)
        {
            callback();
        }
    }
    void BetterEvent::operator+=(const std::function<void()>& callback)
    {
        _callbacks.insert(callback);
    }
    void BetterEvent::operator-=(const std::function<void()>& callback)
    {
        _callbacks.erase(callback);
    }

    bool BetterEvent::Comparator::operator()(const std::function<void()>& lhs, const std::function<void()>& rhs) const
    {
        // Implement comparison logic here
        return lhs.target_type().hash_code() < rhs.target_type().hash_code();
    }
}
