#include <iostream>
#include "../../include/Snake.hpp"
#include "../../include/Settings.hpp"
#include "../../include/Player.hpp"
#include "../../include/SnakeMath.hpp"

using namespace Engine;
using namespace Math;

Snake::Snake()
{

}

Snake::Snake(std::shared_ptr<Context> &context, int player) :context(context), player(player)
{
}

void Snake::Init()
{
    int x, y;
    switch (player)
    {
        case PLAYER1:
            x = SnakeMath::calculateSnake1X(Settings::UNIT_SIZE);
            y = SnakeMath::calculateSnake1Y(Settings::GAME_YPOS, Settings::UNIT_SIZE);
            break;
        case PLAYER2:
            x = SnakeMath::calculateSnake2X(Settings::CENTER, Settings::UNIT_SIZE);
            y = SnakeMath::calculateSnake2Y(Settings::GAME_YPOS, Settings::UNIT_SIZE);
            break;
        default:
            x = 0, y = 0;
            break;
    }
    for (int i = 0; i < size; i++)
    {
        body.emplace_back(context, x, y);
        x+=Settings::UNIT_SIZE;
    }
}

void Snake::Move()
{
    body.emplace_back(context, xPos, yPos);
    if (body.size() > size) body.erase(body.begin());
}

void Snake::draw(char dir)
{
    for (auto part = body.begin(); part != body.end(); ++part)
    {
        switch (player)
        {
            case PLAYER1:
                if (part == body.end()-1)
                    part->drawHead(dir);
                else
                    part->drawBody();
                break;
            case PLAYER2:
                if (part == body.begin())
                    part->drawHead(dir);
                else
                    part->drawBody();
                break;
            default:
                break;
        }
    }
}

void Snake::setXPos(int x)
{
    xPos = x;
}

int Snake::getXPos()
{
    return xPos;
}

void Snake::setYPos(int y)
{
    yPos = y;
}

int Snake::getYPos()
{
    return yPos;
}
