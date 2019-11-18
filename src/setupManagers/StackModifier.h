#pragma once

#include <sys/resource.h>

namespace Setup
{
void resize_stack()
{
    const rlim_t new_stack_limit = 16 * 1024 * 1024; // 16 MB

    struct rlimit current_stack_size;
    int limit = getrlimit(RLIMIT_STACK, &current_stack_size);

    if (limit == 0) {
        if (current_stack_size.rlim_cur < new_stack_limit) {
            current_stack_size.rlim_cur = new_stack_limit;
            limit = setrlimit(RLIMIT_STACK, &current_stack_size);
            if (limit != 0) {
                fprintf(stderr, "setrlimit returned limit = %d\n", limit);
            }
        }
    }
}
}; // namespace Setup