#pragma once

#include <functional>
#include <set>

namespace EPX
{
    class BetterEvent
    {
    public:
        BetterEvent();
        void operator()() const;
        void operator+=(const std::function<void()>& callback);
        void operator-=(const std::function<void()>& callback);

    private:
        struct Comparator
        {
            bool operator()(const std::function<void()>& lhs, const std::function<void()>& rhs) const;
        };

        std::set<std::function<void()>, Comparator> _callbacks;
    };
}
