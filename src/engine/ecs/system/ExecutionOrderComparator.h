#pragma once

struct ExecutionOrderComparator {
    template<typename T>
    inline bool operator()(const T& l, const T& r) const
    {
        if (l.second->get_priority() != r.second->get_priority())

            return l.second->get_priority() < r.second->get_priority();

        return l.first < r.first;
    }
};