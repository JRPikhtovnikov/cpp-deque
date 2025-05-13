#pragma once

#include <deque>
#include <string>

struct Model {
    using Deque = std::deque<std::string>;
    Deque items;
    Deque::iterator iterator = items.begin();
};
