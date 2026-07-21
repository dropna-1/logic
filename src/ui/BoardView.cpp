#include "ui/BoardView.hpp"

#include "Board/board.hpp"
#include "Player/player.hpp"
#include "Characters/Hero.hpp"
#include "Characters/SideKick.hpp"
#include <ftxui/screen/color.hpp>

#include <array>
#include <vector>
#include <algorithm>

using namespace ftxui;
using namespace std;

namespace
{
    string ShortName(const string& name)
    {
        if(name=="Sherlock")
            return "SH";

        if(name=="Dr.Watson")
            return "WA";

        if(name=="Dracula")
            return "DR";

        if(name=="Sister 1")
            return "S1";

        if(name=="Sister 2")
            return "S2";

        if(name=="Sister 3")
            return "S3";

        return name;
    }
}

string MakeLabel(int id, const Board& board, const string& text)
{
    string label = text;

    if(label.size() == 1)
        label = "0" + label;
    if(label.size() > 2)
        label = label.substr(0,2);

    const auto& zone = board.getSpace(id).zone;

    if(zone.size() > 1)
        return "{" + label + "}";

    return "(" + label + ")";
}


BoardView::Canvas BoardView::CreateEmptyBoard() const
{
    return {
"                                                   ",
"*    ---            ---             --*           ",
"   |        \\   /  \\   /    \\   /   \\              ",
"   |                            -----              ",
"     ---      |               |        |           ",
"   |       \\  |               |  ----              ",
"   |                          | /       \\          ",
"   |       /       *    ----    ---    --         ",
"     ---            /        | \\          |        ",
"   |                         |  \\         |        ",
"   |           /    \\        |   \\        |        ",
"     ------             ---    ---    ---         ",
"   |               /    \\   |       \\    /         ",
"*    ---    ---    ------                         ",
"                                                   ",
"                                                   ",
};
}

static const Position SpacePosition[32] =
{
    { 1,  1}, // 00
    { 1,  8}, // 01

    { 4,  1}, // 02
    { 4,  8}, // 03
    { 3, 12}, // 04

    { 1, 16}, // 05
    { 1, 24}, // 06
    { 3, 19}, // 07
    { 3, 28}, // 08

    { 1, 32}, // 09
    { 3, 37}, // 10
    { 1, 39}, // 11

    { 6,  11}, // 12

    { 8,  1}, // 13
    { 8,  8}, // 14

    { 5, 36}, // 15

    { 7, 41}, // 16
    { 7, 28}, // 17
    { 7, 35}, // 18
    { 7, 20}, // 19

    { 9, 16}, // 20
    {11,  11}, // 21

    {11,  1}, // 22
    {13,  1}, // 23
    {13,  8}, // 24
    {13, 15}, // 25

    {11, 20}, // 26
    {13, 25}, // 27
    {11, 27}, // 28
    {11, 34}, // 29

    {13, 37}, // 30
    {11, 41}, // 31
};

string BoardView::GetSpaceLabel(
    int position,
    Player& p1,
    Player& p2
) const
{
    auto checkPlayer =
    [&](Player& player)->string
    {
        auto hero = player.getHero();

        if(!hero)
            return "";

        if(hero->getPosition()==position)
            return ShortName(hero->getname());

        auto& sidekicks = hero->getSidekicks();

        for(const auto& sidekick : sidekicks)
        {
            if(sidekick->getPosition()==position)
                return ShortName(sidekick->getname());
        }

        return "";
    };

    string result = checkPlayer(p1);

    if(!result.empty())
        return result;

    result = checkPlayer(p2);

    if(!result.empty())
        return result;

    return to_string(position);
}

Color BoardView::GetPlayerColor( int position, Player& p1, Player& p2) const
{
    auto hero = p1.getHero();
    
    if(hero)
    {
        if(hero->getPosition()==position)
            return Color::Blue;

        for(auto& s : hero->getSidekicks())
            if(s->getPosition()==position)
                return Color::Blue;
    }

    hero = p2.getHero();

    if(hero)
    {
        if(hero->getPosition()==position)
            return Color::Red;

        for(auto& s : hero->getSidekicks())
            if(s->getPosition()==position)
                return Color::Red;
    }

    return Color::Default;
}

Color BoardView::GetZoneColor(const Board& board, int position) const
{
    const auto& zone = board.getSpace(position).zone;

    if(zone.size()>1)
        return Color::White;

    switch(zone[0])
    {
        case 1: return Color::CyanLight;
        case 2: return Color::SandyBrown;
        case 3: return Color::Khaki1;
        case 4: return Color::DarkBlue;
        case 5: return Color::Purple4;
        case 6: return Color::LightGreen;
        case 7: return Color::SkyBlue1 ;

        default:
            return Color::Black ;
    }
}

/*Color BoardView::GetZoneBackground( const Board& board, int position) const
{
    const auto& zone = board.getSpace(position).zone;

    if(zone.size() > 1)
        return Color::GrayLight; 

    return Color::Default;
}*/


bool BoardView::IsSecret(int position) const
{
    return position==0
        || position==11
        || position==19
        || position==23;
}

Element BoardView::RenderLine(const string& line, int row, Board& board, Player& p1, Player& p2) const
{
    struct SpaceRef
    {
        int id;
        int col;
    };

    vector<SpaceRef> spaces;

    for(int id=0; id<32; id++)
    {
        if(SpacePosition[id].row == row)
            spaces.push_back({id, SpacePosition[id].col});
    }
    sort(spaces.begin(), spaces.end(),
    [](auto& a, auto& b)
    {
        return a.col < b.col;
    });
    Elements parts;

    int current = 0;

    for(auto& s : spaces)
    {
        int id = s.id ;
        auto pos = SpacePosition[id];

        if(pos.row != row)
            continue;

        if(pos.col > current)
        {
            parts.push_back(
                text(line.substr(current, pos.col-current))
            );
        }

        Color c = GetPlayerColor(id,p1,p2);

        if(c == Color::Default)
            c = GetZoneColor(board,id);
        
        parts.push_back(
            text(
                MakeLabel(id, board ,GetSpaceLabel(id,p1,p2))
            )  | color(c)
        );
        current = pos.col + 4;
    }

    if(current < (int)line.size())
    {
        parts.push_back(
            text(line.substr(current))
        );
    }

    return hbox(std::move(parts));
}

Element BoardView::Render(Board& board, Player& player1, Player& player2) const
{
    Canvas canvas = CreateEmptyBoard();

    vector<Element> rows;

    for(int i=0;i<canvas.size();i++)
    {
        rows.push_back(
            RenderLine(
                canvas[i],
                i,
                board,
                player1,
                player2
            )
        );
    }
    return window( text(" Baskerville Manor "), vbox(move(rows)) );
    
}


Element BoardView::RenderPreviewLine(
    const std::string& line,
    int row,
    int selectedPosition,
    Board& board
) const
{
    struct SpaceRef
    {
        int id;
        int col;
    };

    std::vector<SpaceRef> spaces;

    for(int id = 0; id < 32; id++)
        if(SpacePosition[id].row == row)
            spaces.push_back({id, SpacePosition[id].col});

    std::sort(spaces.begin(), spaces.end(),
        [](auto& a, auto& b)
        {
            return a.col < b.col;
        });

    Elements parts;

    int current = 0;

    for(auto& s : spaces)
    {
        if(s.col > current)
        {
            parts.push_back(
                text(line.substr(current, s.col-current))
            );
        }

        Decorator deco = color(Color::GrayLight);

        if(s.id == selectedPosition)
            deco = color(Color::YellowLight) | bold;

        parts.push_back(
            text(MakeLabel(s.id, board ,std::to_string(s.id))) | deco
        );

        current = s.col + 4;
    }

    if(current < (int)line.size())
        parts.push_back(text(line.substr(current)));

    return hbox(std::move(parts));
}

Element BoardView::RenderPlacementPreview(
    Board& board,
    int selectedPosition
) const
{
    Canvas canvas = CreateEmptyBoard();

    Elements rows;

    for(int i = 0; i < canvas.size(); i++)
    {
        rows.push_back(
            RenderPreviewLine(
                canvas[i],
                i,
                selectedPosition , 
                board
            )
        );
    }

    return window(
        text(" Available Positions "),
        vbox(std::move(rows))
    );
}
