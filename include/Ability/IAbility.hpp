#pragma once

#include <iostream>

class IAbility
{
    public:
        virtual ~IAbility() = default;
        virtual std::string getName() const = 0;
        virtual std::string getDescription() const = 0;
};