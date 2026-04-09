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

arc::Core::Core(const std::string &path) {
    setFunctions();
    try {
       _splitLibs = arc::Utils::getSplitLibs();

        for (const auto &display:_splitLibs.first)
            _displayLoader.emplace_back(display);
        for (const auto &game:_splitLibs.second)
            _gameLoader.emplace_back(game);
        
        _displayIdx = arc::Utils::findLib(_splitLibs.first, path);
        auto display = _displayLoader[_displayIdx].makeInstance<IDisplayModule>(arc::LibType::Display);
        if (!display.has_value())
            throw arc::exceptions::NotGraphical();
        _display.reset(display.value().release());

        loadGameModule(DEFAULT_GAME_PATH);
    } catch (const arc::exceptions::LibraryLoadError &e) {
        throw e;
    } catch (const arc::exceptions::NotGraphical &e) {
        throw e;
    } catch (...) {
        throw arc::exceptions::LibraryLoadError();
    }
}

void arc::Core::setFunctions()
{
    _commands[arc::Signal::LoadDisplay] = [this](std::vector<std::string> list) {loadDisplay(list);};
    _commands[arc::Signal::LoadGame] = [this](std::vector<std::string> list) {loadGame(list);};
    _commands[arc::Signal::RestartGame] = [this](std::vector<std::string> list) {restartGame(list);};
    _commands[arc::Signal::BackToMenu] = [this](std::vector<std::string> list) {BackToMenu(list);};
    _commands[arc::Signal::LoadUser] = [this](std::vector<std::string> list) {loadUser(list);};
    _commands[arc::Signal::LoadScore] = [this](std::vector<std::string> list) {loadScore(list);};

    _builtins[arc::Action::F1] = [this]() {BackToMenu();};
    _builtins[arc::Action::F2] = [this]() {restartGame();};
    _builtins[arc::Action::F3] = [this]() {iterGame();};
    _builtins[arc::Action::Tab] = [this]() {iterDisplay();};
}

void arc::Core::loadGameModule(const std::string &path) {
    _game.reset();
    _gameIdx = arc::Utils::findLib(_splitLibs.second, path);
    auto game = _gameLoader[_gameIdx].makeInstance<IGameModule>(arc::LibType::Game);
    if (!game.has_value())
        throw arc::exceptions::LibraryLoadError();
    _game.reset(game.value().release());
}

void arc::Core::loadDisplayModule(const std::string &path) {
    _display.reset();
    _displayIdx = arc::Utils::findLib(_splitLibs.first, path);
    auto display = _displayLoader[_displayIdx].makeInstance<IDisplayModule>(arc::LibType::Display);
    if (!display.has_value())
        throw arc::exceptions::LibraryLoadError();
    _display.reset(display.value().release());
}

void arc::Core::execCommand(const std::vector<Command> commands)
{
    for (auto part: commands)
        _commands[part.first](part.second);
}

void arc::Core::execBuiltin(const Action action)
{
    if (_builtins[action] != nullptr)
        _builtins[action]();
}

void arc::Core::play() {
    Event event = {arc::Action::None, {0, 0}};

    loadAssets();
    while (event.first != arc::Action::Close
        && event.first != arc::Action::F4) {
        event = _display->getEvent();
        _game->simulate(event);
        _display->drawGame(_game->getElements());
        execBuiltin(event.first);
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
        if (args.size() && _displayLoader[_displayIdx].getLibPath() != args.front()) {
            loadDisplayModule(args.front());
            loadAssets();
            _displayIdx = arc::Utils::findLib(_splitLibs.first, args.front());
            _displayLoader[_displayIdx].getLibPath() = args.front();
        }
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
            _gameIdx = arc::Utils::findLib(_splitLibs.second, args.front());
        }
    } catch (const std::exception &e) {
        throw e;
    }
}

void arc::Core::restartGame(std::vector<std::string>)
{
    try {
        loadGameModule(_gameLoader[_gameIdx].getLibPath());
    } catch (const std::exception &e) {
        throw e;
    }
}

void arc::Core::BackToMenu(std::vector<std::string>)
{
    try {
        loadGameModule(DEFAULT_GAME_PATH);
        loadAssets();
        _gameIdx = arc::Utils::findLib(_splitLibs.second, DEFAULT_GAME_PATH);
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
        log << _user + "," + _gameLoader[_gameIdx].getLibPath() + "," << score << "\n";
    }
}

void arc::Core::iterDisplay()
{
    ++_displayIdx;
    if (_displayIdx >= _splitLibs.first.size())
        _displayIdx = 0;
    std::vector<std::string> tmp = {_splitLibs.first[_displayIdx]};
    loadDisplay(tmp);
}

void arc::Core::iterGame()
{
    ++_gameIdx;
    if (_gameIdx >= _splitLibs.second.size())
        _gameIdx = 0;
    std::vector<std::string> tmp = {_splitLibs.second[_gameIdx]};
    loadGame(tmp);
}
