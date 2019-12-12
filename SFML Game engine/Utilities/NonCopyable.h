#pragma once

struct NonCopyable
{
    NonCopyable() = default;
    NonCopyable &operator = (const NonCopyable &other) = delete;
    NonCopyable(const NonCopyable &other) = delete;
};
