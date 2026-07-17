#pragma once

enum HeroType
{
    Sherlock , 
    Dracula 
};

enum CardType
{
    Attack , 
    Defend , 
    Scheme ,
    Multiple 
};

enum class TriggerType
{
    Immediately,
    BeforeCombat,
    DuringCombat,
    AfterCombat
};

enum class FighterType
{
    Hero,
    Sidekick,
    Any
};

enum class AttackType
{
    Melee , 
    Ranged 
};