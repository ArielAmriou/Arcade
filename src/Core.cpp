/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Core
*/

#include <fstream>
#include <iostream>
#include <iomanip>
#include "Core.hpp"
#include "DLLoader.hpp"
#include "Exceptions.hpp"
#define DEBUG(value) std::cout << "\e[0;35m" << "DEBUG: " <<  "\e[0;37m" << "\t" << value << std::endl;

arc::Core::Core(const std::string &path): _loader(path) {
    _commands[arc::Signal::LoadDisplay] = [this](std::vector<std::string> list) {loadDisplay(list);};
    _commands[arc::Signal::LoadGame] = [this](std::vector<std::string> list) {loadGame(list);};
    _commands[arc::Signal::RestartGame] = [this](std::vector<std::string> list) {restartGame(list);};
    _commands[arc::Signal::BackToMenu] = [this](std::vector<std::string> list) {BackToMenu(list);};
    _commands[arc::Signal::LoadUser] = [this](std::vector<std::string> list) {loadUser(list);};
    _commands[arc::Signal::LoadScore] = [this](std::vector<std::string> list) {loadScore(list);};
    try {
        auto disp = _loader.makeInstance<IDisplayModule>(arc::LibType::Display);
        if (!disp.has_value())
            throw arc::exceptions::NotGraphical();
        disp.value().swap(_display);

        _loader.reset(DEFAULT_GAME_PATH);
        auto game = _loader.makeInstance<IGameModule>(arc::LibType::Game);
        if (!game.has_value())
            throw arc::exceptions::LibraryLoadError();
        game.value().swap(_game);
    } catch (...) {
        throw arc::exceptions::LibraryLoadError();
    }
}

void arc::Core::loadGameModule(const std::string &path, const std::exception &e) {
    _loader.reset(path);
    auto game = _loader.makeInstance<IGameModule>(arc::LibType::Game);
    if (!game.has_value())
        throw e;
    game.value().swap(_game);
}

void arc::Core::loadDisplayModule(const std::string &path, const std::exception &e) {
    _loader.reset(path);
    auto disp = _loader.makeInstance<IDisplayModule>(arc::LibType::Display);
    if (!disp.has_value())
        throw e;
    disp.value().swap(_display);
}

void arc::Core::execCommand(const std::vector<Command> commands)
{
    for (auto part: commands)
        _commands[part.first](part.second);
}

void arc::Core::play() {
    Event event = {arc::Action::None, {0, 0}};

    loadAssets();
    while (event.first != arc::Action::Close) {
        event = _display->getEvent();
        _game->simulate(event);
        _display->drawGame(_game->getElements());
        execCommand(_game->loadCommand());
    }
}

void arc::Core::help() noexcept {
    std::ifstream helpfile("src/help.txt");
    std::string line;

    while (std::getline(helpfile, line))
        std::cerr << line << std::endl;
}

void arc::Core::loadDisplay(std::vector<std::string> args)
{
    try {
        if (args.size())
            loadDisplayModule(args.front());
    } catch (const std::exception &e) {
        throw e;
    }
}

void arc::Core::loadGame(std::vector<std::string> args)
{
    try {
        if (args.size()) {
            loadGameModule(args.front());
            loadAssets();
            _gamePath = args.front();
        }
    } catch (const std::exception &e) {
        throw e;
    }
}

void arc::Core::restartGame(std::vector<std::string>)
{
    try {
        loadGameModule(_gamePath);
    } catch (const std::exception &e) {
        throw e;
    }
}

void arc::Core::BackToMenu(std::vector<std::string>)
{
    try {
        loadGameModule(DEFAULT_GAME_PATH);
        loadAssets();
    } catch (const std::exception &e) {
        throw e;
    }
}

void arc::Core::loadAssets()
{
    auto assets = _game->getAssets();
    if (_display->setAssets(assets) == ERROR)
        throw arc::exceptions::AssetLoadError();
}

void arc::Core::loadUser(std::vector<std::string> args)
{
    if (args.size())
        _user = args.front();
}

void arc::Core::loadScore(std::vector<std::string> args)
{
    std::string scorePath(SCORE_PATH);
    std::ofstream log(scorePath, std::ios_base::app | std::ios_base::out);

    if (args.size() && _user.find("_") == std::string::npos && !log.fail()) {
        int score = 0;
        std::istringstream tmp(args.front());
        tmp >> score;
        if (tmp.fail())
            return;
        log << _user + "," + _gamePath + "," << score << "\n";
    }
}

