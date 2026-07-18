#pragma once

#include "IAbility.hpp"

class DraculaAbility : public IAbility
{
    public:
        void execute(Character*) override ;
        std::string getName() const override;
        std::string getDescription() const override;
};