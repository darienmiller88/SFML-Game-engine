#pragma once
#include "NonCopyable.h"

struct NonMovable
{
    NonMovable() = default;
    NonMovable &operator = (NonCopyable &&other) = delete;
    NonMovable(NonCopyable &&other) = delete;
};
