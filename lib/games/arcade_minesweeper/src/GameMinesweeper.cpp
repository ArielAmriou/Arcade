/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** GameMinesweeper
*/

#include "GameMinesweeper.hpp"
#include "Sound.hpp"
#include "Entity.hpp"

void arc::GameMinesweeper::simulate(const Event event) noexcept
{
    if (event.first == Action::Tab) {
        std::vector<std::string> args;
        exit(Signal::BackToMenu, args);
        return;
    }
}

arc::Assets arc::GameMinesweeper::getAssets() noexcept
{
    _loadBackground = true;
    return _assets;
}

std::pair<arc::Entities, arc::Sounds> arc::GameMinesweeper::getElements() noexcept
{
    Entities entities;
    Sounds sounds;

    if (_loadBackground) {
        Sound background(static_cast<size_t>(MSSound::Background), true);
        sounds.push_back(std::make_unique<arc::Sound>(background));
        _loadBackground = false;
    }
    return std::make_pair(std::move(entities), std::move(sounds));
}

std::vector<arc::Command> arc::GameMinesweeper::loadCommand() noexcept
{
    std::vector<Command> cpy(_commands);

    _commands.clear();
    return cpy;
}

void arc::GameMinesweeper::exit(Signal signal, std::vector<std::string> args)
{
    // if (_score != 0) {
    //     std::vector<std::string> argsScore;
    //     argsScore.push_back(std::to_string(_score));
    //     _commands.push_back(std::make_pair(Signal::LoadScore, argsScore));
    // }
    _commands.push_back(std::make_pair(signal, args));
}

const std::pair<std::vector<std::string>, std::vector<std::string>> arc::GameMinesweeper::_assets = {
    {
        "assets/minesweeper/empty",
        "assets/minesweeper/one",
        "assets/minesweeper/two",
        "assets/minesweeper/three",
        "assets/minesweeper/four",
        "assets/minesweeper/five",
        "assets/minesweeper/six",
        "assets/minesweeper/seven",
        "assets/minesweeper/height",
        "assets/minesweeper/cover",
        "assets/minesweeper/flag",
        "assets/minesweeper/bomb",
    }, {
        "assets/minesweeper/background.wav",
        "assets/minesweeper/digging.wav",
        "assets/minesweeper/hammer.wav",
        "assets/minesweeper/explosion.wav",
    }
};

extern "C"
{
    std::unique_ptr<arc::IGameModule> makeInstance()
    {
        return std::make_unique<arc::GameMinesweeper>();
    }
    arc::LibType getLibType()
    {
        return arc::LibType::Game;
    }
}
