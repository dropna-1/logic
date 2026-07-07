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
    Versalite
};

enum class TriggerType
{
    Immediately,
    BeforeCombat,
    DuringCombat,
    AfterCombat , 
    None 
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

enum class EffectTarget
{
    currentPlayer , 
    EnemyPlayer ,
    FriendlyHero , 
    FriendlySidekicks , 
    FriendlyCharacters , 
    EnemyHero , 
    EenmySidekicks , 
    EnemyCharacters ,
    Attacker , 
    Defender ,
    None
};