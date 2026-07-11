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


const vector<shared_ptr<Card>>& Game::showOtherHand(){
    return otherPlayer->getHero().get()->getDeck().get()->getHand();
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
    const int& spacing)
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

        if(dist == spacing)
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


vector<int> Game::getAllSpaces(){
    vector<int> allSpaces;

    for(int space = 0; space < 32; space++)
        if(canMove(space))
            allSpaces.push_back(space);

    return allSpaces;
}


bool Game::canMove(int to) const{
    for(auto character : currentPlayer->getAllCharacters())
        if(character->getPosition() == to)
            return false;
    for(auto character : otherPlayer->getAllCharacters())
        if(character->getPosition() == to)
            return false;
    return true;
}


void Game::move(Character* character, const int& pos){
    character->setPosition(pos);
}


bool Game::canManever(vector<int> availableMoves) const{
    if(availableMoves.empty())
        return false;
    return true;
}


void Game::requestMove(Character* character, int range){
    pendingMove = {character, range};
}


bool Game::hasPendingMove() const{
    return pendingMove.has_value();
}


PendingMove Game::getPendingMove() const{
    return pendingMove.value();
}


void Game::completePendingMove(const int& position){
    move(pendingMove->character, position);
    pendingMove.reset();
}


int Game::calculateDamage(Card* attack, Card* defense){
    if(defense == nullptr)
        return attack->getValue();
    if(attack->getValue() > defense->getValue())
        return defense->getValue() - attack->getValue();
    return 0;
}


vector<Card*> Game::getPlayableAttackCard(Character* attacker)
{
    vector<Card*> playableCards;
    bool ishero = attacker->isHero();
    for(auto card : currentPlayer->getHero().get()->getDeck().get()->getHand())

        if(card.get()->getType() == CardType::Attack || 
        card.get()->getType() == CardType::Versalite)
        {
            if(card.get()->getFighter() == FighterType::Any)
                playableCards.push_back(card.get());
            else if(ishero && card.get()->getFighter() == FighterType::Hero)
                playableCards.push_back(card.get());
            else if(!ishero && card.get()->getFighter() == FighterType::Sidekick)
                playableCards.push_back(card.get()); 
        }
    return playableCards;
}


vector<Card*> Game::getPlayableDefenseCard(Character* defender)
{
    vector<Card*> playableCards;
    bool ishero = defender->isHero();
    for(auto card : otherPlayer->getHero().get()->getDeck().get()->getHand())
    
        if(card.get()->getType() == CardType::Defend || 
        card.get()->getType() == CardType::Versalite)
        {
            if(card.get()->getFighter() == FighterType::Any)
                playableCards.push_back(card.get());
            else if(ishero && card.get()->getFighter() == FighterType::Hero)
                playableCards.push_back(card.get());
            else if(!ishero && card.get()->getFighter() == FighterType::Sidekick)
                playableCards.push_back(card.get());
        }
    return playableCards;
}


vector<Card*> Game::getSchemeCards(Character* character)
{
    vector<Card*> playableCards;
    bool ishero = character->isHero();
    for(auto card : otherPlayer->getHero().get()->getDeck().get()->getHand())

        if(card.get()->getType() == CardType::Scheme)
        {
            if(ishero && card.get()->getFighter() == FighterType::Hero)
                playableCards.push_back(card.get());
            else if(!ishero && card.get()->getFighter() == FighterType::Sidekick)
                playableCards.push_back(card.get());
        }
    return playableCards;
}


vector<int> Game::getSidekickPlacement()
{
    vector<int> reachable;
    for(int zone : board.getSpace(currentPlayer->getHero()->getPosition()).zone)
        for(int i = 0; i < 32; i++)
        {
            if(i == currentPlayer->getHero()->getPosition())
                continue;
            vector<int> zones = board.getSpace(i).zone;
            if(find(zones.begin(), zones.end(), zone) != zones.end())
                reachable.push_back(i);
        }
    return reachable;
}


void Game::changeTurn(){
    swap(currentPlayer, otherPlayer);
}


void Game::addAction(){
    actionsRemaining++;
}


Hero* Game::checkWinner(){
    if(!currentPlayer->getHero()->isAlive())
        return otherPlayer->getHero().get();
    if(!otherPlayer->getHero()->isAlive())
        return currentPlayer->getHero().get();
    return nullptr;
}


vector<AttackOption> Game::getAttackableTargets()
{
    vector<AttackOption> targets;
    for(Character* self : currentPlayer->getAllCharacters())
        for(int neighbor : board.getSpace(self->getPosition()).neighbors)
            for(Character* enemy : otherPlayer->getAllCharacters())
                if(neighbor == enemy->getPosition())
                    targets.push_back({self, enemy});
    return targets;
}


bool Game::canAttack(vector<Card*> playableAttackCard,
    vector<AttackOption> targets) const
{
    if(playableAttackCard.empty() || targets.empty())
        return false;
    return true;
}


bool Game::canDefense(vector<Card*> playableDefenseCard) const{
    if(playableDefenseCard.empty())
        return false;
    return true;
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


bool Game::canPlayScheme(vector<Card*> playableSchemeCard) const{
    if(playableSchemeCard.empty())
        return false;
    return true;
}


void Game::playScheme(Character* source, const int& schemeCardIndex)
{
    GameContext context(
        currentPlayer,
        otherPlayer,
        source,
        nullptr,
        &board,
        nullptr,
        nullptr,
        this
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
        &board,
        attackCard.get(),
        defenseCard.get(),
        this
    );

    /*immediate*/
    defenseCard->execute(TriggerType::Immediately, context);
    attackCard->execute(TriggerType::Immediately, context);

    /*during*/
    defenseCard->execute(TriggerType::DuringCombat, context);
    attackCard->execute(TriggerType::DuringCombat, context);

    int damage = calculateDamage(attackCard.get(), defenseCard.get());

    if(damage != 0)
        option.target->takeDamage(damage);

    if(damage > 0) {context.setWinner(option.attacker);}
    else {context.setWinner(option.target);}
    
    /*after*/
    defenseCard->execute(TriggerType::AfterCombat, context);
    attackCard->execute(TriggerType::AfterCombat, context);

    /*discard*/
    currentPlayer->getHero().get()->getDeck()
    .get()->discardCard(attackCard);

    otherPlayer->getHero().get()->getDeck()
    .get()->discardCard(defenseCard);

}