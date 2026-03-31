/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Core
*/

#include <fstream>
#include <iostream>
#include "Core.hpp"
#include "DLLoader.hpp"
#include "Exceptions.hpp"
#define DEBUG(value) std::cout << "\e[0;35m" << "DEBUG: " <<  "\e[0;37m" << "\t" << value << std::endl;

arc::Core::Core(const std::string &path): _loader(path) {
    auto disp = _loader.makeInstance<IDisplayModule>();
    if (!disp.has_value())
        throw arc::exceptions::NotGraphical();
    _display = std::unique_ptr<IDisplayModule>(disp.value().release());

    _loader.reset(DEFAULT_GAME_PATH);
    auto game = _loader.makeInstance<IGameModule>();
    if (!game.has_value())
        throw arc::exceptions::LibraryLoadError();
    _game = std::unique_ptr<IGameModule>(game.value().release());
}

void arc::Core::loadGameModule(const std::string &path, const std::exception &e) {
    _loader.reset(path);
    auto game = _loader.makeInstance<IGameModule>();
    if (!game.has_value())
        throw e;
    _game = std::unique_ptr<IGameModule>(game.value().release());
}

void arc::Core::loadDisplayModule(const std::string &path, const std::exception &e) {
    _loader.reset(path);
    auto game = _loader.makeInstance<IDisplayModule>();
    if (!game.has_value())
        throw e;
    _display = std::unique_ptr<IDisplayModule>(game.value().release());
}

void arc::Core::play() {
    Event event = {arc::Action::None, {0, 0}};

    auto assets = _game->getAssets();
    _display->setAssets(assets);
    while (event.first != arc::Action::Close) {
        event = _display->getEvent();
        auto elements = _game->getElements();
        _game->simulate(event);
        _display->drawGame(elements);
    }
}

void arc::Core::help(const std::string &path) noexcept {
    std::cerr << "Error: '" + path + "' not a graphical library" << std::endl;
    std::cerr << "Exit code: 84" << std::endl;
}

