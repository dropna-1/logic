#include <functional>
#include <string>
#include <ftxui/component/component.hpp>

class Game;

class GameScreen {
public:
    GameScreen(std::function<void()> on_exit);

    void SetGame(Game*);
    ftxui::Component GetComponent();

private:
    Game* game_;

    ftxui::Component menu_;
    ftxui::Component renderer_;

    std::vector<std::string> actions{
        "Maneuver",
        "Attack",
        "Scheme",
        "End Turn"
    };

    int selected_ = 0;
};