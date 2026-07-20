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
        void DrawSpaces(Canvas& canvas,Board& board,Player& player1,Player& player2) const;

        void PutText(Canvas& canvas,int row, int col,const std::string& text) const;

        std::string GetSpaceLabel(int position,Player& player1,Player& player2) const;

        ftxui::Color GetPlayerColor(int position, Player& p1, Player& p2) const;

        ftxui::Color GetZoneColor(const Board& board, int position) const;
        bool IsSecret(int position) const;
};

 