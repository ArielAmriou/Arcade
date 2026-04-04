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

arc::GameSnake::GameSnake() : _rotation(90), _tick(0)
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
        if ((action == Action::Z || action == Action::Up) && _rotation != 180)
            _rotation = 0;
        if ((action == Action::S || action == Action::Down) && _rotation != 0)
            _rotation = 180;
        if ((action == Action::Q || action == Action::Left) && _rotation != 90)
            _rotation = 270;
        if ((action == Action::D || action == Action::Right) && _rotation != 270)
            _rotation = 90;
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
    if (_rotation == 90) {
        if (head % GRIDX != GRIDX - 1)
            head += 1;
        else {
            std::vector<std::string> args;
            exit(Signal::RestartGame, args);
            return;
        }
    }
    if (_rotation == 180) {
        if (head < SIZE - GRIDX)
            head += GRIDX;
        else {
            std::vector<std::string> args;
            exit(Signal::RestartGame, args);
            return;
        }
    }
    if (_rotation == 270) {
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

    float rotation = _rotation;
    for (auto snake: _snake) {
        Entity tmp(0, {(float)(snake % GRIDX) / GRIDX, (snake - (float)(snake % GRIDX)) / GRIDX / GRIDY}, {1.0 / GRIDX, 1.0 / GRIDY}, rotation);
        entities.push_back(std::make_unique<arc::Entity>(tmp));
        rotation = 0;
    }
    Entity tmp(1, {(float)(_apple % GRIDX) / GRIDX, (_apple - (float)(_apple % GRIDX)) / GRIDX / GRIDY}, {1.0 / GRIDX, 1.0 / GRIDY}, rotation);
    entities.push_back(std::make_unique<arc::Entity>(tmp));
    if (_loadBackground) {
        Sound background(0, true);
        sounds.push_back(std::make_unique<arc::Sound>(background));
        _loadBackground = false;
    }
    if (_eat) {
        Sound pickUp(1, false);
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

const std::pair<std::vector<std::string>, std::vector<std::string>> arc::GameSnake::_assets = {
    {
        "assets/snake/loan",
        "assets/snake/ariel",
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
