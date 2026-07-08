#include <algorithm>
#include <queue>
#include "include/Characters/SideKick.hpp"
#include "Effects/GameContext.hpp"
#include "Game.hpp"
#include "Cards/Deck.hpp"

Game::Game() : dracula(HeroFactory::createDracula())
, sherlock(HeroFactory::createSherlock()){}


void Game::setPlayer1(const string& name, const int& age){
    player1.setName(name);
    player1.setAge(age);
}


void Game::setPlayer2(const string& name, const int& age){
    player2.setName(name);
    player2.setAge(age);
}


Player* Game::getFirstPlayer(){
    if(player1.getAge() <= player2.getAge())
        return &player1;
    return &player2;
}


Player* Game::getCurrentPlayer(){
    return currentPlayer;
}


void Game::choiceHero(Player& player, HeroType choice){
    player.setHero((choice == dracula.get()->getHeroType() ? dracula : sherlock));
}


void Game::setupGame(){
    if(player1.getAge() <= player2.getAge()){
        currentPlayer = &player1;
        otherPlayer = &player2;
    }
    else{
        otherPlayer = &player1;
        currentPlayer = &player2;
    }

    for(int i = 0; i < 10; i++)
        (i < 5 ? currentPlayer : otherPlayer)->getHero()->getDeck().get()->drawCard();
}


void Game::startTurn(){
    actionsRemaining = 2;
}


Board& Game::getBoard(){
    return board;
}


bool Game::useAction(){
    if(actionsRemaining == 0)
        return false;
    actionsRemaining--;
    return true;
}


int Game::getRemainingActions() const{
    return actionsRemaining;
}


vector<int> Game::getAvailableMoves(Character* character, 
    const int& move)
{
    vector<int> reachable;
    queue<pair<int, int>> q;
    vector<bool> visited(board.size(), false);

    int start = character->getPosition();
    q.push({start, 0});
    visited[start] = true;

    while(!q.empty()){
        auto current = q.front();
        q.pop();
        int place = current.first;
        int dist = current.second;

        if(dist == move)
            continue;

        for(int next : board.getSpace(place).neighbors){
            if(visited[next])
                continue;
            if(next == otherPlayer->getHero()->getPosition())
                continue;
            for(auto sidekick : otherPlayer->getHero()->getSidekicks())
                if(next == sidekick.get()->getPosition())
                    continue;

            visited[next] = true;
            q.push({next, dist+1});

            for(auto sidekick : currentPlayer->getHero()->getSidekicks())
                if(next == sidekick.get()->getPosition())
                    continue;    
            reachable.push_back(next);
        }
    }
    sort(reachable.begin(), reachable.end());
    return reachable;
}


bool Game::canMove(int to, const vector<int>& reachable){
    for(int i : reachable)
        if(to == i)
            return true;
    return false;
}


void Game::move(Character* character, const int& pos){
    character->setPosition(pos);
}


int Game::calculateDamage(Card* attack, Card* defense){
    if(defense == nullptr)
        return attack->getValue();
    if(attack->getValue() > defense->getValue())
        return defense->getValue() - attack->getValue();
    return 0;
}


vector<Card*> Game::getPlayableAttackCard(Character* attacker){

    vector<Card*> playableCards;
    for(auto card : currentPlayer->getHero().get()->getDeck().get()->getHand())

        if(card.get()->getType() == CardType::Attack || 
        card.get()->getType() == CardType::Versalite)
        {
            if(card.get()->getFighter() == FighterType::Any)
                playableCards.push_back(card.get());
            else if(attacker->isHero() && card.get()->getFighter() == FighterType::Hero)
                playableCards.push_back(card.get());
            else if(!attacker->isHero() && card.get()->getFighter() == FighterType::Sidekick)
                playableCards.push_back(card.get()); 
        }
    return playableCards;
}


vector<Card*> Game::getPlayableDefenseCard(Character* defender){

    vector<Card*> playableCards;
    for(auto card : otherPlayer->getHero().get()->getDeck().get()->getHand())
    
        if(card.get()->getType() == CardType::Defend || 
        card.get()->getType() == CardType::Versalite)
        {
            if(card.get()->getFighter() == FighterType::Any)
                playableCards.push_back(card.get());
            else if(defender->isHero() && card.get()->getFighter() == FighterType::Hero)
                playableCards.push_back(card.get());
            else if(!defender->isHero() && card.get()->getFighter() == FighterType::Sidekick)
                playableCards.push_back(card.get());
        }
    return playableCards;
}


vector<int> Game::getSidekickPlacement(){

    vector<int> reachable;
    for(int zone : board.getSpace(currentPlayer->getHero()->getPosition()).zone){
        for(int i = 0; i < 32; i++)
        {
            if(i == currentPlayer->getHero()->getPosition())
                continue;
            vector<int> zones = board.getSpace(i).zone;
            if(find(zones.begin(), zones.end(), zone) != zones.end())
                reachable.push_back(i);
        }
    }
    return reachable;
}


void Game::changeTurn(){
    swap(currentPlayer, otherPlayer);
}


Hero* Game::checkWinner(){
    if(!currentPlayer->getHero()->isAlive())
        return otherPlayer->getHero().get();
    if(!otherPlayer->getHero()->isAlive())
        return currentPlayer->getHero().get();
    return nullptr;
}


vector<AttackOption>& Game::getAttackableTargets()
{
    vector<AttackOption> targets;
    for(Character* self : currentPlayer->getAllCharacters())
        for(int neighbor : board.getSpace(self->getPosition()).neighbors)
            for(Character* enemy : otherPlayer->getAllCharacters())
                if(neighbor == enemy->getPosition())
                    targets.push_back({self, enemy});

    return targets;
}


int Game::boost(Character* self, vector<int>& cards){
    int movement = self->getMovement();
    for(int cardIndex : cards){
        movement += currentPlayer->getHero().get()->getDeck()
        .get()->getHand().at(cardIndex).get()->getBoost();

        currentPlayer->getHero().get()->getDeck()
        .get()->discardFromHand(cardIndex);
    }
    return movement;
}


void Game::playScheme(Character* source, const int& schemeCardIndex)
{
    GameContext context(
        currentPlayer,
        otherPlayer,
        source,
        nullptr,
        &board
    );
    auto schemeCard = currentPlayer->getHero().get()->getDeck()
    .get()->playCard(schemeCardIndex);

    schemeCard.get()->execute(TriggerType::None, context);

    currentPlayer->getHero().get()->getDeck()
    .get()->discardCard(schemeCard);
}



void Game::combat(AttackOption option, const int& attackCardIndex, 
    const int& defenseCardIndex){

    auto attackCard = currentPlayer->getHero().get()->getDeck()
    .get()->playCard(attackCardIndex);

    auto defenseCard = otherPlayer->getHero().get()->getDeck().
    get()->playCard(defenseCardIndex);

    GameContext context(
        currentPlayer,
        otherPlayer,
        option.attacker,
        option.target,
        &board
    );

    int damage = calculateDamage(attackCard.get(), defenseCard.get());

    /*immediate*/
    attackCard->execute(TriggerType::Immediately, context);
    defenseCard->execute(TriggerType::Immediately, context);

    if(damage != 0)
        option.target->takeDamage(damage);
    
    /*during*/
    attackCard->execute(TriggerType::DuringCombat, context);
    defenseCard->execute(TriggerType::DuringCombat, context);

    /*after*/
    attackCard->execute(TriggerType::AfterCombat, context);
    defenseCard->execute(TriggerType::AfterCombat, context);

    /*discard*/
    currentPlayer->getHero().get()->getDeck()
    .get()->discardCard(attackCard);

    otherPlayer->getHero().get()->getDeck()
    .get()->discardCard(defenseCard);

}