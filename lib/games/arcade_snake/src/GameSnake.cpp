/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Game
*/

#include <cstdlib> 
#include <ctime> 
#include "GameSnake.hpp"
#include "Entity.hpp"
#include "Sound.hpp"
#include "IGameModule.hpp"

#include <iostream>
#define DEBUG(value) std::cout << "\e[0;35m" << "DEBUG: " <<  "\e[0;37m" << "\t" << value << std::endl;

arc::GameSnake::GameSnake() : _rotation(getAngle(Turn::Right)), _tick(0)
{
    srand((unsigned)time(0));
    int head = rand() % SIZE;
    if (head % GRIDX <= 2)
        head += 2;
    for (std::size_t i = head; i > head - 3; i--)
        _snake.push_back(i);
    while (true) {
        int nb = rand() % SIZE;
        bool collision = false;
        for (auto snake: _snake)
            if (snake == nb) {
                collision = true;
                continue;
            }
        if (collision)
            continue;
        _apple = nb;
        break;
    }
}

arc::Assets arc::GameSnake::getAssets() noexcept
{
    _loadBackground = true;
    return _assets;
}

void arc::GameSnake::simulate(const Event event) noexcept
{
    int head = _snake[0];

    if (event.first == Action::A || event.first == Action::Close) {
        _open = false;
        return;
    }
    if (event.first == Action::Enter) {
        std::vector<std::string> args;
        exit(Signal::BackToMenu, args);
        return;
    }
    _events.push_back(event);
    _tick++;
    if (_tick != 10)
        return;
    _tick = 0;
    for (auto myevent: _events) {
        auto action = myevent.first;
        if (action == Action::LShift)
            _shift = true;
        if (action == Action::Tab)
            _tab = true;
        if ((action == Action::Z || action == Action::Up) && _rotation != getAngle(Turn::Bottom))
            _rotation = 0;
        if ((action == Action::S || action == Action::Down) && _rotation != 0)
            _rotation = getAngle(Turn::Bottom);
        if ((action == Action::Q || action == Action::Left) && _rotation != getAngle(Turn::Right))
            _rotation = getAngle(Turn::Left);
        if ((action == Action::D || action == Action::Right) && _rotation != getAngle(Turn::Left))
            _rotation = getAngle(Turn::Right);
    }

    if (_rotation == 0) {
        if (head >= GRIDX)
            head -= GRIDX;
        else {
            std::vector<std::string> args;
            exit(Signal::RestartGame, args);
            return;
        }
    }
    if (_rotation == getAngle(Turn::Right)) {
        if (head % GRIDX != GRIDX - 1)
            head += 1;
        else {
            std::vector<std::string> args;
            exit(Signal::RestartGame, args);
            return;
        }
    }
    if (_rotation == getAngle(Turn::Bottom)) {
        if (head < SIZE - GRIDX)
            head += GRIDX;
        else {
            std::vector<std::string> args;
            exit(Signal::RestartGame, args);
            return;
        }
    }
    if (_rotation == getAngle(Turn::Left)) {
        if (head % GRIDX != 0)
            head -= 1;
        else {
            std::vector<std::string> args;
            exit(Signal::RestartGame, args);
            return;
        }
    }

    int tail = _snake.back();
    for (int i = _snake.size() - 1; i > 0; i--)
        _snake[i] = _snake[i - 1];
    _snake[0] = head;

    if (head == _apple) {
        _score += 10;
        _eat = true;
        _snake.push_back(tail);
        while (true) {
            int nb = rand() % SIZE;
            bool collision = false;
            for (auto snake: _snake)
                if (snake == nb) {
                    collision = true;
                    break;
                }
            if (!collision) {
                _apple = nb;
                break;
            }
        }
    }

    for (std::size_t i = 1; i < _snake.size(); i++)
        if (_snake[0] == _snake[i]) {
            std::vector<std::string> args;
            exit(Signal::RestartGame, args);
            return;
        }
}

std::pair<arc::Entities, arc::Sounds> arc::GameSnake::getElements() noexcept
{
    Entities entities;
    Sounds sounds;

    for (size_t i = 0; i < _snake.size(); i++)
        drawSnakePart(entities, i);
    Entity tmp(static_cast<size_t>(SnakeAsset::Apple), getPartPos(_apple),
        {1.0 / GRIDX, 1.0 / GRIDY}, 0);
    entities.push_back(std::make_unique<arc::Entity>(tmp));
    if (_loadBackground) {
        Sound background(static_cast<size_t>(SnakeSound::Background), true);
        sounds.push_back(std::make_unique<arc::Sound>(background));
        _loadBackground = false;
    }
    if (_eat) {
        Sound pickUp(static_cast<size_t>(SnakeSound::PickUp), false);
        sounds.push_back(std::make_unique<arc::Sound>(pickUp));
        _eat = false;
    }
    return std::make_pair(std::move(entities), std::move(sounds));
}

std::vector<arc::Command> arc::GameSnake::loadCommand() noexcept
{
    std::vector<Command> cpy(_commands);

    _commands.clear();
    return cpy;
}

void arc::GameSnake::exit(Signal signal, std::vector<std::string> args)
{
    if (_score != 0) {
        std::vector<std::string> argsScore;
        argsScore.push_back(std::to_string(_score));
        _commands.push_back(std::make_pair(Signal::LoadScore, argsScore));
    }
    _commands.push_back(std::make_pair(signal, args));
}

void arc::GameSnake::drawSnakePart(
    std::reference_wrapper<Entities> entities, size_t idx)
{
    if (idx == 0) {
        auto snake = _snake[idx];
        Entity part(static_cast<size_t>(SnakeAsset::Head), getPartPos(snake),
            {1.0 / GRIDX, 1.0 / GRIDY}, _rotation);
        entities.get().push_back(std::make_unique<arc::Entity>(part));
    } else if (idx == _snake.size() - 1)
        drawTail(entities, idx);
    else
        drawBody(entities, idx);
}

void arc::GameSnake::drawBody(
    std::reference_wrapper<Entities> entities, size_t idx)
{
    auto snake = _snake[idx];
    auto before = _snake[idx - 1];
    auto after = _snake[idx + 1];
    float rotation = 0;

    if (abs(before - after) != 2 && abs(before - after) != GRIDX * 2)
        return drawTurnBody(entities, idx);
    if (before == snake - 1)
        rotation = getAngle(Turn::Left);
    if (before == snake + 1)
        rotation = getAngle(Turn::Right);
    Entity part(static_cast<size_t>(SnakeAsset::Body), getPartPos(snake),
            {1.0 / GRIDX, 1.0 / GRIDY}, rotation);
    entities.get().push_back(std::make_unique<arc::Entity>(part));
}

void arc::GameSnake::drawTurnBody(
    std::reference_wrapper<Entities> entities, size_t idx)
{
    auto snake = _snake[idx];
    auto before = _snake[idx - 1];
    auto after = _snake[idx + 1];
    float rotation = 0;

    if ((before % GRIDX == snake % GRIDX && before > snake
        && after + 1 == snake) || (after % GRIDX == snake % GRIDX
        && after > snake && before + 1 == snake))
        rotation = getAngle(Turn::Right);
    if ((before % GRIDX == snake % GRIDX && before < snake
        && after + 1 == snake) || (after % GRIDX == snake % GRIDX
        && after < snake && before + 1 == snake))
        rotation = getAngle(Turn::Bottom);
    if ((before % GRIDX == snake % GRIDX && before < snake
        && after - 1 == snake) || (after % GRIDX == snake % GRIDX
        && after < snake && before - 1 == snake))
        rotation = getAngle(Turn::Left);
    Entity part(static_cast<size_t>(SnakeAsset::Turn), getPartPos(snake),
            {1.0 / GRIDX, 1.0 / GRIDY}, rotation);
    entities.get().push_back(std::make_unique<arc::Entity>(part));
}

void arc::GameSnake::drawTail(
    std::reference_wrapper<Entities> entities, size_t idx)
{
    auto snake = _snake[idx];
    auto before = _snake[idx - 1];
    float rotation = 0;

    if (before == snake - 1)
        rotation = getAngle(Turn::Left);
    if (before > snake)
        rotation = getAngle(Turn::Bottom);
    if (before == snake + 1)
        rotation = getAngle(Turn::Right);
    Entity part(static_cast<size_t>(SnakeAsset::Tail), getPartPos(snake),
            {1.0 / GRIDX, 1.0 / GRIDY}, rotation);
    entities.get().push_back(std::make_unique<arc::Entity>(part));
}

arc::Vector2f arc::GameSnake::getPartPos(size_t part)
{ 
    float x = (float)(part % GRIDX) / GRIDX;
    float y = (part - (float)(part % GRIDX)) / GRIDX / GRIDY;
    return std::make_pair(x, y);
}

const std::pair<std::vector<std::string>, std::vector<std::string>> arc::GameSnake::_assets = {
    {
        "assets/snake/snakeHead",
        "assets/snake/snakeTail",
        "assets/snake/snakeBody",
        "assets/snake/snakeTurn",
        "assets/snake/apple",
    }, {
        "assets/snake/background.wav",
        "assets/snake/pickUp.wav"
    }
};

extern "C"
{
    std::unique_ptr<arc::IGameModule> makeInstance()
    {
        return std::make_unique<arc::GameSnake>();
    }
    arc::LibType getLibType()
    {
        return arc::LibType::Game;
    }
}
