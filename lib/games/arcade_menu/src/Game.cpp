/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Game
*/

#include "Game.hpp"
#include "Entity.hpp"
#include "Sound.hpp"

void arc::Game::simulate(const Event event) noexcept
{
    if (event.first == Action::Enter) {
        std::vector<std::string> args;
        args.push_back("lib/libarcade_snake.so");
        _commands.push_back(std::make_pair(Signal::LoadGame, args));
        return;
    }
}

std::pair<arc::Entities, arc::Sounds> arc::Game::getElements() noexcept
{
    Entities entities;
    Sounds sounds;

    if (_loadBackground) {
        Sound background(0, true);
        sounds.push_back(std::make_unique<arc::Sound>(background));
        _loadBackground = false;
    }
    return std::make_pair(std::move(entities), std::move(sounds));
}

std::vector<arc::Command> arc::Game::loadCommand() noexcept
{
    std::vector<Command> cpy(_commands);

    _commands.clear();
    return cpy;
}

const std::pair<std::vector<std::string>, std::vector<std::string>> arc::Game::_assets = {
    {

    }, {
        "assets/menu/background.wav",
    }
};

extern "C"
{
    std::unique_ptr<arc::IGameModule> makeInstance()
    {
        return std::make_unique<arc::Game>();
    }
    arc::LibType getLibType()
    {
        return arc::LibType::Game;
    }
}
