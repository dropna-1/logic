#ifndef SIDEKICK_HPP
#define SIDEKICK_HPP

#include "Character.hpp"

class SideKick : public Character
{
    public :
        SideKick(const std::string& name, int health, int movement) ;
        void printInfo() const ;
};

#endif 