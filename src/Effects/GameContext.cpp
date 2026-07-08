#include "Effects/GameContext.hpp"
using namespace std ;

GameContext::GameContext(Player* currentPlayer, Player* enemyPlayer, Character* attacker , Character* defender , Board* board) :
    currentPlayer(currentPlayer) , enemyPlayer(enemyPlayer) , attacker(attacker) , defender(defender) , board(board)
{
}

Player* GameContext::getCurrentPlayer() const
{
    return currentPlayer ;
}

Player* GameContext::getEnemyPlayer() const
{
    return enemyPlayer ;
}

Character* GameContext::getAttacker() const
{
    return attacker ;
}

Character* GameContext::getDefender() const
{
    return defender ;
}

Board* GameContext::getBoard() const
{
    return board ;
}

vector<Character*> GameContext::getTargets(EffectTarget target)
{
    switch(target)
    {
        case EffectTarget::FriendlyHero :
        {
            return {currentPlayer->getHero().get()};
        }
        case EffectTarget::EnemyHero :
        {
            return {enemyPlayer->getHero().get()} ;
        }
        case EffectTarget::FriendlySidekicks :
        {
            vector<Character*> result ;
            for(auto& sidekick : currentPlayer->getHero()->getSidekicks())
            {
                result.push_back(sidekick.get()) ;
            }
            return result ;
        }
        case EffectTarget::EenmySidekicks :
        {
            vector<Character*> result ;
            for(auto& sidekick : enemyPlayer->getHero()->getSidekicks())
            {
                result.push_back(sidekick.get()) ;
            }
            return result ;
        }
        case EffectTarget::FriendlyCharacters:
        {
            return currentPlayer->getAllCharacters();
        }
        case EffectTarget::EnemyCharacters:
        {
            return enemyPlayer->getAllCharacters();
        }
        case EffectTarget::Attacker:
        {
            return { attacker };
        }
        case EffectTarget::Defender:
        {
            return { defender };
        }
        default:
        {
            return {};
        }
    }
}

std::vector<Character*> GameContext::resolve(ConditionTarget target) const
{
    switch(target)
    {
        case ConditionTarget::FriendlyHero :
        {
            return {currentPlayer->getHero().get()};
        }
        case ConditionTarget::EnemyHero :
        {
            return {enemyPlayer->getHero().get()} ;
        }
        case ConditionTarget::FriendlySidekicks :
        {
            vector<Character*> result ;
            for(auto& sidekick : currentPlayer->getHero()->getSidekicks())
            {
                result.push_back(sidekick.get()) ;
            }
            return result ;
        }
        case ConditionTarget::EnemySidekicks :
        {
            vector<Character*> result ;
            for(auto& sidekick : enemyPlayer->getHero()->getSidekicks())
            {
                result.push_back(sidekick.get()) ;
            }
            return result ;
        }
        case ConditionTarget::FriendlyCharacters:
        {
            return currentPlayer->getAllCharacters();
        }
        case ConditionTarget::EnemyCharacters:
        {
            return enemyPlayer->getAllCharacters();
        }
        case ConditionTarget::Attacker:
        {
            return { attacker };
        }
        case ConditionTarget::Defender:
        {
            return { defender };
        }
        default:
        {
            return {};
        }
    }
}