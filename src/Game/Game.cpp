#include <algorithm>
#include "Characters/SideKick.hpp"
#include "Game/Game.hpp"
#include "Cards/Deck.hpp"
#include "Pending/Pending.hpp"
using namespace std;


Game::Game() : dracula(HeroFactory::createDracula())
, sherlock(HeroFactory::createSherlock()){}


shared_ptr<Hero> Game::getDracula() const{
    return dracula;
}

unique_ptr<PendingCombat>& Game::getPendingCombat(){
    return pendingCombat;
}


void Game::setPlayer1(const string& name, const int& age){
    player1.setName(name);
    player1.setAge(age);
}


void Game::setPlayer2(const string& name, const int& age){
    player2.setName(name);
    player2.setAge(age);
}


void Game::setupPlayers(){
    if(player1.getAge() <= player2.getAge()){
        currentPlayer = &player1;
        otherPlayer = &player2;
    }
    else{
        otherPlayer = &player1;
        currentPlayer = &player2;
    }
}


Player* Game::getCurrentPlayer(){
    return currentPlayer;
}


Player* Game::getOtherPlayer(){
    return otherPlayer;
}


void Game::choiceHero(Player& player, HeroType choice){
    player.setHero((choice == dracula.get()->getHeroType() ? dracula : sherlock));
}


void Game::setupGame(){
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


vector<Option> Game::getAvailableMoves(Character* character, 
    const int& spacing)
{
    vector<Option> reachable;
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
            reachable.push_back({"House", next});
        }
    }
    sort(reachable.begin(), reachable.end());
    return reachable;
}


vector<Option> Game::getAllSpaces(){
    vector<Option> allSpaces;

    for(int space = 0; space < 32; space++)
        if(canMove(space))
            allSpaces.push_back({"House", space});

    return allSpaces;
}

vector<Option> Game::getFreeSpacesNearby(Character* character){
    vector<Option> freeSpaces;
    for(int neigh : board.getSpace(character->getPosition()).neighbors)
        if(canMove(neigh))
            freeSpaces.push_back({"House", neigh});
    return freeSpaces;
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


void Game::requestAction(unique_ptr<PendingAction> action){
    pendingActions.push(std::move(action));
}


bool Game::hasPendingMove() const{
    return !pendingActions.empty();
}


PendingAction* Game::currentPendingAction(){
    if(pendingActions.empty())
        return nullptr;
    return pendingActions.front().get();
}


void Game::completePendingMove(const int& position){
    pendingActions.pop();
}


int Game::calculateDamage(Card* attack, Card* defense){
    if(defense == nullptr)
        return attack->getValue();
    if(attack->getValue() > defense->getValue())
        return defense->getValue() - attack->getValue();
    return 0;
}


vector<Character*> Game::getEnemiesNearby(Character* character){
    vector<Character*> enemies;
    auto neighboors = board.getSpace(dracula.get()->getPosition()).neighbors;
    for(int target : neighboors){
        for(auto character : player1.getAllCharacters())
            if(character->getPosition() == target)
                enemies.push_back(character);
        for(auto character : player2.getAllCharacters())
            if(character->getPosition() == target)
                enemies.push_back(character);
    }
    return enemies;
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


vector<Option> Game::getSidekickPlacement(Character* character)
{
    vector<Option> reachable;
    for(int zone : board.getSpace(character->getPosition()).zone)
        for(int i = 0; i < 32; i++)
        {
            if(!canMove(i))
                continue;
            vector<int> zones = board.getSpace(i).zone;
            if(find(zones.begin(), zones.end(), zone) != zones.end())
                reachable.push_back({"House", i});
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
    .get()->getHand().at(schemeCardIndex);

    schemeCard.get()->execute(TriggerType::None, context);

    if(hasPendingMove())
        return;

    currentPlayer->getHero().get()->getDeck()
    .get()->discardFromHand(schemeCardIndex);
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

    pendingCombat = make_unique<PendingCombat>(
        option, attackCard, defenseCard, context
    );

    continueCombat();
}

void Game::continueCombat()
{
    while(pendingCombat)
    {
        switch (pendingCombat.get()->stage)
        {
        /*---------------------------immediat---------------------------*/
        case CombatStage::DefenseImmediate:
        {
            pendingCombat.get()->defenseCard->execute(TriggerType::Immediately, 
                pendingCombat.get()->context);
            if(hasPendingMove())
                return;
            pendingCombat.get()->stage = CombatStage::AttackImmediate;
            continue;
        }
        /*-----------------------------------------------------------------*/
        case CombatStage::AttackImmediate:
        {
            pendingCombat.get()->attackCard->execute(TriggerType::Immediately, 
                pendingCombat.get()->context);
            if(hasPendingMove())
                return;
            pendingCombat.get()->stage = CombatStage::DefenseDuring;
            continue;
        }
        /*---------------------------during---------------------------*/
        case CombatStage::DefenseDuring:
        {
            pendingCombat.get()->defenseCard->execute(TriggerType::DuringCombat, 
                pendingCombat.get()->context);
            if(hasPendingMove())
                return;
            pendingCombat.get()->stage = CombatStage::AttackDuring;
            continue;
        }
        /*-----------------------------------------------------------------*/
        case CombatStage::AttackDuring:
        {
            pendingCombat.get()->attackCard->execute(TriggerType::DuringCombat, 
                pendingCombat.get()->context);
            if(hasPendingMove())
                return;
            pendingCombat.get()->stage = CombatStage::DealDamage;
            continue;
        }
        /*---------------------------damage---------------------------*/
        case CombatStage::DealDamage:
        {
            int damage = calculateDamage(pendingCombat.get()->attackCard.get(), 
            pendingCombat.get()->defenseCard.get());

            if(damage > 0){
                pendingCombat.get()->option.target->takeDamage(damage);
                pendingCombat.get()->context.setWinner(pendingCombat.get()->option.attacker);
            }
            else {pendingCombat.get()->context.setWinner(pendingCombat.get()->option.target);}
            pendingCombat.get()->stage = CombatStage::DefenseAfter;  
            continue;
        }
        /*---------------------------after---------------------------*/
        case CombatStage::DefenseAfter:
        {
            pendingCombat.get()->defenseCard->execute(TriggerType::AfterCombat, 
                pendingCombat.get()->context);
            if(hasPendingMove())
                return;
            pendingCombat.get()->stage = CombatStage::AttackAfter;
            continue;
        }
        /*-----------------------------------------------------------------*/
        case CombatStage::AttackAfter:
        {
            pendingCombat.get()->attackCard->execute(TriggerType::AfterCombat, 
                pendingCombat.get()->context);
            if(hasPendingMove())
                return;
            pendingCombat.get()->stage = CombatStage::Discard;
            continue;
        }
        /*---------------------------discard---------------------------*/
        case CombatStage::Discard:
        {
            currentPlayer->getHero().get()->getDeck()
                .get()->discardCard(pendingCombat.get()->defenseCard);

            otherPlayer->getHero().get()->getDeck()
                .get()->discardCard(pendingCombat.get()->attackCard);

            pendingCombat.get()->stage = CombatStage::Finished;
            continue;
        }
        /*---------------------------finish---------------------------*/
        case CombatStage::Finished:
        {
            pendingCombat.reset();
            return;
        }
        }
    }
}