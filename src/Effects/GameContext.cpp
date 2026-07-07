#include "Effects/GameContext.hpp"
using namespace std ;

vector<Character*> GameContext::getTargets(EffectTarget target)
{
    switch(target)
    {
        case EffectTarget::FriendlyHero :
        {
            return {currentPlayer->getHero()};
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