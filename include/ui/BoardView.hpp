#pragma once

#include <string>
#include <vector>

#include <ftxui/dom/elements.hpp>



class Board;
class Player;

struct Position
    {
        int row;
        int col;
};

class BoardView
{
    public:
        ftxui::Element Render(
            Board& board,
            Player& player1,
            Player& player2
        ) const;

    private:

        using Canvas = std::vector<std::string>;
        Canvas CreateEmptyBoard() const;
        std::string GetSpaceLabel(int position,Player& player1,Player& player2) const;
        ftxui::Color GetPlayerColor(int position, Player& p1, Player& p2) const;
        ftxui::Color GetZoneColor(const Board& board, int position) const;
        bool IsSecret(int position) const;
        ftxui::Element RenderLine( const std::string& line, int row, Board& board, Player& p1, Player& p2) const;
        ftxui::Color GetZoneBackground( const Board& board,int position) const ;
};

 