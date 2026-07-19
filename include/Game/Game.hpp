#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "Board/board.hpp"
#include "Characters/Hero.hpp"
#include "Factory/HeroFactory.hpp"
#include "Effects/GameContext.hpp"
#include "Player/player.hpp"

class PendingAction;
class GameContext;
class Character;
class Card;

struct AttackOption {
    Character* attacker;
    Character* target;
};


struct Option {
    std::string text;
    int id;

    bool operator<(const Option& other){
        return id < other.id; 
    }
};


enum class CombatStage{
    DefenseImmediate,
    AttackImmediate,

    DefenseDuring,
    AttackDuring,

    DealDamage,

    DefenseAfter,
    AttackAfter,

    Discard,
    Finished
};

struct PendingSelection{
    Character* character = nullptr;
    std::vector<int> cards;
    int destination = -1;
};

struct PendingCombat{
    AttackOption option;

    std::shared_ptr<Card> attackCard;
    std::shared_ptr<Card> defenseCard;

    GameContext& context;
    CombatStage stage;
    PendingSelection selection;

    PendingCombat(AttackOption option, std::shared_ptr<Card> attackCard, 
        std::shared_ptr<Card> defenseCard, GameContext& context) : option(option), 
        attackCard(attackCard), defenseCard(defenseCard), context(context),
        stage(CombatStage::DefenseImmediate) {}
};

class Game {

    Board board;

    Player player1;
    Player player2;
    
    std::shared_ptr<Hero> dracula;
    std::shared_ptr<Hero> sherlock;

    Player* currentPlayer;
    Player* otherPlayer;

    int actionsRemaining = 2;

    std::queue<unique_ptr<PendingAction>> pendingActions;
    std::unique_ptr<PendingCombat> pendingCombat;

public:

    Game();
    void setupGame();
    void startTurn();
    void changeTurn();
    Hero* checkWinner();
    Board& getBoard();
    std::shared_ptr<Hero> getDracula() const;
    std::unique_ptr<PendingCombat>& getPendingCombat();
    /*-----------------------------------------------------------------*/
    void setPlayer1(const string& name, const int& age);
    void setPlayer2(const string& name, const int& age);
    Player* getCurrentPlayer();
    Player* getOtherPlayer();
    Player* getFirstPlayer();
    void choiceHero(Player& player, HeroType choice);
    std::vector<Option> getSidekickPlacement(Character* character);
    const std::vector<std::shared_ptr<Card>>& showOtherHand();
    /*-----------------------------------------------------------------*/
    std::vector<Option> getAvailableMoves(Character* character, const int& spacing);
    std::vector<Option> getAllSpaces();
    bool canMove(int to) const;
    void move(Character* character, const int& pos);
    int boost(Character* self, vector<int>& cards);
    bool canManever(std::vector<int> availableMoves) const;
    std::vector<Option> getFreeSpacesNearby(Character* character);
    /*------------------------------------------------------------------*/
    void requestAction(std::unique_ptr<PendingAction> action);
    bool hasPendingMove() const;
    PendingAction* currentPendingAction();
    void completePendingMove(const int& position);
    /*------------------------------------------------------------------*/
    bool useAction();
    int getRemainingActions() const;
    void addAction();
    /*------------------------------------------------------------------*/
    std::vector<AttackOption> getAttackableTargets();
    std::vector<Card*> getPlayableAttackCard(Character* attacker);
    std::vector<Card*> getPlayableDefenseCard(Character* defender);
    bool canDefense(std::vector<Card*> playableDefenseCard) const;
    bool canAttack(std::vector<Card*> playableAttackCard,
        std::vector<AttackOption> targets) const;
    std::vector<Character*> getEnemiesNearby(Character* character);
    /*------------------------------------------------------------------*/
    void playScheme(Character* source, const int& schemeCardIndex);
    std::vector<Card*> getSchemeCards(Character* character);
    bool canPlayScheme(std::vector<Card*> playableSchemeCard) const;
    /*------------------------------------------------------------------*/
    int calculateDamage(Card* attack, Card* defense);
    void combat(AttackOption option, const int& attackCardIndex, 
        const int& defenseCardIndex);
    void continueCombat();
};