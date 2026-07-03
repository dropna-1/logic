#pragma once

#include "IAbility.hpp"

class DraculaAbility : public IAbility
{
    public:
        std::string getName() const override;
        std::string getDescription() const override;
};