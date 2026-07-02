#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream> 

class Character
{
    protected :
        std::string name ; 
        int maxHp ;
        int hp ; 
        int movement ; 
        int position ;

    public :
        Character(const std::string& name , int maxHP , int movement) ;
        
        virtual ~Character() = default ;

        void takeDamage(int) ; 
        void heal(int) ;
        bool isAlive() const ;
        int getPosition() const ;
        void setPosition(int) ;

        std::string getname() const ; 
        int getMaxhp() const ;
        int getHp() const ;
        int getMovement() const ;

        virtual void printInfo() const = 0 ;
};


#endif